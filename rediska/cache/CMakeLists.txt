add_library(cache STATIC
    tmp.cpp
    # Исходные файлы
)

target_link_libraries(cache PUBLIC
    common
)
