add_library(frontend STATIC
    tmp.cpp
    # Source files
)

include(FetchContent)

set(ABSL_ENABLE_INSTALL ON)
FetchContent_Declare(
    gRPC
    GIT_REPOSITORY https://github.com/grpc/grpc
    GIT_TAG v1.76.0
)

FetchContent_MakeAvailable(gRPC)

target_link_libraries(frontend PUBLIC
    common
    gRPC
)
