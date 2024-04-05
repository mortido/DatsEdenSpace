cmake_minimum_required(VERSION 3.21)
project(dats-eden-space)

set(LOGURU_WITH_STREAMS TRUE)
add_subdirectory(loguru)
add_subdirectory(rapidjson)

add_subdirectory(src)
