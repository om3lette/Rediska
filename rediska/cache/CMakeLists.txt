add_library(cache STATIC
    lru/LRU.cpp
)

target_link_libraries(cache PUBLIC
    common
)
