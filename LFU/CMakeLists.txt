cmake_minimum_required(VERSION 3.10)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(lfu_proj VERSION 1.0)

#file(GLOB_RECURSE SRC_FILES src/*.cpp)

add_executable(LFU_CACHE main.cpp )
target_include_directories(LFU_CACHE PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)