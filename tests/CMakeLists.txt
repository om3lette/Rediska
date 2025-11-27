add_executable(unit_tests
    main.cpp
    t.cpp
)

target_link_libraries(unit_tests
    PRIVATE
        worker
        cache
        frontend
        doctest::doctest
)
