cmake_minimum_required(VERSION 3.5)

project(cpp_playground)
set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE cpps *.cpp)
file(GLOB_RECURSE hpps *.h *.hpp)

include_directories(${CMAKE_SOURCE_DIR})
add_executable(cpp_playground src/main.cpp)