cmake_minimum_required(VERSION 3.5.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(WSD VERSION 0.1.0 LANGUAGES C CXX)

add_executable(WSD src/Markov.cpp src/main.cpp src/math.cpp) #main project
# add_executable(WSD src/math.cpp src/Markov.cpp src/test.cpp) #testing file

include_directories(include)

set(OUTPUT_DIR ${CMAKE_SOURCE_DIR}/bin)

file(MAKE_DIRECTORY ${OUTPUT_DIR})

add_custom_command(TARGET WSD POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:WSD> ${OUTPUT_DIR}/$<TARGET_FILE_NAME:WSD>)
