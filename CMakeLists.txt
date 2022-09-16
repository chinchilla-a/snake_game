cmake_minimum_required(VERSION 3.23)
project(snake)

set(CMAKE_CXX_STANDARD 14)

add_executable(snake main.cpp snake.cpp snake.h)

add_library(default INTERFACE)
target_compile_features(default INTERFACE cxx_std_17)
enable_testing()

# Taken from homework files
add_library(doctest STATIC external/doctest.cpp)
target_include_directories(doctest PUBLIC external/ )
set_target_properties(doctest PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED ON)
add_library(doctest::doctest ALIAS doctest)
add_library(Catch2::Catch2 ALIAS doctest)

add_executable(project-tests tests/test_snake.cpp snake.cpp)
target_link_libraries(project-tests PUBLIC doctest default)
add_test(NAME project-tests COMMAND project-tests --force-colors -d)