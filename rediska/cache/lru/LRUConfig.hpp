#pragma once

#include <cstddef>
#include "rediska/cache/BaseCacheConfig.hpp"

namespace cache {
    struct LRUConfig : BaseCacheConfig {
        size_t maxCapacity = 10000;
    };
}
