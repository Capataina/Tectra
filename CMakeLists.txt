cmake_minimum_required(VERSION 3.20)
project(tectra VERSION 0.1.0 LANGUAGES CXX)

# Use C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compiler warnings - be strict from day one
add_compile_options(-Wall -Wextra -Wpedantic -Werror)

# Build the main executable
add_executable(tectra src/main.cpp)
