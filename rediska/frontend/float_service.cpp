#include <grpcpp/grpcpp.h>
#include "v1/primitives/float.grpc.pb.h"

#include "cache/frontend_message.hpp"
#include "queue/send_to_backend.hpp"

namespace rediska::frontend {

class FloatCacheServiceImpl :
    public v1::primitives::floating::FloatCacheService::Service {

public:
    grpc::Status Create(
        grpc::ServerContext*,
        const v1::primitives::floating::FloatCreateRequest* request,
        v1::primitives::floating::FloatCreateResponse* response) override
    {
        FrontendMessage msg;
        msg.key = request->key();
        msg.operation = OperationId::FloatCreate;
        msg.arguments.float_value = request->initial_value();

        msg.reply = [response](const BackendResult& result) {
            response->set_id(result.created_id);
        };

        EnqueueToBackend(std::move(msg));
        return grpc::Status::OK;
    }

    grpc::Status Set(
        grpc::ServerContext*,
        const v1::primitives::floating::FloatSetRequest* request,
        google::protobuf::Empty*) override
    {
        FrontendMessage msg;
        msg.key = request->key();
        msg.operation = OperationId::FloatSet;
        msg.arguments.float_value = request->new_value();

        msg.reply = [](const BackendResult&) {};
        EnqueueToBackend(std::move(msg));
        return grpc::Status::OK;
    }

    grpc::Status Get(
        grpc::ServerContext*,
        const v1::primitives::floating::FloatGetRequest* request,
        v1::primitives::floating::FloatGetResponse* response) override
    {
        FrontendMessage msg;
        msg.key = request->key();
        msg.operation = OperationId::FloatGet;

        msg.reply = [response](const BackendResult& result) {
            response->set_value(result.float_value);
        };

        EnqueueToBackend(std::move(msg));
        return grpc::Status::OK;
    }

    grpc::Status Delete(
        grpc::ServerContext*,
        const v1::primitives::floating::FloatDeleteRequest* request,
        v1::primitives::floating::FloatDeleteResponse* response) override
    {
        FrontendMessage msg;
        msg.key = request->key();
        msg.operation = OperationId::FloatDelete;

        msg.reply = [response](const BackendResult& result) {
            response->set_deleted(result.success);
        };

        EnqueueToBackend(std::move(msg));
        return grpc::Status::OK;
    }
};

std::unique_ptr<grpc::Service> MakeFloatService() {
    return std::make_unique<FloatCacheServiceImpl>();
}

} // namespace rediska::frontend
