cmake_minimum_required(VERSION 3.10)
project(Glad)

set(CMAKE_CXX_STANDARD 20)

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/debug)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/release)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build." FORCE)
  message(STATUS "Release Build")
endif()

if(NOT (CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "Release"))
  message(FATAL_ERROR "Invalid build type: ${CMAKE_BUILD_TYPE}. Allowed types: Debug or Release only.")
endif()

add_library(Glad
    include/glad/glad.h
    include/KHR/khrplatform.h
    src/glad.c
)

target_include_directories(Glad PRIVATE include)