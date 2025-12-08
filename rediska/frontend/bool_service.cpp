#include "v1/primitives/boolean/bool.grpc.pb.h"
#include <grpcpp/grpcpp.h>
#include <grpcpp/support/status.h>
#include <memory>  
#include <future> 

namespace {

enum class element_kind { BOOL = 2};

void send_to_backend(const std::string& id, bool value, element_kind type, uint32_t ttl, std::function<void(const std::string& result_id)> callback) {
    //?
}

class bool_cache_service final : public v1::primitives::boolean::BoolCacheService::Service {
public:
    grpc::Status Create(grpc::ServerContext* context, const BoolCreateRequest* request, BoolCreateResponse* response) override {
        bool value = request->value();
        uint32_t ttl = request->has_ttl_seconds() ? request->ttl_seconds() : 0;
        element_kind type = element_kind::BOOL;

        std::promise<std::string> promise;
        std::future<std::string> future = promise.get_future();

        send_to_backend("", value, type, ttl, [&](const std::string& result_id) {
            promise.set_value(result_id); 
        });

        std::string id = future.get();
        response->set_id(id);

        return grpc::Status::OK;
    }

    grpc::Status Set(grpc::ServerContext* context, const BoolSetRequest* request, google::protobuf::Empty* response) override {
        std::string id = request->id();
        bool value = request->value();
        element_kind type = element_kind::BOOL;

        send_to_backend(id, value, type, 0, [](const std::string&) {});

        return grpc::Status::OK;
    }

    grpc::Status Get(grpc::ServerContext* context, const BoolGetRequest* request, BoolGetResponse* response) override {
        return grpc::Status::OK;
    }

    grpc::Status Delete(grpc::ServerContext* context, const BoolDeleteRequest* request, BoolDeleteResponse* response) override {
        return grpc::Status::OK;
    }
};

}  