#pragma once

#include <cstdint>
#include <string>
#include <variant>
#include "rediska/data-structures/impl/ListDataStructure.hpp"

// Definition order of `CacheValueType` and `TypeId` MUST match!

using CacheValueType = std::variant<bool, int64_t, double, std::string, ListDataStructure>;

enum class CacheValueTypeId { BOOLEAN = 0, INT, FLOAT, STRING, ARRAY }; // TODO: Object
