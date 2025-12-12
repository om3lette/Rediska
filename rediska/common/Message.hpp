#pragma once

#include <variant>
#include <vector>

#include "rediska/common/enums.hpp"
#include "rediska/common/types.hpp"

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

// TODO: Consider adding CallData
struct FrontendMessage {
    CacheKey key;
    OperationId operation;
    MessageArguments arguments;
};
