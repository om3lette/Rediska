#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <variant>
#include <chrono>
#include "rediska/data-structures/impl/ListDataStructure.hpp"

using CacheKey = std::string;

// Definition order of `CacheValue` and `TypeId` MUST match!
using CacheValue = std::variant<bool, int64_t, double, std::string, std::unique_ptr<ListDataStructure>>;

enum class CacheValueId { BOOLEAN = 0, INT, FLOAT, STRING, ARRAY }; // TODO: Object

enum class RediskaReturnCode {
    OK,
    INCOMPATIBLE_OPERATION,
    NOT_FOUND,
    KEY_EXPIRED,
    UNKNOWN_ERROR,
    DS_EMPTY,
    DS_OUT_OF_RANGE,
    DS_UNKNOWN_ERROR
};

using TTL = uint32_t;

using Timestamp = std::chrono::steady_clock::time_point;
