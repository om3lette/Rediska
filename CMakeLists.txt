cmake_minimum_required(VERSION 3.28)
project(Rediska)

set(CMAKE_CXX_STANDARD 23)

if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Werror)
endif()

include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.11.0
)
FetchContent_MakeAvailable(Catch2)

add_executable(Rediska rediska/main.cpp)
add_executable(tests tests/example_test.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)