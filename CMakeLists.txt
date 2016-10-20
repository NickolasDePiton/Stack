cmake_minimum_required(VERSION 3.5.2)

project(catch_builder CXX)
include(ExternalProject)
find_package(Git REQUIRED)

ExternalProject_Add(
    catch
    PREFIX ${CMAKE_BINARY_DIR}/catch
    GIT_REPOSITORY https://github.com/philsquared/Catch.git
    TIMEOUT 10
    UPDATE_COMMAND ${GIT_EXECUTABLE} pull
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    LOG_DOWNLOAD ON
)

ExternalProject_Get_Property(catch source_dir)
set(CATCH_INCLUDE_DIR ${source_dir}/include CACHE INTERNAL "Path to include folder for Catch")
PROJECT(${GLOBAL_PROJECT_NAME})
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -fdiagnostics-color=always")
include_directories("include")
add_subdirectory(sources)
include_directories(${CATCH_INCLUDE_DIR})
enable_testing(true)
add_subdirectory(tests)
