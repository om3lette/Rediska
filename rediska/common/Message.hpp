#pragma once

#include <variant>
#include <vector>

#include "rediska/common/enums.hpp"
#include "rediska/common/types.hpp"
#include <grpcpp/grpcpp.h>
#include <grpcpp/support/async_stream.h> // for ServerAsyncStreamingInterface completeness

// TODO: get rid of forward declaration somehow maybe
struct BaseRequestManager;

struct RequestEvent {
    BaseRequestManager& manager;
};

// This just leaves the responder for you to delete.
struct FinishEvent {
    std::unique_ptr<grpc::internal::ServerAsyncStreamingInterface> responder;
};

using EventVariant = std::variant<RequestEvent, FinishEvent>;


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
    bool replace_entire_list = false; // true => overwrite entire list, false => append
};

using MessageArguments = std::variant<std::monostate,
                                      PrimitiveSetArgs,
                                      ListCreateArgs,
                                      ListIndexArgs,
                                      ListSetArgs,
                                      ListInsertArgs,
                                      ListPushBackArgs,
                                      ListPushManyArgs>;

struct QueueMessage {
    CacheValueId type;
    CacheKey key;
    OperationId operation;
    MessageArguments arguments;
    std::unique_ptr<grpc::internal::ServerAsyncStreamingInterface> responder;

    template<typename ResponseT>
    void respond(ResponseT response) {
        if (auto* writer = dynamic_cast<grpc::ServerAsyncResponseWriter<ResponseT>*>(responder.get())) {
            writer->Finish(response, grpc::Status::OK, std::make_unique<EventVariant>(FinishEvent { std::move(responder) }).release());
            responder = nullptr;
        } else {
            throw std::runtime_error("Invalid responder type in QueueMessage::respond");
        }
    }
};
