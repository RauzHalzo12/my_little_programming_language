cmake_minimum_required(VERSION 3.21)
project(dsl)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS -Ofast)

find_package(Boost COMPONENTS regex REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

add_executable(dsl main.cpp token.h token.cpp)

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})