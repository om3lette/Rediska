#include <list>
#include <shared_mutex>
#include <unordered_map>
#include "rediska/cache/constants.hpp"
#include "rediska/cache/types.hpp"
#include "rediska/common/types.hpp"
#include "rediska/cache/CachePolicy.hpp"

namespace cache {
    class LRU : public CachePolicy {
    public:
        using ItemMetadata = struct {
            Timestamp expires_at;
        };
        using ItemHandle = struct {
            CacheValue value;
            ItemMetadata metadata;
        };

        LRU(size_t capacity, CacheOpCallback callback);
        ~LRU() = default;

        void get(CacheKey&& key) override;

        void set(CacheKey&& key, CacheValue&& value, TTL ttl) override;

        void applyTo(CacheKey&& key, OperationId op, CacheValueId type) override;

    private:
        std::list<ItemHandle> lru_list_;
        std::unordered_map<CacheKey, std::list<ItemHandle>::iterator> keyToItem_;

        std::shared_mutex mutex_;

        size_t capacity_;
        CacheOpCallback callback_;
    };
}
