#pragma once

#include <cstdint>
#include <memory>
#include <variant>
#include <chrono>
#include "rediska/data-structures/impl/ListDataStructure.hpp"

using CacheKey = std::string;

// Definition order of `CacheValueType` and `TypeId` MUST match!
using CacheValue = std::variant<bool, int64_t, double, char*, std::unique_ptr<ListDataStructure>>;

enum class CacheValueId { BOOLEAN = 0, INT, FLOAT, STRING, ARRAY }; // TODO: Object

enum class RediskaReturnCode { SUCCESS, INCOMPATIBLE_OPERATION, INVALID_OPERATION, EMPTY, OUT_OF_RANGE, NOT_FOUND };

using TTL = uint32_t;

using Timestamp = std::chrono::steady_clock::time_point;
