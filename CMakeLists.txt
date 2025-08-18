cmake_minimum_required(VERSION 4.0)
project(untitled)
set(CMAKE_CXX_STANDARD 20)

add_executable(untitled tito.cpp display.cpp common.h main.cpp)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(untitled PRIVATE glfw3)