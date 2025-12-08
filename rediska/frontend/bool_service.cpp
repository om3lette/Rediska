#include <grpcpp/grpcpp.h>
#include "v1/primitives/bool.grpc.pb.h"

#include "cache/frontend_message.hpp"
#include "queue/send_to_backend.hpp"

namespace rediska::frontend {

class BoolCacheServiceImpl :
    public v1::primitives::boolean::BoolCacheService::Service {

public:
    grpc::Status Create(
        grpc::ServerContext*,
        const v1::primitives::boolean::BoolCreateRequest* request,
        v1::primitives::boolean::BoolCreateResponse* response) override
    {
        FrontendMessage msg;
        msg.key = request->key();
        msg.operation = OperationId::BoolCreate;
        msg.arguments.bool_value = request->initial_value();

        msg.reply = [response](const BackendResult& result) {
            response->set_id(result.created_id);
        };

        EnqueueToBackend(std::move(msg));
        return grpc::Status::OK;
    }

    grpc::Status Set(
        grpc::ServerContext*,
        const v1::primitives::boolean::BoolSetRequest* request,
        google::protobuf::Empty*) override
    {
        FrontendMessage msg;
        msg.key = request->key();
        msg.operation = OperationId::BoolSet;
        msg.arguments.bool_value = request->new_value();

        msg.reply = [](const BackendResult&) {};
        EnqueueToBackend(std::move(msg));
        return grpc::Status::OK;
    }

    grpc::Status Get(
        grpc::ServerContext*,
        const v1::primitives::boolean::BoolGetRequest* request,
        v1::primitives::boolean::BoolGetResponse* response) override
    {
        FrontendMessage msg;
        msg.key = request->key();
        msg.operation = OperationId::BoolGet;

        msg.reply = [response](const BackendResult& result) {
            response->set_value(result.bool_value);
        };

        EnqueueToBackend(std::move(msg));
        return grpc::Status::OK;
    }

    grpc::Status Delete(
        grpc::ServerContext*,
        const v1::primitives::boolean::BoolDeleteRequest* request,
        v1::primitives::boolean::BoolDeleteResponse* response) override
    {
        FrontendMessage msg;
        msg.key = request->key();
        msg.operation = OperationId::BoolDelete;

        msg.reply = [response](const BackendResult& result) {
            response->set_deleted(result.success);
        };

        EnqueueToBackend(std::move(msg));
        return grpc::Status::OK;
    }
};

std::unique_ptr<grpc::Service> MakeBoolService() {
    return std::make_unique<BoolCacheServiceImpl>();
}

} // namespace rediska::frontend
