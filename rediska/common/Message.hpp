#pragma once

#include <functional>
#include <variant>
#include <vector>

#include "rediska/common/OptionalRef.hpp"
#include "rediska/common/enums.hpp"
#include "rediska/common/types.hpp"

using FrontendReplyCallback =
    std::function<void(std::expected<OptionalRef<CacheValue>, RediskaReturnCode>)>;

struct PrimitiveSetArgs {
    CacheValue value;
    TTL ttl_seconds;
};

struct ListCreateArgs {
    CacheValueId element_kind;
    TTL ttl_seconds;
};

struct ListIndexArgs {
    int64_t index;
};

struct ListSetArgs {
    int64_t index;
    CacheValue value;
};

struct ListInsertArgs {
    int64_t index;
    CacheValue value;
};

struct ListPushBackArgs {
    CacheValue value;
};

struct ListPushManyArgs {
    std::vector<CacheValue> values;
};

using MessageArguments = std::variant<std::monostate,
                                      PrimitiveSetArgs,
                                      ListCreateArgs,
                                      ListIndexArgs,
                                      ListSetArgs,
                                      ListInsertArgs,
                                      ListPushBackArgs,
                                      ListPushManyArgs>;

struct FrontendMessage {
    CacheKey key;
    OperationId operation;
    MessageArguments arguments;
    FrontendReplyCallback reply;
};
