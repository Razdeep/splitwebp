cmake_minimum_required(VERSION 3.0)
project(splitwebp)
set(CMAKE_CXX_STANDARD 11)
find_package(OpenCV REQUIRED)

if (APPLE)
    message(STATUS "Detected Operating System: Mac OS")
    link_directories("3rdparty/libwebp/lib/mac")
elseif (UNIX)
    message(STATUS "Detected Operating System: Linux")
    link_directories("3rdparty/libwebp/lib/linux")
elseif (WIN32)
    message(STATUS "Detected Operating System: Windows")
    link_directories("vcpkg/installed/x64-windows/lib")
else ()
    message(FATAL_ERROR "Detected Operating System: Unknown")
endif()

include_directories("3rdparty/libwebp/include")

include_directories("include")
file(GLOB_RECURSE sources "src/*.cpp")

add_executable(splitwebp main.cpp ${sources})
target_link_libraries(splitwebp ${OpenCV_LIBS})
if (WIN32)
    target_link_libraries(splitwebp webp webpdemux libwebpmux webpdecoder pthreadVC3)
else ()
    target_link_libraries(splitwebp webp webpdemux pthread)
endif()

# add unit tests
enable_testing()

option(BUILD_TESTS "Build all tests" OFF)
if (BUILD_TESTS)
    add_subdirectory(test)
endif()
