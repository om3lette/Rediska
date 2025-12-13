#include <functional>
#include <grpcpp/grpcpp.h>
#include <memory>
#include <vector>
#include "google/protobuf/empty.pb.h"

#include "v1/collections/list.grpc.pb.h"
#include "v1/primitives/bool.grpc.pb.h"
#include "v1/primitives/int.grpc.pb.h"
#include "v1/primitives/string.grpc.pb.h"

#include "rediska/common/Message.hpp"
#include "rediska/frontend/RequestManager.hpp"
#include "rediska/frontend/server.hpp"

namespace {
    CacheValue CollectionElementToCacheValue(const v1::collections::common::CollectionElement& element) {
        if (element.has_integer())
            return static_cast<int64_t>(element.integer());
        if (element.has_floating_point())
            return element.floating_point();
        if (element.has_boolean())
            return element.boolean();
        if (element.has_str_or_obj())
            return element.str_or_obj();
        return std::string{};
    }
} // namespace

using BoolService = v1::primitives::boolean::BoolCacheService::AsyncService;
using IntService = v1::primitives::integer::IntCacheService::AsyncService;
using StringService = v1::primitives::str::StringCacheService::AsyncService;
using ListService = v1::collections::list::ListCacheService::AsyncService;

struct BoolSetRequestManager : RequestManager<
                                   BoolSetRequestManager,
                                   v1::primitives::boolean::BoolSetRequest,
                                   grpc::ServerAsyncResponseWriter<google::protobuf::Empty>,
                                   BoolService,
                                   &BoolService::RequestSet> {
    using RequestManager::RequestManager;

    QueueMessage BuildMessage() {
        QueueMessage msg;
        msg.type = CacheValueId::BOOLEAN;
        msg.key = this->request.id();
        msg.operation = OperationId::SET;
        msg.arguments = PrimitiveSetArgs{.value = CacheValue{this->request.value()}, .ttl_seconds = 0};
        msg.responder = this->TakeResponder();
        return msg;
    }
};

struct BoolGetRequestManager : RequestManager<
                                   BoolGetRequestManager,
                                   v1::primitives::boolean::BoolGetRequest,
                                   grpc::ServerAsyncResponseWriter<v1::primitives::boolean::BoolGetResponse>,
                                   BoolService,
                                   &BoolService::RequestGet> {
    using RequestManager::RequestManager;

    QueueMessage BuildMessage() {
        QueueMessage msg;
        msg.type = CacheValueId::BOOLEAN;
        msg.key = this->request.id();
        msg.operation = OperationId::GET;
        msg.arguments = std::monostate{};
        msg.responder = this->TakeResponder();
        return msg;
    }
};

struct BoolDeleteRequestManager : RequestManager<
                                      BoolDeleteRequestManager,
                                      v1::primitives::boolean::BoolDeleteRequest,
                                      grpc::ServerAsyncResponseWriter<v1::primitives::boolean::BoolDeleteResponse>,
                                      BoolService,
                                      &BoolService::RequestDelete> {
    using RequestManager::RequestManager;

    QueueMessage BuildMessage() {
        QueueMessage msg;
        msg.type = CacheValueId::BOOLEAN;
        msg.key = this->request.id();
        msg.operation = OperationId::DELETE;
        msg.arguments = std::monostate{};
        msg.responder = this->TakeResponder();
        return msg;
    }
};

struct IntSetRequestManager : RequestManager<
                                  IntSetRequestManager,
                                  v1::primitives::integer::IntSetRequest,
                                  grpc::ServerAsyncResponseWriter<google::protobuf::Empty>,
                                  IntService,
                                  &IntService::RequestSet> {
    using RequestManager::RequestManager;

    QueueMessage BuildMessage() {
        QueueMessage msg;
        msg.type = CacheValueId::INT;
        msg.key = this->request.id();
        msg.operation = OperationId::SET;
        msg.arguments = PrimitiveSetArgs{.value = CacheValue{this->request.value()}, .ttl_seconds = 0};
        msg.responder = this->TakeResponder();
        return msg;
    }
};

