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
else ()
    message(FATAL_ERROR "Detected Operating System: Unknown")
endif()

include_directories("3rdparty/libwebp/include")

include_directories("include")
file(GLOB_RECURSE sources "src/*.cpp")

add_executable(splitwebp main.cpp ${sources})
target_link_libraries(splitwebp ${OpenCV_LIBS})
target_link_libraries(splitwebp webp webpdemux pthread)

# add unit tests
enable_testing()
add_subdirectory(test)