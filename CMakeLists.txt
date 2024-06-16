cmake_minimum_required(VERSION 3.11)

project(pseudo-terminal)

set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_STANDARD 20)

set(PROJECT_ROOT_DIR    ${PROJECT_SOURCE_DIR})

set(PROJECT_INCLUDE_DIR ${PROJECT_ROOT_DIR}/include)
set(PROJECT_LIB_DIR     ${PROJECT_ROOT_DIR}/lib)
set(PROJECT_SOURCE_DIR  ${PROJECT_ROOT_DIR}/src)

add_subdirectory(${PROJECT_LIB_DIR})

add_subdirectory(${PROJECT_ROOT_DIR}/test)
