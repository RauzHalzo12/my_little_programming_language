cmake_minimum_required(VERSION 3.21)

project(INTERPRETER)
set(CMAKE_CXX_STANDARD 20)


add_subdirectory(parsers)
include_directories(parsers)

set(
        SOURCES
        main.cpp
        virtual_machine.cpp
        object.cpp
)

set(
        HEADERS
        virtual_machine.h
        object.h
        instructions.h
)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})
target_link_libraries(${PROJECT_NAME} parsing_stuff)