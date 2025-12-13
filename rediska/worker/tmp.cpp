#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <grpcpp/grpcpp.h>
#include "google/protobuf/empty.pb.h"
#include "v1/primitives/bool.grpc.pb.h"
#include "v1/primitives/int.grpc.pb.h"
#include "v1/primitives/string.grpc.pb.h"
#include "v1/collections/list.grpc.pb.h"
#include "rediska/common/Message.hpp"
#include "rediska/frontend/RequestManager.hpp"
#include "rediska/frontend/server.hpp"

namespace {
class PrintWorker {
public:
    void Enqueue(QueueMessage msg) {
        std::lock_guard lock(mtx_);
        queue_.push(std::move(msg));
        cv_.notify_one();
    }

    void Run() {
        for (;;) {
            QueueMessage msg;
            {
                std::unique_lock lock(mtx_);
                cv_.wait(lock, [&] { return !queue_.empty(); });
                msg = std::move(queue_.front());
                queue_.pop();
            }

            std::cout << "[worker] key=" << msg.key
                      << " type=" << static_cast<int>(msg.type)
                      << " op=" << static_cast<int>(msg.operation) << std::endl;

            if (!msg.responder) continue;

            switch (msg.operation) {
                case OperationId::SET:
                case OperationId::DELETE: {
                    msg.respond<google::protobuf::Empty>(google::protobuf::Empty{});
                    break;
                }
                case OperationId::GET: {
                    if (msg.type == CacheValueId::BOOLEAN) {
                        v1::primitives::boolean::BoolGetResponse r; r.set_value(false);
                        msg.respond<v1::primitives::boolean::BoolGetResponse>(r);
                    } else if (msg.type == CacheValueId::INT) {
                        v1::primitives::integer::IntGetResponse r; r.set_value(0);
                        msg.respond<v1::primitives::integer::IntGetResponse>(r);
                    } else if (msg.type == CacheValueId::STRING) {
                        v1::primitives::str::StringGetResponse r; r.set_value("test");
                        msg.respond<v1::primitives::str::StringGetResponse>(r);
                    } else if (msg.type == CacheValueId::ARRAY) {
                        v1::collections::list::ListGetResponse r;
                        // no elements
                        msg.respond<v1::collections::list::ListGetResponse>(r);
                    }
                    break;
                }
                default:
                    break;
            }
        }
    }

private:
    std::queue<QueueMessage> queue_;
    std::mutex mtx_;
    std::condition_variable cv_;
};
} // namespace

int run_print_server() {
    PrintWorker worker;
    std::thread t([&] { worker.Run(); });

    RunFrontendServer("0.0.0.0:50051", [&](QueueMessage msg) {
        worker.Enqueue(std::move(msg));
    });

    t.join();
    return 0;
}
