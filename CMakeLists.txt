project(btree)

cmake_minimum_required(VERSION 3.0)

add_executable(btree main.c)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(btree PRIVATE -Wno-dangling-else)
endif()
