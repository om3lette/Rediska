add_library(frontend STATIC tmp.cpp)

# Find packages
find_package(Protobuf REQUIRED CONFIG)
find_package(gRPC REQUIRED CONFIG)

set(PROTO_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../proto")

# Define the proto files
set(PROTO_FILES
    "${PROTO_ROOT_DIR}/v1/collections/common.proto"
    "${PROTO_ROOT_DIR}/v1/collections/element_kind.proto"
    "${PROTO_ROOT_DIR}/v1/collections/list.proto"
    "${PROTO_ROOT_DIR}/v1/object/object.proto"
    "${PROTO_ROOT_DIR}/v1/primitives/bool.proto"
    "${PROTO_ROOT_DIR}/v1/primitives/float.proto"
    "${PROTO_ROOT_DIR}/v1/primitives/int.proto"
    "${PROTO_ROOT_DIR}/v1/primitives/string.proto"
)

# This allows protobuf_generate to find them when inspecting the target.
target_sources(frontend PRIVATE ${PROTO_FILES})

# Include directories
# We include the binary dir (for generated .pb.h files) and the root (for imports)
target_include_directories(frontend PUBLIC
    "${CMAKE_CURRENT_BINARY_DIR}"
    "${PROTO_ROOT_DIR}"
)

# Generate Standard Protobuf files (.pb.cc / .pb.h)
# We use 'protobuf_generate' instead of the legacy 'protobuf_generate_cpp'.
# It automatically adds the generated C++ files back into the 'frontend' target.
protobuf_generate(
    TARGET frontend
    LANGUAGE cpp
    IMPORT_DIRS "${PROTO_ROOT_DIR}"
    PROTOC_OUT_DIR "${CMAKE_CURRENT_BINARY_DIR}"
)

# Generate gRPC specific files (.grpc.pb.cc / .grpc.pb.h)
protobuf_generate(
    TARGET frontend
    LANGUAGE grpc
    GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc
    PLUGIN "protoc-gen-grpc=$<TARGET_FILE:gRPC::grpc_cpp_plugin>"
    IMPORT_DIRS "${PROTO_ROOT_DIR}"
    PROTOC_OUT_DIR "${CMAKE_CURRENT_BINARY_DIR}"
)

target_link_libraries(frontend
    PUBLIC
    gRPC::grpc++
    protobuf::libprotobuf
)