cmake_minimum_required(VERSION 3.10)

project(StrikeEngine)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/release)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build." FORCE)
  message(STATUS "Release Build")
endif()

if(NOT (CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "Release"))
  message(FATAL_ERROR "Invalid build type: ${CMAKE_BUILD_TYPE}. Allowed types: Debug or Release only.")
endif()

#TODO!!! include platform exclusive code instead of including code from all platforms
file(GLOB_RECURSE SOURCES 
    "src/Core/*.cpp"
    "src/Core/*.h"
    "src/Platforms/*.cpp"
    "src/Platforms/*.h"
    
    "Dependencies/Vendor/entt/*.cpp"
    "Dependencies/Vendor/entt/*.h"
    "Dependencies/Vendor/glm/*.cpp"
    "Dependencies/Vendor/glm/*.h"
    "Dependencies/Vendor/stbImage/*.cpp"
    "Dependencies/Vendor/stbImage/*.h"
)

add_library(StrikeEngine 
    ${SOURCES}
)

add_subdirectory("Dependencies/Vendor/GLFW/glfw")
add_subdirectory("Dependencies/Vendor/glad")

find_package(OpenGL REQUIRED)
target_link_libraries(StrikeEngine PRIVATE OpenGL::GL)
target_link_libraries(StrikeEngine PRIVATE glfw)
target_link_libraries(StrikeEngine PRIVATE Glad)

target_include_directories(StrikeEngine PRIVATE 
    Dependencies/Vendor/GLFW/glfw/include
    Dependencies/Vendor/glad/include
    Dependencies/Vendor/stbImage
    Dependencies/Vendor/glm
    Dependencies/Vendor/entt/include
    src/Core
    src/Platforms
)


if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(StrikeEngine PRIVATE STRIKE_DEBUG)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(StrikeEngine PRIVATE STRIKE_RELEASE)
endif()

#TODO!!! Seperate into respective OS Windowing definitions if/when support for those platforms exist (include the commented code below)
target_compile_definitions(StrikeEngine PRIVATE STRIKE_GLFW)
#if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
#   target_compile_definitions(StrikeEngine PRIVATE STRIKE_LINUX)
#elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
#   target_compile_definitions(StrikeEngine PRIVATE STRIKE_WINDOWS)
#endif()

target_precompile_headers(StrikeEngine PRIVATE
    src/Core/StrikePCH.h
)