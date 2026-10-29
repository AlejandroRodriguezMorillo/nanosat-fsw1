
cmake_minimum_required(VERSION 3.16)
project(nanosat-fsw C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -Wpedantic -Werror)

add_executable(nanosat src/app/main.c)
target_include_directories(nanosat PRIVATE src/core)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)