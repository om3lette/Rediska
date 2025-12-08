// rediska/frontend/skeleton_service.cpp

#include <memory>
#include <vector>
#include <grpcpp/grpcpp.h>
#include "v1/primitives/int.grpc.pb.h"

namespace rediska::frontend {

// Реализация сервиса для int, пока просто заглушки.
// Позже сюда заедет прокидывание в FrontendMessage / backend.

class IntCacheServiceImpl final
    : public v1::primitives::integer::IntCacheService::Service {
public:
    grpc::Status Create(
        grpc::ServerContext* /*context*/,
        const v1::primitives::integer::IntCreateRequest* /*request*/,
        v1::primitives::integer::IntCreateResponse* /*response*/) override
    {
        return grpc::Status(
            grpc::StatusCode::UNIMPLEMENTED,
            "IntCacheService.Create is not implemented yet"
        );
    }

    grpc::Status Set(
        grpc::ServerContext* /*context*/,
        const v1::primitives::integer::IntSetRequest* /*request*/,
        google::protobuf::Empty* /*response*/) override
    {
        return grpc::Status(
            grpc::StatusCode::UNIMPLEMENTED,
            "IntCacheService.Set is not implemented yet"
        );
    }

    grpc::Status Get(
        grpc::ServerContext* /*context*/,
        const v1::primitives::integer::IntGetRequest* /*request*/,
        v1::primitives::integer::IntGetResponse* /*response*/) override
    {
        return grpc::Status(
            grpc::StatusCode::UNIMPLEMENTED,
            "IntCacheService.Get is not implemented yet"
        );
    }

    grpc::Status Delete(
        grpc::ServerContext* /*context*/,
        const v1::primitives::integer::IntDeleteRequest* /*request*/,
        v1::primitives::integer::IntDeleteResponse* /*response*/) override
    {
        return grpc::Status(
            grpc::StatusCode::UNIMPLEMENTED,
            "IntCacheService.Delete is not implemented yet"
        );
    }
};

// Хелпер для регистрации сервисов фронтенда в gRPC-сервере.
// main() (в другом модуле) сможет просто вызвать эту функцию.

void RegisterFrontendServices(
    grpc::ServerBuilder& builder,
    std::vector<std::unique_ptr<grpc::Service>>& services)
{
    auto int_service = std::make_unique<IntCacheServiceImpl>();
    builder.RegisterService(int_service.get());
    services.push_back(std::move(int_service));

    // сюда же потом добавишь Bool/Float/String/List/Object сервисы
    // по той же схеме
}

} // namespace rediska::frontend
