cmake_minimum_required(VERSION 3.21)
project(pupupu)

set(CMAKE_CXX_STANDARD 17)


add_subdirectory(token)
include_directories(token)

add_subdirectory(lexer)

set(
        SOURCES
        main.cpp
)

set(
        HEADERS
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} token)