cmake_minimum_required(VERSION 3.21)

project(token)

set(CMAKE_CXX_STANDARD 17)



set(
        SOURCES
        token.cpp
)

set(
        HEADERS
        token.h
)

add_library(${PROJECT_NAME} ${SOURCES} ${HEADERS})