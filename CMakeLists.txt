cmake_minimum_required(VERSION 3.0)
project(splitwebp)
set(CMAKE_CXX_STANDARD 11)
find_package(OpenCV REQUIRED)

# Enabled the ExternalProject module
INCLUDE(ExternalProject)
SET_DIRECTORY_PROPERTIES(PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/third_party)

if (APPLE)
    message(STATUS "Detected Operating System: Mac OS")
    link_directories("3rdparty/libwebp/lib/mac")
elseif (UNIX)
    message(STATUS "Detected Operating System: Linux")
    link_directories("3rdparty/libwebp/lib/linux")
elseif (WIN32)
    message(STATUS "Detected Operating System: Windows")
else ()
    message(FATAL_ERROR "Detected Operating System: Unknown")
endif()

# Add gtest
ExternalProject_add(
	gtest
	URL http://googletest.googlecode.com/files/gtest-1.10.0.zip
	INSTALL_COMMAND ""
	LOG_DOWNLOAD ON
	LOG_CONFIGURE ON
	LOG_BUILD ON
)

# Specify include dir
ExternalProject_Get_Property(googletest source_dir)
set(GTEST_INCLUDE_DIR ${source_dir}/include)

# Library
ExternalProject_Get_Property(googletest binary_dir)
set(GTEST_LIBRARY_PATH ${binary_dir}/${CMAKE_FIND_LIBRARY_PREFIXES}gtest.a)
add_library(${GTEST_LIBRARY} UNKNOWN IMPORTED)
set_property(splitwebp {GTEST_LIBRARY} PROPERTY IMPORTED_LOCATION
                ${GTEST_LIBRARY_PATH} )

include_directories("3rdparty/libwebp/include")

include_directories("include")
file(GLOB_RECURSE sources "src/*.cpp")

add_executable(splitwebp main.cpp ${sources})
target_link_libraries(splitwebp ${OpenCV_LIBS})
target_link_libraries(splitwebp webp webpdemux pthread)
