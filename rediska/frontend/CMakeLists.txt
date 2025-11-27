add_library(frontend STATIC
    tmp.cpp
    # Исходные файлы
)

target_link_libraries(frontend PUBLIC
    common
)
