#include "rediska/cache/lru/LRU.hpp"
#include <algorithm>
#include <expected>
#include <mutex>
#include <chrono>
#include <optional>
#include "rediska/cache/lru/LRUConfig.hpp"
#include "rediska/cache/types.hpp"
#include "rediska/common/types.hpp"

namespace cache {
    LRU::LRU(LRUConfig config, CacheOpCallback callback)
        : config_(std::move(config)), callback_(callback) {}

    void LRU::get(CacheKey&& key) {
        std::shared_lock lock(mutex_);
        auto it = keyToItem_.find(key);
        if (it == keyToItem_.end()) {
            lock.unlock();
            return callback_(std::unexpected<RediskaReturnCode>(RediskaReturnCode::NOT_FOUND));
        }

        // Move to start
        lru_list_.splice(lru_list_.begin(), lru_list_, it->second);
        keyToItem_[key] = lru_list_.begin();

        callback_(OptionalRef<CacheValue>(it->second->value));
    }

    void LRU::set(CacheKey&& key, CacheValue&& value, TTL ttl) {
        std::unique_lock lock(mutex_);
        auto it = keyToItem_.find(key);
        if (it != keyToItem_.end()) {
            it->second->value = std::move(value);
            lru_list_.splice(lru_list_.begin(), lru_list_, it->second);
            lock.unlock();
            callback_(OptionalRef<CacheValue>());
            return;
        }

        if (lru_list_.size() >= config_.maxCapacity) {
            keyToItem_.erase(key);
            lru_list_.pop_back();
        }
        lru_list_.push_front(
            ItemHandle{
                .value = std::move(value),
                .metadata = ItemMetadata {
                    .expires_at = std::chrono::steady_clock::now() + std::chrono::seconds(ttl)
                }
            }
        );
        keyToItem_[key] = lru_list_.begin();
        callback_(OptionalRef<CacheValue>());
    }

    void LRU::applyTo(CacheKey&& key, OperationId op, CacheValueId type) {
        // TODO:
        (void) op;
        (void) type;

        std::unique_lock lock(mutex_);
        auto it = keyToItem_.find(key);
        if (it == keyToItem_.end()) {
            lock.unlock();
            return callback_(std::unexpected<RediskaReturnCode>(RediskaReturnCode::NOT_FOUND));
        }

        std::optional<CacheValue> value;
        // TODO: Extract value from variant with index type Return error on failure
        // TODO: Call handle with arguments (add arguments)
        lru_list_.splice(lru_list_.begin(), lru_list_, it->second);
        lock.unlock();
        callback_(OptionalRef<CacheValue>());
        return;
    }
}
