cmake_minimum_required(VERSION 3.10)

project(geometry VERSION 1.0)

# settings

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(CMAKE_BUILD_TYPE "Release")

# main

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/main.cpp)

# install

set(CMAKE_INSTALL_PREFIX /usr/local)

file(GLOB HEADERS ${CMAKE_SOURCE_DIR}/include/*)

install(FILES ${HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/geometry)
