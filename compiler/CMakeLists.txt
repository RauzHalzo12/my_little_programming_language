cmake_minimum_required(VERSION 3.21)

project(compiler)

set(CMAKE_CXX_STANDARD 20)


add_subdirectory(token)
include_directories(token)

add_subdirectory(lexer)
include_directories(lexer)

set(
        SOURCES
        main.cpp
)

set(
        HEADERS
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} token)
target_link_libraries(${PROJECT_NAME} lexer)
