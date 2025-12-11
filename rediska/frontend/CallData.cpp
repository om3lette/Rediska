#include <grpcpp/grpcpp.h>
#include "v1/primitives/bool.grpc.pb.h"
#include "google/protobuf/empty.pb.h"
#include <memory>


/*
Usage pseudocode:

xxxManager is XxxRequestManager

service.RequestSet(&ctx, &setManager.request, &setManager.responder, cq_, cq_, static_cast<BaseRequestManager*>(setManager));
service.RequestDelete(&ctx, &deleteManager.request, &deleteManager.responder, cq_, cq_, static_cast<BaseRequestManager*>(deleteManager));
...

while (true) {
    cq->Next(&tag, &ok);
    GPR_ASSERT(ok);
    QueueMessage msg = static_cast<BaseRequestManager*>(tag)->MoveMessageOut();
    put msg into the queue
    then it can be answered through the responder and destroyed with the responder
}
*/

enum class OperationId {
    Create,
    Delete,
    // ...
};

enum class TypeId {
    Boolean,
    Integer,
    // ...
};

struct QueueMessage {
    std::string key;
    TypeId type;
    OperationId operation;


    void* arguments;

    std::unique_ptr<grpc::internal::ServerAsyncStreamingInterface> responder;
};

struct BaseRequestManager {
    virtual QueueMessage MoveMessageOut() = 0;
    virtual ~BaseRequestManager() = default;
};

struct SetRequestManager : public BaseRequestManager {
    v1::primitives::boolean::BoolSetRequest request;
    grpc::ServerAsyncResponseWriter<google::protobuf::Empty> responder;

    QueueMessage MoveMessageOut() override {
        QueueMessage msg;
        msg.key = request.id();
        msg.type = TypeId::Boolean;
        msg.operation = OperationId::Create;
        msg.arguments = nullptr;
        msg.responder = std::make_unique<grpc::ServerAsyncResponseWriter<google::protobuf::Empty>>(std::move(responder));;
        return msg;
    }
};
