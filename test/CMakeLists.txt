find_package(GTest REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/src include ${GTEST_INCLUDE_DIRS})

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

add_executable(testGeometry testMain.cpp)

target_link_libraries(testGeometry ${GTEST_BOTH_LIBRARIES} pthread)