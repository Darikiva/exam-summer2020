cmake_minimum_required(VERSION 3.15)
project(exam_summer2020)

set(CMAKE_CXX_STANDARD 14)

set(TOP_DIR ${CMAKE_SOURCE_DIR})
set(SRC_DIR ${TOP_DIR}/src)
set(TESTS_DIR ${TOP_DIR}/test)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(${SRC_DIR})

set(SRC_LIST
        ${SRC_DIR}/AVLtree.hpp
    )

set(LIB_NAME ${PROJECT_NAME}core)
add_library(${LIB_NAME} STATIC ${SRC_LIST})

set_target_properties(${LIB_NAME} PROPERTIES LINKER_LANGUAGE CXX)

option(BUILD_TEST "Build project tests" ON)
if(BUILD_TEST)
    enable_testing()
    add_subdirectory(${TESTS_DIR})
endif()


add_executable(main main.cpp)
target_link_libraries(main PRIVATE ${LIB_NAME})