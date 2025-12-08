add_library(frontend STATIC tmp.cpp)

find_package(Protobuf REQUIRED)
find_package(gRPC REQUIRED)

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
        --plugin=protoc-gen-grpc=$<TARGET_FILE:gRPC::grpc_cpp_plugin>
        -I ${PROTO_ROOT_DIR}
        ${PROTO_FILE}
        DEPENDS ${PROTO_FILE} protobuf::protoc gRPC::grpc_cpp_plugin
        COMMENT "Generating gRPC code for ${PROTO_FILE_REL}"
        VERBATIM
    )

    list(APPEND GENERATED_SRCS ${OUT_PB_CC} ${OUT_PB_H} ${OUT_GRPC_CC} ${OUT_GRPC_H})
endforeach ()

target_sources(frontend PRIVATE ${GENERATED_SRCS})
target_include_directories(frontend PUBLIC ${PROTO_GEN_DIR})

target_link_libraries(frontend
    PUBLIC
    gRPC::grpc++
    protobuf::libprotobuf
)