cmake_minimum_required(VERSION 3.10)
project(loguru LANGUAGES CXX)

add_library(${PROJECT_NAME} src/loguru.cpp) # allow BUILD_SHARED_LIBS to decide STATIC/SHARED
#add_library(${PROJECT_NAME} STATIC src/loguru.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC include)

#set(CMAKE_CXX_STANDARD 11)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_11)

find_package(Threads REQUIRED) # defines IMPORTED target Threads::Threads
target_link_libraries(${PROJECT_NAME}
  PRIVATE
    Threads::Threads    # pthreads (or equivalent)
    ${_lib_dl_linkflag} # dl (or equivalent)
)

target_compile_definitions(loguru
  # NOTE: these generator expressions are dense but the logic is quite simple!
  #       if any of the cache variables are not equal to the empty string, set them as a definition.
  #       Additionally, the "boolean" variables are coerced into a numeric representation (1 or 0)
  PUBLIC
    $<$<NOT:$<STREQUAL:,${LOGURU_EXPORT}>>:LOGURU_EXPORT=${LOGURU_EXPORT}>
    $<$<NOT:$<STREQUAL:,${LOGURU_DEBUG_LOGGING}>>:LOGURU_DEBUG_LOGGING=$<BOOL:${LOGURU_DEBUG_LOGGING}>>
    $<$<NOT:$<STREQUAL:,${LOGURU_DEBUG_CHECKS}>>:LOGURU_DEBUG_CHECKS=$<BOOL:${LOGURU_DEBUG_CHECKS}>>
    $<$<NOT:$<STREQUAL:,${LOGURU_SCOPE_TEXT_SIZE}>>:LOGURU_SCOPE_TEXT_SIZE=${LOGURU_SCOPE_TEXT_SIZE}>
    $<$<NOT:$<STREQUAL:,${LOGURU_REDEFINE_ASSERT}>>:LOGURU_REDEFINE_ASSERT=$<BOOL:${LOGURU_REDEFINE_ASSERT}>>
    $<$<NOT:$<STREQUAL:,${LOGURU_WITH_STREAMS}>>:LOGURU_WITH_STREAMS=$<BOOL:${LOGURU_WITH_STREAMS}>>
    $<$<NOT:$<STREQUAL:,${LOGURU_REPLACE_GLOG}>>:LOGURU_REPLACE_GLOG=$<BOOL:${LOGURU_REPLACE_GLOG}>>
    $<$<NOT:$<STREQUAL:,${LOGURU_USE_FMTLIB}>>:LOGURU_USE_FMTLIB=$<BOOL:${LOGURU_USE_FMTLIB}>>
    $<$<NOT:$<STREQUAL:,${LOGURU_FMT_HEADER_ONLY}>>:LOGURU_FMT_HEADER_ONLY=$<BOOL:${LOGURU_FMT_HEADER_ONLY}>>
    $<$<NOT:$<STREQUAL:,${LOGURU_WITH_FILEABS}>>:LOGURU_WITH_FILEABS=$<BOOL:${LOGURU_WITH_FILEABS}>>
    $<$<NOT:$<STREQUAL:,${LOGURU_STACKTRACES}>>:LOGURU_STACKTRACES=$<BOOL:${LOGURU_STACKTRACES}>>
    $<$<NOT:$<STREQUAL:,${LOGURU_RTTI}>>:LOGURU_RTTI=$<BOOL:${LOGURU_RTTI}>>
    $<$<NOT:$<STREQUAL:,${LOGURU_FILENAME_WIDTH}>>:LOGURU_FILENAME_WIDTH=${LOGURU_FILENAME_WIDTH}>
    $<$<NOT:$<STREQUAL:,${LOGURU_THREADNAME_WIDTH}>>:LOGURU_THREADNAME_WIDTH=${LOGURU_THREADNAME_WIDTH}>
    $<$<NOT:$<STREQUAL:,${LOGURU_SCOPE_TIME_PRECISION}>>:LOGURU_SCOPE_TIME_PRECISION=${LOGURU_SCOPE_TIME_PRECISION}>
    $<$<NOT:$<STREQUAL:,${LOGURU_VERBOSE_SCOPE_ENDINGS}>>:LOGURU_VERBOSE_SCOPE_ENDINGS=$<BOOL:${LOGURU_VERBOSE_SCOPE_ENDINGS}>>
)
