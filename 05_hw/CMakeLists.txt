cmake_minimum_required(VERSION 3.10)
project(stack)

add_library(stack stack.c)

add_executable(main main.c)
target_link_libraries(main stack)

add_executable(tests tests.c)
target_link_libraries(tests stack)

set(CMAKE_C_CLANG_TIDY clang-tidy)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
