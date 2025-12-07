cmake_minimum_required(VERSION 3.15)
project(RediskaFrontend)

add_library(frontend STATIC tmp.cpp)

include(FetchContent)

FetchContent_Declare(
    Protobuf
    GIT_REPOSITORY https://github.com/protocolbuffers/protobuf.git
    GIT_TAG v33.2
    SOURCE_SUBDIR cmake
)
set(protobuf_BUILD_TESTS OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(Protobuf)

set(gRPC_ABSL_PROVIDER "package")
set(gRPC_CARES_PROVIDER "package")
set(gRPC_PROTOBUF_PROVIDER "package")
set(gRPC_RE2_PROVIDER "package")
set(gRPC_SSL_PROVIDER "package")
set(gRPC_ZLIB_PROVIDER "package")

FetchContent_Declare(
    gRPC
    GIT_REPOSITORY https://github.com/grpc/grpc
    GIT_TAG v1.76.0
)
FetchContent_MakeAvailable(gRPC) # Явно делаем gRPC доступным

# 3. Находим инструменты ДО генерации
find_package(Protobuf REQUIRED)

set(PROTOS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../proto)
file(GLOB_RECURSE PROTO_FILES ${PROTOS_DIR}/*.proto)

set(GENERATED_DIR ${CMAKE_CURRENT_BINARY_DIR}/generated)

foreach(PROTO_FILE ${PROTO_FILES})
    file(RELATIVE_PATH REL_PROTO_PATH ${PROTOS_DIR} ${PROTO_FILE})
    get_filename_component(REL_DIR ${REL_PROTO_PATH} DIRECTORY)
    get_filename_component(BASE_NAME ${REL_PROTO_PATH} NAME_WE)

    if(REL_DIR)
        set(PROTO_SRC "${GENERATED_DIR}/${REL_DIR}/${BASE_NAME}.pb.cc")
        set(PROTO_HDR "${GENERATED_DIR}/${REL_DIR}/${BASE_NAME}.pb.h")
        set(GRPC_SRC "${GENERATED_DIR}/${REL_DIR}/${BASE_NAME}.grpc.pb.cc")
        set(GRPC_HDR "${GENERATED_DIR}/${REL_DIR}/${BASE_NAME}.grpc.pb.h")
    else()
        set(PROTO_SRC "${GENERATED_DIR}/${BASE_NAME}.pb.cc")
        set(PROTO_HDR "${GENERATED_DIR}/${BASE_NAME}.pb.h")
        set(GRPC_SRC "${GENERATED_DIR}/${BASE_NAME}.grpc.pb.cc")
        set(GRPC_HDR "${GENERATED_DIR}/${BASE_NAME}.grpc.pb.h")
    endif()

    get_filename_component(OUT_DIR ${PROTO_SRC} DIRECTORY)
    file(MAKE_DIRECTORY ${OUT_DIR})

    message(STATUS ${GENERATED_DIR})

    execute_process(
        COMMAND protoc
        --proto_path=${PROTOS_DIR}
        --proto_path=${Protobuf_INCLUDE_DIRS}
        --proto_path=${gRPC_INCLUDE_DIRS}
        --cpp_out=${GENERATED_DIR}
        ${REL_PROTO_PATH}
    )

    list(APPEND GENERATED_SOURCES ${PROTO_SRC} ${GRPC_SRC})
endforeach()

add_custom_target(generate_grpc_code ALL
    DEPENDS ${GENERATED_SOURCES}
)

add_dependencies(frontend generate_grpc_code)

target_link_libraries(frontend PUBLIC
    common
    grpc++
    protobuf::libprotobuf
)