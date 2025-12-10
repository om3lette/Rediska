// rediska/frontend/ListService.cpp

#include <grpcpp/grpcpp.h>
#include "v1/collections/list.grpc.pb.h"

namespace rediska::frontend {

class ListCacheServiceImpl final
    : public v1::collections::ListCacheService::Service {
public:
    grpc::Status Create(
        grpc::ServerContext* context,
        grpc::ServerReader<v1::collections::ListCreateRequest>* reader,
        v1::collections::ListCreateResponse* response) override
    {
        return grpc::Status(
            grpc::StatusCode::UNIMPLEMENTED,
            "ListCacheService.Create is not implemented yet"
        );
    }

    grpc::Status Get(
        grpc::ServerContext* context,
        const v1::collections::ListGetRequest* request,
        grpc::ServerWriter<v1::collections::ListGetResponse>* writer) override
    {
        return grpc::Status(
            grpc::StatusCode::UNIMPLEMENTED,
            "ListCacheService.Get is not implemented yet"
        );
    }

    grpc::Status Insert(
        grpc::ServerContext* context,
        const v1::collections::ListInsertRequest* request,
        google::protobuf::Empty* response) override
    {
        return grpc::Status(
            grpc::StatusCode::UNIMPLEMENTED,
            "ListCacheService.Insert is not implemented yet"
        );
    }

    grpc::Status Erase(
        grpc::ServerContext* context,
        const v1::collections::ListEraseRequest* request,
        v1::collections::ListEraseResponse* response) override
    {
        return grpc::Status(
            grpc::StatusCode::UNIMPLEMENTED,
            "ListCacheService.Erase is not implemented yet"
        );
    }

    grpc::Status Set(
        grpc::ServerContext* context,
        const v1::collections::ListSetRequest* request,
        v1::collections::ListSetResponse* response) override
    {
        return grpc::Status(
            grpc::StatusCode::UNIMPLEMENTED,
            "ListCacheService.Set is not implemented yet"
        );
    }

    grpc::Status Length(
        grpc::ServerContext* context,
        const v1::collections::ListLengthRequest* request,
        v1::collections::ListLengthResponse* response) override
    {
        return grpc::Status(
            grpc::StatusCode::UNIMPLEMENTED,
            "ListCacheService.Length is not implemented yet"
        );
    }

    grpc::Status PushBack(
        grpc::ServerContext* context,
        const v1::collections::PushBackRequest* request,
        google::protobuf::Empty* response) override
    {
        return grpc::Status(
            grpc::StatusCode::UNIMPLEMENTED,
            "ListCacheService.PushBack is not implemented yet"
        );
    }

    grpc::Status PushMany(
        grpc::ServerContext* context,
        grpc::ServerReader<v1::collections::PushManyRequest>* reader,
        google::protobuf::Empty* response) override
    {
        return grpc::Status(
            grpc::StatusCode::UNIMPLEMENTED,
            "ListCacheService.PushMany is not implemented yet"
        );
    }

    grpc::Status PopBack(
        grpc::ServerContext* context,
        const v1::collections::PopBackRequest* request,
        v1::collections::PopBackResponse* response) override
    {
        return grpc::Status(
            grpc::StatusCode::UNIMPLEMENTED,
            "ListCacheService.PopBack is not implemented yet"
        );
    }

    grpc::Status Clear(
        grpc::ServerContext* context,
        const v1::collections::ClearRequest* request,
        google::protobuf::Empty* response) override
    {
        return grpc::Status(
            grpc::StatusCode::UNIMPLEMENTED,
            "ListCacheService.Clear is not implemented yet"
        );
    }

    grpc::Status Delete(
        grpc::ServerContext* context,
        const v1::collections::DeleteRequest* request,
        google::protobuf::Empty* response) override
    {
        return grpc::Status(
            grpc::StatusCode::UNIMPLEMENTED,
            "ListCacheService.Delete is not implemented yet"
        );
    }
};

// Фабричная функция — по аналогии с примитивами/skeleton’ом
std::unique_ptr<grpc::Service> MakeListService()
{
    return std::make_unique<ListCacheServiceImpl>();
}

} // namespace rediska::frontend
