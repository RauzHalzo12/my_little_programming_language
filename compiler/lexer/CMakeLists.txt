cmake_minimum_required(VERSION 3.21)

project(lexer)

set(CMAKE_CXX_STANDARD 20)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost 1.77 COMPONENTS regex)

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
        profile.h)

add_library(${PROJECT_NAME} ${HEADERS} ${SOURCES})
target_link_libraries(${PROJECT_NAME} token)
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})