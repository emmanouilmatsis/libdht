cmake_minimum_required(VERSION 2.8.8 FATAL_ERROR)

project(libdht C CXX)

set(libdht_VERSION_MAJOR 0)
set(libdht_VERSION_MINOR 1)
set(libdht_VERSION_PATCH 0)

find_package(Threads REQUIRED)

set(CMAKE_CXX_FLAGS "-std=c++14 -Wall -pthread")

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

enable_testing()
include(FindGMock)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_subdirectory(${PROJECT_SOURCE_DIR}/src)
add_subdirectory(${PROJECT_SOURCE_DIR}/test)
