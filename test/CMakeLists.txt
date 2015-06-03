add_subdirectory(${PROJECT_SOURCE_DIR}/ext/gtest ${CMAKE_BINARY_DIR}/googletest)

include_directories(${GTEST_INCLUDE_DIRS})

file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/test/*_test.cpp)
add_executable(libdht_test ${TEST_SRC_FILES})
add_dependencies(libdht_test googletest)
target_link_libraries(libdht_test ${GTEST_LIBS_DIR}/libgtest.a ${GTEST_LIBS_DIR}/libgtest_main.a ${CMAKE_THREAD_LIBS_INIT})

add_test(test libdht_test)
