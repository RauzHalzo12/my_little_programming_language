cmake_minimum_required(VERSION 3.21)

project(test_lexer)

set(
        SOURCES
        test_lexer.cpp
)

set(
        HEADERS
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
