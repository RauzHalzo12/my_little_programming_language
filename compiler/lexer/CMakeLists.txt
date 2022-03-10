cmake_minimum_required(VERSION 3.21)

project(lexer)

set(CMAKE_CXX_STANDARD 20)

find_package(Boost 1.45 COMPONENTS regex REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
set(
        SOURCES
        #test_lexer.cpp
        lexer.cpp
        token_recognizer.cpp
)

set(
        HEADERS
        lexer.h
        rules.h
)

add_library(${PROJECT_NAME} ${HEADERS} ${SOURCES})
target_link_libraries(${PROJECT_NAME} token)
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
