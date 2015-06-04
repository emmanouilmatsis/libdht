include(ExternalProject)

ExternalProject_Add(gtest
    SVN_REPOSITORY http://googletest.googlecode.com/svn/trunk
    PREFIX "${CMAKE_CURRENT_BINARY_DIR}"
    INSTALL_COMMAND ""
)

ExternalProject_Get_Property(gtest SOURCE_DIR)
set(GTEST_INCLUDE_DIRS ${SOURCE_DIR}/include)

ExternalProject_Get_Property(gtest BINARY_DIR)
set(GTEST_BOTH_LIBRARIES ${BINARY_DIR}/libgtest.a ${BINARY_DIR}/libgtest_main.a)
