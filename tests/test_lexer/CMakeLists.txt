cmake_minimum_required(VERSION 3.21)

project(test_lexer)

#add_subdirectory(../../examples/example1.txt)

set(
        SOURCES
        test_lexer.cpp
)

set(
        HEADERS
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} token)
target_link_libraries(${PROJECT_NAME} lexer)