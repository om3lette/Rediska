add_library(common STATIC
    tmp.cpp
)

find_package(concurrentqueue REQUIRED)

target_link_libraries(common
    PUBLIC
    spdlog::spdlog
    concurrentqueue
)