include(ExternalProject)

ExternalProject_Add(googletest
    SVN_REPOSITORY http://googletest.googlecode.com/svn/trunk
    CMAKE_ARGS -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG:PATH=DebugLibs
               -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE:PATH=ReleaseLibs
               -DCMAKE_CXX_FLAGS=${MSVC_COMPILER_DEFS}
               -Dgtest_force_shared_crt=ON
    PREFIX "${CMAKE_CURRENT_BINARY_DIR}"
    INSTALL_COMMAND ""
)

# Specify include dir
ExternalProject_Get_Property(googletest source_dir)
set(GTEST_INCLUDE_DIRS ${source_dir}/include)

# Specify MainTest's link libraries
ExternalProject_Get_Property(googletest binary_dir)
set(GTEST_LIBS_DIR ${binary_dir})
