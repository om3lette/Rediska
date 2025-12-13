#pragma once

#include <grpcpp/grpcpp.h>
#include <grpcpp/support/async_stream.h>
#include <memory>
#include <optional>
#include "rediska/common/Message.hpp"

// One global context kept alive as long as the server lives.
inline grpc::ServerContext& GlobalServerContext() {
    static grpc::ServerContext ctx;
    return ctx;
}

// The thing recieved from the completion queue in case of a request.
struct BaseRequestManager {
    virtual void ListenForOne(grpc::ServerCompletionQueue& cq) = 0;
    virtual std::optional<QueueMessage> ConsumeMessage() = 0;
    virtual ~BaseRequestManager() = default;
};

// This is basically storage for an incoming request.
template <typename Derived, typename RequestT, typename ResponderT, typename ServiceT, auto RequestMethod>
class RequestManager : public BaseRequestManager {
protected:
    RequestT request;
    std::unique_ptr<ResponderT> responder;
    ServiceT& service;

    std::unique_ptr<grpc::internal::ServerAsyncStreamingInterface> TakeResponder() {
        return std::unique_ptr<grpc::internal::ServerAsyncStreamingInterface>(std::move(responder));
    }

public:
    explicit RequestManager(ServiceT& svc) : service(svc) { }

    // Sets up listening for a new request.
    // You must ensure this object lives until the request is consumed, or grpc will be unhappy.
    // The tag you recieve from the queue is a EventVariant* that you must take ownership of.
    void ListenForOne(grpc::ServerCompletionQueue& cq) override {
        request = RequestT{};
        // FIXME: just leak this stupid shit for now idk how to fix I'm done with this stupid language
        auto* ctx = new grpc::ServerContext();
        responder = std::make_unique<ResponderT>(ctx);
        (service.*RequestMethod)(ctx, &request, responder.get(), &cq, &cq, std::make_unique<EventVariant>(RequestEvent{*this}).release());
    }

    std::optional<QueueMessage> ConsumeMessage() override {
        QueueMessage msg = static_cast<Derived*>(this)->BuildMessage();
        return msg;
    }
};
