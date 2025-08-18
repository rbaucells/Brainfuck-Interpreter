cmake_minimum_required(VERSION 4.0)
project(untitled)
set(CMAKE_CXX_STANDARD 20)

add_executable(untitled display.cpp common.h gl.c tito.cpp)
target_include_directories(untitled PRIVATE include)

target_link_libraries(untitled PRIVATE ${PROJECT_SOURCE_DIR}/lib/libglfw3.a "-framework Cocoa" "-framework IOKit" "-framework CoreFoundation")