cmake_minimum_required(VERSION 3.10)

project(geometry VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE "Release")

add_subdirectory(${CMAKE_SOURCE_DIR}/src)

set(BUILD_TEST ON)

if(BUILD_TEST)
    add_subdirectory(${CMAKE_SOURCE_DIR}/test)
endif()

set(CMAKE_INSTALL_PREFIX /usr/local)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/src/include/ DESTINATION include/artwork/geometry)