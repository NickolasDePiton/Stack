cmake_minimum_required(VERSION 3.5.2)
project(${CMAKE_PROJECT_NAME}_test CXX)

file(GLOB SOURCES *.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${CMAKE_PROJECT_NAME}_lib)

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME} "-s" "-r" "compact" "--use-colour" "yes")
