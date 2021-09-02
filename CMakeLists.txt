cmake_minimum_required(VERSION 3.19)
project(RSA)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

set(CMAKE_C_FLAGS "-std=c99")

add_executable(RSA
        main.c src/utils.c)

target_link_libraries(RSA gmp)