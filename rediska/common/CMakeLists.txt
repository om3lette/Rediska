add_library(common STATIC
    tmp.cpp
    # Исходные файлы
)

target_link_libraries(common
    PUBLIC
        spdlog::spdlog
)
