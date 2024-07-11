cmake_minimum_required(VERSION 3.5.0)
project(WSD VERSION 0.1.0 LANGUAGES C CXX)

add_executable(WSD src/main.cpp src/print.cpp)

set(OUTPUT_DIR ${CMAKE_SOURCE_DIR}/bin)

file(MAKE_DIRECTORY ${OUTPUT_DIR})

add_custom_command(TARGET WSD POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:WSD> ${OUTPUT_DIR}/$<TARGET_FILE_NAME:WSD>)
