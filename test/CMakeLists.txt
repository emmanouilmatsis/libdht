include_directories(${GMOCK_INCLUDE_DIRS})

file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/test/*_test.cpp)
add_executable(libdht_test ${TEST_SRC_FILES})

add_dependencies(libdht_test gmock)
target_link_libraries(libdht_test libdht ${GMOCK_BOTH_LIBRARIES})

add_test(test libdht_test)
