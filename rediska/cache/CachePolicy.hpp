#include "rediska/common/enums.hpp"
#include "rediska/common/types.hpp"

namespace cache {
    class CachePolicy {
        public:
            virtual ~CachePolicy() = default;

            virtual void get(CacheKey&& key) = 0;

            virtual void set(CacheKey&& key, CacheValue&& value, TTL ttl) = 0;

            virtual void applyTo(CacheKey&& key, OperationId op, CacheValueId type) = 0;
    };
}
