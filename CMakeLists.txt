cmake_minimum_required(VERSION 3.21)
project(DatsEdenSpace)
set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCE_FILES "src/**.cpp" "src/**.cc")
list(REMOVE_ITEM SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")
add_executable(dats_eden_space src/main.cpp ${SOURCE_FILES})

#add_subdirectory(proto)
#add_subdirectory(3rdparty/clsocket)
#add_subdirectory(3rdparty/simplex)
target_include_directories(dats_eden_space PRIVATE "src")
#target_link_libraries(dats_eden_space PRIVATE proto_messages clsocket open_simplex )
