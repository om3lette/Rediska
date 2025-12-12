#include "rediska/common/enums.hpp"
#include "rediska/common/types.hpp"

namespace cache {
    class CachePolicy {
        public:
            virtual ~CachePolicy() = default;

            virtual void get(CacheKey&& key) = 0;

            virtual void set(CacheKey&& key, CacheValue&& value, TTL ttl) = 0;

            virtual void applyTo(CacheKey&& key, OperationId op) = 0;
        protected:
            inline static Timestamp getExpirationTime(TTL ttl) {
                return std::chrono::steady_clock::now() + std::chrono::seconds(ttl);
            }

            inline static bool isExpired(Timestamp expirationTime) {
                return expirationTime < std::chrono::steady_clock::now();
            }

            virtual void evict() = 0;
    };
}
