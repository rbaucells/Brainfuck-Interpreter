cmake_minimum_required(VERSION 4.0)
project(bf-interpreter)
set(CMAKE_CXX_STANDARD 20)

add_executable(bf-interpreter display.cpp common.h tito.cpp)
target_include_directories(bf-interpreter PRIVATE dependencies/include)

target_link_libraries(bf-interpreter PRIVATE ${PROJECT_SOURCE_DIR}/dependencies/lib/glfw/libglfw3.a "-framework Cocoa" "-framework IOKit" "-framework CoreFoundation")
target_link_libraries(bf-interpreter PRIVATE ${PROJECT_SOURCE_DIR}/dependencies/lib/glad/libglad.a)