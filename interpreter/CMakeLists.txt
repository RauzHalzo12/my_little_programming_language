cmake_minimum_required(VERSION 3.21)

project(INTERPRETER)
set(CMAKE_CXX_STANDARD 17)

set(
        SOURCES
        main.cpp
)

set(
        HEADERS
        interpreter.h interpreter.cpp variable.h)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})