cmake_minimum_required(VERSION 3.29)

project(SSPP
		DESCRIPTION "Simplified Signal Proocessing Pipeline for SYSC 4906 assignment"
		LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS off)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(test)

