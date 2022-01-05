cmake_minimum_required(VERSION 3.10)

project(testGeometry VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)

include_directories(../include
                    ./include
                    ${GTEST_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ./testMain.cpp)

target_link_libraries(${PROJECT_NAME} ${GTEST_BOTH_LIBRARIES} pthread)