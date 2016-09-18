cmake_minimum_required(VERSION 2.8)

set(TESTS_FOR_PROJECT STACK)

project(Tests)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

option(BUILD_SHARED_LIBS "Build shared instead of static library" OFF)

file(GLOB ${PROJECT_NAME}_sources "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp")

find_package(${TESTS_FOR_PROJECT})
include_directories(${${TESTS_FOR_PROJECT}_INCLUDE_DIRS}})

include(cmake/FindCPM.cmake)
CPM_AddModule("cpm-catch"
  GIT_REPOSITORY "https://github.com/designerror/cpm-catch")
include_directories(${CPM_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_sources} ${${PROJECT_NAME}_headers})

target_link_libraries(${PROJECT_NAME} ${TESTS_FOR_PROJECT})


add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_CURRENT_SOURCE_DIR}/fixtures $<TARGET_FILE_DIR:${PROJECT_NAME}>)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${PROJECT_NAME} -s -r compact WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
