#include <grpcpp/grpcpp.h>
#include <utility>

#include "v1/primitives/int.grpc.pb.h"
#include "cache/frontend_message.hpp"
#include "queue/send_to_backend.hpp"

namespace rediska::frontend {

class IntCacheServiceImpl final :
    public v1::primitives::integer::IntCacheService::Service {

public:
    grpc::Status Create(
        grpc::ServerContext* context,
        const v1::primitives::integer::IntCreateRequest* request,
        v1::primitives::integer::IntCreateResponse* response) override
    {
        FrontendMessage msg;
        msg.key = request->key();
        msg.operation = OperationId::IntCreate;
        msg.arguments.int_value = request->initial_value();

        msg.reply = [response](const BackendResult& result) {
            response->set_id(result.created_id);
        };

        EnqueueToBackend(std::move(msg));
        return grpc::Status::OK;
    }

    grpc::Status Set(
        grpc::ServerContext* context,
        const v1::primitives::integer::IntSetRequest* request,
        google::protobuf::Empty*) override
    {
        FrontendMessage msg;
        msg.key = request->key();
        msg.operation = OperationId::IntSet;
        msg.arguments.int_value = request->new_value();

        msg.reply = [](const BackendResult&) {};

        EnqueueToBackend(std::move(msg));
        return grpc::Status::OK;
    }

    grpc::Status Get(
        grpc::ServerContext* context,
        const v1::primitives::integer::IntGetRequest* request,
        v1::primitives::integer::IntGetResponse* response) override
    {
        FrontendMessage msg;
        msg.key = request->key();
        msg.operation = OperationId::IntGet;

        msg.reply = [response](const BackendResult& result) {
            response->set_value(result.int_value);
        };

        EnqueueToBackend(std::move(msg));
        return grpc::Status::OK;
    }

    grpc::Status Delete(
        grpc::ServerContext* context,
        const v1::primitives::integer::IntDeleteRequest* request,
        v1::primitives::integer::IntDeleteResponse* response) override
    {
        FrontendMessage msg;
        msg.key = request->key();
        msg.operation = OperationId::IntDelete;

        msg.reply = [response](const BackendResult& result) {
            response->set_deleted(result.success);
        };

        EnqueueToBackend(std::move(msg));
        return grpc::Status::OK;
    }
};

std::unique_ptr<grpc::Service> MakeIntService()
{
    return std::make_unique<IntCacheServiceImpl>();
}

} // namespace rediska::frontend
