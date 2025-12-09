#include <list>
#include <shared_mutex>
#include <unordered_map>
#include "rediska/cache/constants.hpp"
#include "rediska/cache/lru/LRUConfig.hpp"
#include "rediska/cache/types.hpp"
#include "rediska/common/types.hpp"
#include "rediska/cache/CachePolicy.hpp"

namespace cache {
    class LRU : public CachePolicy {
    public:
        using ItemMetadata = struct {
            Timestamp expiresAt;
        };
        using ItemHandle = struct {
            CacheValue value;
            ItemMetadata metadata;
        };
        using CacheNode = struct {
            CacheKey key;
            ItemHandle location;
        };

        LRU(LRUConfig config, CacheOpCallback callback);
        ~LRU() = default;

        void get(CacheKey&& key) override;

        void set(CacheKey&& key, CacheValue&& value, TTL ttl) override;

        void applyTo(CacheKey&& key, OperationId op) override;

    private:
        std::list<CacheNode> lru_list_;
        std::unordered_map<CacheKey, std::list<CacheNode>::iterator> keyToItem_;

        std::shared_mutex mutex_;

        LRUConfig config_;
        CacheOpCallback callback_;

        void evict() override;

        void evict(const std::unordered_map<CacheKey, std::list<CacheNode>::iterator>::iterator node);

        void resetTTLIfEnabled(CacheNode& key);
    };
}
