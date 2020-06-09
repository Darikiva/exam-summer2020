cmake_minimum_required(VERSION 3.15)
project(exam_summer2020)

set(CMAKE_CXX_STANDARD 17)

set(TOP_DIR ${CMAKE_SOURCE_DIR})
set(SRC_DIR ${TOP_DIR}/src)
set(TESTS_DIR ${TOP_DIR}/test)
set(GUI_DIR ${TOP_DIR}/ui)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "-g3")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(${SRC_DIR})
include_directories(${SRC_DIR})

option(BUILD_TEST "Build project tests" ON)
if(BUILD_TEST)
    enable_testing()
    add_subdirectory(${TESTS_DIR})
endif()

option(BUILD_GUI "Build sorting algorithms visualization" ON)
if (BUILD_GUI)
    add_subdirectory(${GUI_DIR})
endif()


add_executable(main main.cpp src/sortings/CountSort.h src/sortings/BucketSort.h)
target_link_libraries(main PRIVATE ${LIB_NAME})
