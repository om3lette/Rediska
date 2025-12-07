#pragma once

#include <expected>
#include <functional>
#include "rediska/common/types.hpp"
#include "rediska/common/OptionalRef.hpp"

namespace cache {
    using CacheOpCallback = std::function<void(std::expected<OptionalRef<CacheValue>, RediskaReturnCode>)>;
}
