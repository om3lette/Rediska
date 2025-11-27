cmake_minimum_required(VERSION 3.28)
project(Rediska)

set(CMAKE_CXX_STANDARD 23)

# Подключение модуля для загрузки зависимостей
include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.11.0
)
FetchContent_MakeAvailable(Catch2)

add_executable(Rediska main.cpp)
