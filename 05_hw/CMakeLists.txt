cmake_minimum_required(VERSION 3.13)
project(stack C)

option(ENABLE_SANITIZERS "Enable runtime sanitizers (ASan, UBSan, LSan)" OFF)

message(STATUS "C compiler id: ${CMAKE_C_COMPILER_ID}")
message(STATUS "C compiler: ${CMAKE_C_COMPILER}")

set(SANITIZE_COMPILE_FLAGS_CLANG_GCC
    -fsanitize=address
    -fsanitize=undefined
    -fsanitize=leak
    -fno-omit-frame-pointer
)
set(SANITIZE_LINK_FLAGS_CLANG_GCC
    -fsanitize=address
    -fsanitize=undefined
    -fsanitize=leak
)

set(SANITIZE_COMPILE_FLAGS_MSVC
    /fsanitize=address
)
set(SANITIZE_LINK_FLAGS_MSVC
    /fsanitize=address
)

add_library(stack stack.c)

add_executable(main main.c)
add_executable(tests tests.c)
add_executable(bench bench.c)

target_link_libraries(main PRIVATE stack)
target_link_libraries(tests PRIVATE stack)
target_link_libraries(bench PRIVATE stack)

if(ENABLE_SANITIZERS)
    message(STATUS "Sanitizers enabled")

    foreach(tgt IN ITEMS stack main tests bench)
        if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
            target_compile_options(${tgt} PRIVATE ${SANITIZE_COMPILE_FLAGS_CLANG_GCC})
            target_link_options(${tgt} PRIVATE ${SANITIZE_LINK_FLAGS_CLANG_GCC})
        elseif(CMAKE_C_COMPILER_ID STREQUAL "MSVC")
            target_compile_options(${tgt} PRIVATE ${SANITIZE_COMPILE_FLAGS_MSVC})
            target_link_options(${tgt} PRIVATE ${SANITIZE_LINK_FLAGS_MSVC})
        else()
            message(WARNING "Unknown compiler ${CMAKE_C_COMPILER_ID}; sanitizers not applied")
        endif()
    endforeach()

else()
    message(STATUS "Sanitizers disabled")
endif()

set(CMAKE_C_CLANG_TIDY clang-tidy)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
