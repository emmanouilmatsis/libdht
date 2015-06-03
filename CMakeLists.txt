cmake_minimum_required(VERSION 2.8.8 FATAL_ERROR)

project(libdht C CXX)

set(libdht_VERSION_MAJOR 0)
set(libdht_VERSION_MINOR 1)
set(libdht_VERSION_PATCH 0)

enable_testing()

#find_package(Threads REQUIRED)
#set(CMAKE_CXX_FLAGS "-std=c++14 -Wall -pthread")

set(CMAKE_CXX_FLAGS "-std=c++14 -Wall")

include_directories(${PROJECT_SOURCE_DIR}/include)

add_subdirectory(${PROJECT_SOURCE_DIR}/src)
add_subdirectory(${PROJECT_SOURCE_DIR}/test)
add_subdirectory(${PROJECT_SOURCE_DIR}/ext/gtest)


# Test
include_directories(${GTEST_INCLUDE_DIRS})

set(PROJECT_TEST_NAME ${PROJECT_NAME_STR}_test)
file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/test/*_test.cpp)
add_executable(${PROJECT_TEST_NAME} ${TEST_SRC_FILES})

#add_executable(dhttest ${PROJECT_SOURCE_DIR}/test/*_test.cpp)
add_dependencies(dhttest googletest)
target_link_libraries(dhttest
    ${GTEST_LIBS_DIR}/libgtest.a
    ${GTEST_LIBS_DIR}/libgtest_main.a
    #${CMAKE_THREAD_LIBS_INIT}
    )

add_test(test1 dhttest)
