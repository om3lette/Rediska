#include <grpcpp/grpcpp.h>
#include "v1/primitives/string.grpc.pb.h"

#include "cache/frontend_message.hpp"
#include "queue/send_to_backend.hpp"

namespace rediska::frontend {

class StringCacheServiceImpl :
    public v1::primitives::str::StringCacheService::Service {

public:
    grpc::Status Create(
        grpc::ServerContext*,
        const v1::primitives::str::StringCreateRequest* request,
        v1::primitives::str::StringCreateResponse* response) override
    {
        FrontendMessage msg;
        msg.key = request->key();
        msg.operation = OperationId::StringCreate;
        msg.arguments.string_value = request->initial_value();

        msg.reply = [response](const BackendResult& result) {
            response->set_id(result.created_id);
        };

        EnqueueToBackend(std::move(msg));
        return grpc::Status::OK;
    }

    grpc::Status Set(
        grpc::ServerContext*,
        const v1::primitives::str::StringSetRequest* request,
        google::protobuf::Empty*) override
    {
        FrontendMessage msg;
        msg.key = request->key();
        msg.operation = OperationId::StringSet;
        msg.arguments.string_value = request->new_value();

        msg.reply = [](const BackendResult&) {};
        EnqueueToBackend(std::move(msg));
        return grpc::Status::OK;
    }

    grpc::Status Get(
        grpc::ServerContext*,
        const v1::primitives::str::StringGetRequest* request,
        v1::primitives::str::StringGetResponse* response) override
    {
        FrontendMessage msg;
        msg.key = request->key();
        msg.operation = OperationId::StringGet;

        msg.reply = [response](const BackendResult& result) {
            response->set_value(result.string_value);
        };

        EnqueueToBackend(std::move(msg));
        return grpc::Status::OK;
    }

    grpc::Status Delete(
        grpc::ServerContext*,
        const v1::primitives::str::StringDeleteRequest* request,
        v1::primitives::str::StringDeleteResponse* response) override
    {
        FrontendMessage msg;
        msg.key = request->key();
        msg.operation = OperationId::StringDelete;

        msg.reply = [response](const BackendResult& result) {
            response->set_deleted(result.success);
        };

        EnqueueToBackend(std::move(msg));
        return grpc::Status::OK;
    }
};

std::unique_ptr<grpc::Service> MakeStringService() {
    return std::make_unique<StringCacheServiceImpl>();
}

} // namespace rediska::frontend
