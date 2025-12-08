#include "rediska/cache/lru/LRU.hpp"
#include <expected>
#include <mutex>
#include <optional>
#include <unordered_map>
#include "rediska/cache/lru/LRUConfig.hpp"
#include "rediska/cache/types.hpp"
#include "rediska/common/types.hpp"
#include "rediska/common/utils.hpp"

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

        if (isExpired(it->second->location.metadata.expiresAt)) {
            lock.unlock();
            evict(it);
            return callback_(std::unexpected<RediskaReturnCode>(RediskaReturnCode::KEY_EXPIRED));
        }

        // Move to start
        lru_list_.splice(lru_list_.begin(), lru_list_, it->second);
        keyToItem_[key] = lru_list_.begin();

        callback_(OptionalRef<CacheValue>(it->second->location.value));
    }

    void LRU::set(CacheKey&& key, CacheValue&& value, TTL ttl) {
        std::unique_lock lock(mutex_);
        auto it = keyToItem_.find(key);
        if (it != keyToItem_.end()) {
            it->second->location.value = std::move(value);
            lru_list_.splice(lru_list_.begin(), lru_list_, it->second);
            lock.unlock();
            callback_(OptionalRef<CacheValue>());
            return;
        }

        if (lru_list_.size() >= config_.maxCapacity) evict();
        lru_list_.push_front(
            CacheNode {
                .key = std::move(key),
                .location = ItemHandle{
                    .value = std::move(value),
                    .metadata = ItemMetadata {
                        .expiresAt = getExpirationTime(ttl)
                    }
                }
            }
        );
        keyToItem_[key] = lru_list_.begin();
        callback_(OptionalRef<CacheValue>());
    }

    void LRU::applyTo(CacheKey&& key, OperationId op) {
        std::unique_lock lock(mutex_);
        auto it = keyToItem_.find(key);
        if (it == keyToItem_.end()) {
            lock.unlock();
            return callback_(std::unexpected<RediskaReturnCode>(RediskaReturnCode::NOT_FOUND));
        }

        // variant<bool, long, double, basic_string<char>, unique_ptr<ListDataStructure>>
        std::expected<std::optional<CacheValue>, RediskaReturnCode> value;
        std::visit([&value, op](auto&& arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (is_any_of_v<T, int64_t, bool, double, std::string>) {
                value = std::unexpected(RediskaReturnCode::INCOMPATIBLE_OPERATION);
            } else if constexpr (std::is_same_v<T, std::unique_ptr<ListDataStructure>>) {
                // TODO: Replace with real data argument
                DSValueType dummy_data{};

                std::expected<std::optional<DSValueType>, DSReturnCode> res = arg->handle(op, std::move(dummy_data));
                if (!res) {
                    value = std::unexpected(DSReturnCodeToRediskaReturnCode(res.error()));
                    return;
                }
                if (!res.value().has_value()) {
                    value = std::nullopt;
                    return;
                }

                // TODO: Explore implicit conversion
                // Attempts to covert failed
                value = std::visit([](auto&& arg) -> CacheValue {
                    return CacheValue{std::move(arg)};
                }, std::move(res->value()));
            }
        }, it->second->location.value);

        // TODO: Extract value from variant with index type Return error on failure
        // TODO: Call handle with arguments (add arguments)
        lru_list_.splice(lru_list_.begin(), lru_list_, it->second);
        lock.unlock();
        callback_(OptionalRef<CacheValue>());
        return;
    }

    void LRU::evict() {
        if (lru_list_.empty()) return;

        keyToItem_.erase(lru_list_.back().key);
        lru_list_.pop_back();
    }

    void LRU::evict(const std::unordered_map<CacheKey, std::list<CacheNode>::iterator>::iterator node) {
        lru_list_.erase(node->second);
        keyToItem_.erase(node->second->key);
    }
}
