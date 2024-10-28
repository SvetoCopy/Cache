cmake_minimum_required(VERSION 3.10)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(pca_proj VERSION 1.0)

add_executable(UNIT_TEST src/tests.cpp)
target_include_directories(UNIT_TEST PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../LFU/include ${CMAKE_CURRENT_SOURCE_DIR}/../PCA/include)

target_link_libraries(UNIT_TEST gtest gmock pthread)