struct IntGetRequestManager : RequestManager<
                                  IntGetRequestManager,
                                  v1::primitives::integer::IntGetRequest,
                                  grpc::ServerAsyncResponseWriter<v1::primitives::integer::IntGetResponse>,
                                  IntService,
                                  &IntService::RequestGet> {
    using RequestManager::RequestManager;

    QueueMessage BuildMessage() {
        QueueMessage msg;
        msg.type = CacheValueId::INT;
        msg.key = this->request.id();
        msg.operation = OperationId::GET;
        msg.arguments = std::monostate{};
        msg.responder = this->TakeResponder();
        return msg;
    }
};

struct IntDeleteRequestManager : RequestManager<
                                     IntDeleteRequestManager,
                                     v1::primitives::integer::IntDeleteRequest,
                                     grpc::ServerAsyncResponseWriter<v1::primitives::integer::IntDeleteResponse>,
                                     IntService,
                                     &IntService::RequestDelete> {
    using RequestManager::RequestManager;

    QueueMessage BuildMessage() {
        QueueMessage msg;
        msg.type = CacheValueId::INT;
        msg.key = this->request.id();
        msg.operation = OperationId::DELETE;
        msg.arguments = std::monostate{};
        msg.responder = this->TakeResponder();
        return msg;
    }
};

struct StringSetRequestManager : RequestManager<
                                     StringSetRequestManager,
                                     v1::primitives::str::StringSetRequest,
                                     grpc::ServerAsyncResponseWriter<google::protobuf::Empty>,
                                     StringService,
                                     &StringService::RequestSet> {
    using RequestManager::RequestManager;

    QueueMessage BuildMessage() {
        QueueMessage msg;
        msg.type = CacheValueId::STRING;
        msg.key = this->request.id();
        msg.operation = OperationId::SET;
        msg.arguments = PrimitiveSetArgs{.value = CacheValue{this->request.value()}, .ttl_seconds = 0};
        msg.responder = this->TakeResponder();
        return msg;
    }
};

struct StringGetRequestManager : RequestManager<
                                     StringGetRequestManager,
                                     v1::primitives::str::StringGetRequest,
                                     grpc::ServerAsyncResponseWriter<v1::primitives::str::StringGetResponse>,
                                     StringService,
                                     &StringService::RequestGet> {
    using RequestManager::RequestManager;

    QueueMessage BuildMessage() {
        QueueMessage msg;
        msg.type = CacheValueId::STRING;
        msg.key = this->request.id();
        msg.operation = OperationId::GET;
        msg.arguments = std::monostate{};
        msg.responder = this->TakeResponder();
        return msg;
    }
};

struct StringDeleteRequestManager : RequestManager<
                                        StringDeleteRequestManager,
                                        v1::primitives::str::StringDeleteRequest,
                                        grpc::ServerAsyncResponseWriter<v1::primitives::str::StringDeleteResponse>,
                                        StringService,
                                        &StringService::RequestDelete> {
    using RequestManager::RequestManager;

    QueueMessage BuildMessage() {
        QueueMessage msg;
        msg.type = CacheValueId::STRING;
        msg.key = this->request.id();
        msg.operation = OperationId::DELETE;
        msg.arguments = std::monostate{};
        msg.responder = this->TakeResponder();
        return msg;
    }
};

struct ListSetRequestManager : RequestManager<
                                   ListSetRequestManager,
                                   v1::collections::list::ListSetRequest,
                                   grpc::ServerAsyncResponseWriter<v1::collections::list::ListSetResponse>,
                                   ListService,
                                   &ListService::RequestSet> {
    using RequestManager::RequestManager;
    QueueMessage BuildMessage() {
        std::vector<CacheValue> values;
        values.reserve(static_cast<size_t>(this->request.elements_size()));
        for (const auto& el : this->request.elements())
            values.emplace_back(CollectionElementToCacheValue(el));
        QueueMessage msg;
        msg.type = CacheValueId::ARRAY;
        msg.key = this->request.id();
        msg.operation = OperationId::SET;
        msg.arguments = ListPushManyArgs{.values = std::move(values), .replace_entire_list = true};
        msg.responder = this->TakeResponder();
        return msg;
    }
};

