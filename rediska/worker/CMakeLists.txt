add_library(worker STATIC
    tmp.cpp
    # Исходные файлы
)

target_link_libraries(worker PUBLIC
    common
)
