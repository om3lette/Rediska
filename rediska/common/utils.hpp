#pragma once

#include <type_traits>
#include "rediska/common/types.hpp"

template<typename T, typename... Ts>
constexpr bool is_any_of_v = (std::is_same_v<T, Ts> || ...);

inline RediskaReturnCode DSReturnCodeToRediskaReturnCode(DSReturnCode code) {
    switch (code) {
        case DSReturnCode::OK:
            return RediskaReturnCode::OK;
        case DSReturnCode::NOT_FOUND:
            return RediskaReturnCode::NOT_FOUND;
        case DSReturnCode::INCOMPATIBLE_OPERATION:
            return RediskaReturnCode::INCOMPATIBLE_OPERATION;
        case DSReturnCode::EMPTY:
            return RediskaReturnCode::DS_EMPTY;
        case DSReturnCode::OUT_OF_RANGE:
            return RediskaReturnCode::DS_OUT_OF_RANGE;
        default:
            return RediskaReturnCode::UNKNOWN_ERROR;
    }
}
