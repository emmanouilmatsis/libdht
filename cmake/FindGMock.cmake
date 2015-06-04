include(ExternalProject)

ExternalProject_Add(gmock
    SVN_REPOSITORY http://googlemock.googlecode.com/svn/trunk
    INSTALL_COMMAND ""
)

ExternalProject_Get_Property(gmock SOURCE_DIR)
set(GMOCK_INCLUDE_DIRS ${SOURCE_DIR}/gtest/include ${SOURCE_DIR}/include)

ExternalProject_Get_Property(gmock BINARY_DIR)
set(GMOCK_BOTH_LIBRARIES ${BINARY_DIR}/libgmock.a ${BINARY_DIR}/libgmock_main.a)
