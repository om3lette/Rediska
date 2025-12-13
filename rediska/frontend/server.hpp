#pragma once

#include <functional>
#include <string>
#include "rediska/common/Message.hpp"

// Starts the gRPC frontend server on the given address and blocks.
// Each incoming request is transformed into a QueueMessage with its responder
// moved inside; the provided callback decides when/how to finish it.
void RunFrontendServer(const std::string& address,
                       std::function<void(QueueMessage)> on_request);
