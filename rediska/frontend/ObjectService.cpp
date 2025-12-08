// rediska/frontend/ObjectService.cpp

#include <grpcpp/grpcpp.h>
#include "v1/object/object.grpc.pb.h"

namespace rediska::frontend {

class ObjectCacheServiceImpl final
    : public v1::object::ObjectCacheService::Service {
public:
    grpc::Status Create(
        grpc::ServerContext* context,
        const v1::object::CreateObjectRequest* request,
        v1::object::CreateObjectResponse* response) override
    {
        return grpc::Status(
            grpc::StatusCode::UNIMPLEMENTED,
            "ObjectCacheService.Create is not implemented yet"
        );
    }

    grpc::Status Get(
        grpc::ServerContext* context,
        const v1::object::GetObjectRequest* request,
        v1::object::GetObjectResponse* response) override
    {
        return grpc::Status(
            grpc::StatusCode::UNIMPLEMENTED,
            "ObjectCacheService.Get is not implemented yet"
        );
    }

    grpc::Status Set(
        grpc::ServerContext* context,
        const v1::object::SetObjectRequest* request,
        google::protobuf::Empty* response) override
    {
        return grpc::Status(
            grpc::StatusCode::UNIMPLEMENTED,
            "ObjectCacheService.Set is not implemented yet"
        );
    }

    grpc::Status Delete(
        grpc::ServerContext* context,
        const v1::object::DeleteObjectRequest* request,
        google::protobuf::Empty* response) override
    {
        return grpc::Status(
            grpc::StatusCode::UNIMPLEMENTED,
            "ObjectCacheService.Delete is not implemented yet"
        );
    }

    grpc::Status GetField(
        grpc::ServerContext* context,
        const v1::object::GetObjectFieldRequest* request,
        v1::object::GetObjectFieldResponse* response) override
    {
        return grpc::Status(
            grpc::StatusCode::UNIMPLEMENTED,
            "ObjectCacheService.GetField is not implemented yet"
        );
    }

    grpc::Status SetField(
        grpc::ServerContext* context,
        const v1::object::SetObjectFieldRequest* request,
        google::protobuf::Empty* response) override
    {
        return grpc::Status(
            grpc::StatusCode::UNIMPLEMENTED,
            "ObjectCacheService.SetField is not implemented yet"
        );
    }

    grpc::Status DeleteField(
        grpc::ServerContext* context,
        const v1::object::DeleteObjectFieldRequest* request,
        google::protobuf::Empty* response) override
    {
        return grpc::Status(
            grpc::StatusCode::UNIMPLEMENTED,
            "ObjectCacheService.DeleteField is not implemented yet"
        );
    }
};

std::unique_ptr<grpc::Service> MakeObjectService()
{
    return std::make_unique<ObjectCacheServiceImpl>();
}

} // namespace rediska::frontend
