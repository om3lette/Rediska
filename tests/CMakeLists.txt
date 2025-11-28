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

list(APPEND CMAKE_MODULE_PATH "${doctest_SOURCE_DIR}/scripts/cmake")
include(doctest)
list(POP_BACK CMAKE_MODULE_PATH)

doctest_discover_tests(unit_tests
    TEST_PREFIX ""
    TEST_SUFFIX ""
)

find_program(CPPCHECK_EXECUTABLE cppcheck)
if(CPPCHECK_EXECUTABLE)
    add_test(
        NAME static_analysis
        COMMAND ${CPPCHECK_EXECUTABLE}
            --enable=all
            --std=c++23
            --error-exitcode=1
            --inline-suppr
            ${CMAKE_SOURCE_DIR}/rediska
    )
    set_tests_properties(static_analysis PROPERTIES
        LABELS "static"
        TIMEOUT 120
    )
else()
    message(WARNING "Cppcheck not found — skipping static analysis test")
endif()
