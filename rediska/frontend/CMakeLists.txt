add_library(frontend STATIC 
    bool_service.cpp
    int_service.cpp
    float_service.cpp
    string_service.cpp
    list_service.cpp
    object_service.cpp
)

set(ABSL_ENABLE_INSTALL ON)

set(protobuf_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(gRPC_BUILD_TESTS OFF CACHE BOOL "" FORCE)

include(FetchContent)

FetchContent_Declare(
    Protobuf
    GIT_REPOSITORY https://github.com/protocolbuffers/protobuf.git
    GIT_TAG v33.2
    SOURCE_SUBDIR cmake
)
FetchContent_MakeAvailable(Protobuf)

FetchContent_Declare(
    gRPC
    GIT_REPOSITORY https://github.com/grpc/grpc
    GIT_TAG v1.76.0
)
FetchContent_MakeAvailable(gRPC)

get_filename_component(PROTO_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../proto" ABSOLUTE)
set(PROTO_GEN_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")
file(MAKE_DIRECTORY ${PROTO_GEN_DIR})

file(GLOB_RECURSE PROTO_FILES "${PROTO_ROOT_DIR}/*.proto")

set(GENERATED_SRCS)

foreach (PROTO_FILE ${PROTO_FILES})
    file(RELATIVE_PATH PROTO_FILE_REL ${PROTO_ROOT_DIR} ${PROTO_FILE})

    get_filename_component(PROTO_FILE_DIR ${PROTO_FILE_REL} DIRECTORY)
    file(MAKE_DIRECTORY "${PROTO_GEN_DIR}/${PROTO_FILE_DIR}")

    string(REGEX REPLACE "\\.proto$" "" PROTO_FILE_WE ${PROTO_FILE_REL})

    set(OUT_PB_CC "${PROTO_GEN_DIR}/${PROTO_FILE_WE}.pb.cc")
    set(OUT_PB_H "${PROTO_GEN_DIR}/${PROTO_FILE_WE}.pb.h")
    set(OUT_GRPC_CC "${PROTO_GEN_DIR}/${PROTO_FILE_WE}.grpc.pb.cc")
    set(OUT_GRPC_H "${PROTO_GEN_DIR}/${PROTO_FILE_WE}.grpc.pb.h")

    add_custom_command(
        OUTPUT ${OUT_PB_CC} ${OUT_PB_H} ${OUT_GRPC_CC} ${OUT_GRPC_H}
        COMMAND protobuf::protoc
        ARGS
        --cpp_out=${PROTO_GEN_DIR}
        --grpc_out=${PROTO_GEN_DIR}
        --plugin=protoc-gen-grpc=$<TARGET_FILE:grpc_cpp_plugin>
        -I ${PROTO_ROOT_DIR}
        -I "${protobuf_SOURCE_DIR}/src"
        ${PROTO_FILE}
        DEPENDS ${PROTO_FILE} protobuf::protoc grpc_cpp_plugin
        COMMENT "Generating gRPC code for ${PROTO_FILE_REL}"
        VERBATIM
    )

    list(APPEND GENERATED_SRCS ${OUT_PB_CC} ${OUT_PB_H} ${OUT_GRPC_CC} ${OUT_GRPC_H})
endforeach ()

target_sources(frontend PRIVATE ${GENERATED_SRCS})
target_include_directories(frontend PUBLIC ${PROTO_GEN_DIR})

target_link_libraries(frontend
    PUBLIC
    grpc++
    protobuf::libprotobuf
)