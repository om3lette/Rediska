cmake_minimum_required(VERSION 3.28)
project(Rediska)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Werror)
endif()

include(FetchContent)

FetchContent_Declare(
    doctest
    GIT_REPOSITORY https://github.com/doctest/doctest.git
    GIT_TAG v2.4.12
)
FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.16.0
)

FetchContent_MakeAvailable(doctest)
FetchContent_MakeAvailable(spdlog)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(rediska)

enable_testing()
add_subdirectory(tests)
