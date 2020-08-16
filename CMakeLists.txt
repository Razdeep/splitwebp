cmake_minimum_required(VERSION 3.0)
project(splitwebp)
set(CMAKE_CXX_STANDARD 11)
find_package(OpenCV REQUIRED)

include_directories("include")
file(GLOB_RECURSE sources "src/*.cpp")

add_executable(splitwebp main.cpp ${sources})
target_link_libraries(splitwebp ${OpenCV_LIBS})