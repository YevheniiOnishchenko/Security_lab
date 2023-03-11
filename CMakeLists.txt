cmake_minimum_required(VERSION 3.5)

project(Lab1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(COMPILE_FLAGS -D _CRT_SECURE_NO_WARNINGS)

FILE(GLOB SRC ${CMAKE_SOURCE_DIR}/*.cpp
    ${CMAKE_SOURCE_DIR}/Algorythms/*.cpp
    ${CMAKE_SOURCE_DIR}/Handlers/*.cpp)
FILE(GLOB HDR ${CMAKE_SOURCE_DIR}/*.h
    ${CMAKE_SOURCE_DIR}/Algorythms/*.h
    ${CMAKE_SOURCE_DIR}/Handlers/*.h)

add_executable(Lab1 ${SRC} ${HDR} main.cpp)

install(TARGETS Lab1
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
