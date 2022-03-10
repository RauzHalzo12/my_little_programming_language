cmake_minimum_required(VERSION 3.21)

project(MY_LITTLE_PROGRAMMING_LANGUAGE)



set(CMAKE_CXX_FLAGS -O3)
add_subdirectory(compiler build/compiler)
add_subdirectory(tests build/tests)