struct ListGetRequestManager : RequestManager<
                                   ListGetRequestManager,
                                   v1::collections::list::ListGetRequest,
                                   grpc::ServerAsyncWriter<v1::collections::list::ListGetResponse>,
                                   ListService,
                                   &ListService::RequestGet> {
    using RequestManager::RequestManager;

    QueueMessage BuildMessage() {
        QueueMessage msg;
        msg.type = CacheValueId::ARRAY;
        msg.key = this->request.id();
        msg.operation = OperationId::GET;
        msg.arguments = std::monostate{};
        msg.responder = this->TakeResponder();
        return msg;
    }
};

struct ListDeleteRequestManager : RequestManager<
                                      ListDeleteRequestManager,
                                      v1::collections::list::DeleteRequest,
                                      grpc::ServerAsyncResponseWriter<google::protobuf::Empty>,
                                      ListService,
                                      &ListService::RequestDelete> {
    using RequestManager::RequestManager;

    QueueMessage BuildMessage() {
        QueueMessage msg;
        msg.type = CacheValueId::ARRAY;
        msg.key = this->request.id();
        msg.operation = OperationId::DELETE;
        msg.arguments = std::monostate{};
        msg.responder = this->TakeResponder();
        return msg;
    }
};

void RunFrontendServer(const std::string& address, std::function<void(QueueMessage)> callback_enqueue_message) {
    grpc::ServerBuilder builder;
    BoolService bool_service;
    IntService int_service;
    StringService string_service;
    ListService list_service;

    builder.AddListeningPort(address, grpc::InsecureServerCredentials());
    builder.RegisterService(&bool_service);
    builder.RegisterService(&int_service);
    builder.RegisterService(&string_service);
    builder.RegisterService(&list_service);

    std::unique_ptr<grpc::ServerCompletionQueue> cq = builder.AddCompletionQueue();
    std::unique_ptr<grpc::Server> server = builder.BuildAndStart();

    BoolSetRequestManager _BoolSetRequestManager(bool_service);
    _BoolSetRequestManager.ListenForOne(*cq);
    BoolGetRequestManager _BoolGetRequestManager(bool_service);
    _BoolGetRequestManager.ListenForOne(*cq);
    BoolDeleteRequestManager _BoolDeleteRequestManager(bool_service);
    _BoolDeleteRequestManager.ListenForOne(*cq);

    IntSetRequestManager _IntSetRequestManager(int_service);
    _IntSetRequestManager.ListenForOne(*cq);
    IntGetRequestManager _IntGetRequestManager(int_service);
    _IntGetRequestManager.ListenForOne(*cq);
    IntDeleteRequestManager _IntDeleteRequestManager(int_service);
    _IntDeleteRequestManager.ListenForOne(*cq);

    StringSetRequestManager _StringSetRequestManager(string_service);
    _StringSetRequestManager.ListenForOne(*cq);
    StringGetRequestManager _StringGetRequestManager(string_service);
    _StringGetRequestManager.ListenForOne(*cq);
    StringDeleteRequestManager _StringDeleteRequestManager(string_service);
    _StringDeleteRequestManager.ListenForOne(*cq);

    ListSetRequestManager _ListSetRequestManager(list_service);
    _ListSetRequestManager.ListenForOne(*cq);
    ListGetRequestManager _ListGetRequestManager(list_service);
    _ListGetRequestManager.ListenForOne(*cq);
    ListDeleteRequestManager _ListDeleteRequestManager(list_service);
    _ListDeleteRequestManager.ListenForOne(*cq);

    void* tag;
    bool ok;
    while (cq->Next(&tag, &ok)) {
        if (!tag)
            continue;
        // taking ownership as per the manager api
        std::unique_ptr<EventVariant> event(static_cast<EventVariant*>(tag));

        if (!ok) {
            // idk could happen, but we do take ownership of the event anyway
            (void)event;
            continue;
        }

        if (auto* req = std::get_if<RequestEvent>(event.get())) {
            auto& manager = req->manager;
            if (auto msg = manager.ConsumeMessage(); msg.has_value()) {
                callback_enqueue_message(std::move(*msg));
            }
            manager.ListenForOne(*cq);
        } else if (auto* fin = std::get_if<FinishEvent>(event.get())) {
            // we just destroy
            std::cout << "Finished a request\n" << std::flush;
            (void)fin;
        }
    }
}
