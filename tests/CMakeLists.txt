cmake_minimum_required(VERSION 3.21)
project(compiler_tests)

set(CMAKE_CXX_STANDARD 20)

include_directories(libs)
include_directories(../)


add_subdirectory(test_lexer)
add_subdirectory(test_token)