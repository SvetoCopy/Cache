cmake_minimum_required(VERSION 3.10)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(pca_proj VERSION 1.0)

#file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(PCA_CACHE main.cpp)

target_include_directories(PCA_CACHE PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(PCA_UNIT_TEST src/tests.cpp)
target_include_directories(PCA_UNIT_TEST PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(PCA_UNIT_TEST gtest gmock pthread)