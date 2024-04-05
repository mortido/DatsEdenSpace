cmake_minimum_required(VERSION 3.21)
project(mortido-bot)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/**.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/**.cc")
list(REMOVE_ITEM SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
add_executable(${PROJECT_NAME} main.cpp ${SOURCE_FILES})

include(FindPkgConfig)
pkg_check_modules(CURLPP REQUIRED curlpp)
target_link_libraries(${PROJECT_NAME} PRIVATE loguru rapidjson ${CURLPP_LDFLAGS})
