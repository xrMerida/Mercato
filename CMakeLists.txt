cmake_minimum_required(VERSION 3.21)
project(Mercato)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB SOURCES src/*.cpp)
add_executable(mercato ${SOURCES})
target_include_directories(mercato PRIVATE include/mercato)
