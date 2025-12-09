#pragma once

#include <cstddef>
#include "rediska/cache/BaseCacheConfig.hpp"
#include "rediska/common/types.hpp"

namespace cache {
    struct LRUConfig : BaseCacheConfig {
        size_t maxCapacity;
        TTL ttl;
    };
}
