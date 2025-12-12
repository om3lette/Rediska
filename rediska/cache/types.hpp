#pragma once

#include <expected>
#include <functional>
#include <optional>
#include "rediska/common/types.hpp"

namespace cache {
    using CacheOpCallback = std::function<void(std::expected<std::optional<CacheValue>, RediskaReturnCode>)>;
}
