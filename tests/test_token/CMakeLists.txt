cmake_minimum_required(VERSION 3.21)

project(test_token)

set(
        SOURCES
        test_token.cpp
)

set(
        HEADERS
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
