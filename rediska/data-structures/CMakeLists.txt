add_library(data-structures STATIC
    impl/ListDataStructure.cpp
)

target_link_libraries(data-structures PUBLIC
    common
)
