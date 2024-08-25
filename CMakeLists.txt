cmake_minimum_required(VERSION 3.29)
project(lexical)

set(CMAKE_CXX_STANDARD 20)
configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Source.txt
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY
)
add_executable(lexical main.cpp)
add_library(file_util STATIC src/utils.cpp)
add_library(lex_definitions STATIC src/definitions.cpp
        library/definitions.hpp)

target_include_directories(file_util PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/library)
target_include_directories(lex_definitions PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/library)

target_link_libraries(lexical PUBLIC file_util lex_definitions)
