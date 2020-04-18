cmake_minimum_required(VERSION 3.15)

set(ProjectName GameOfLife)

project(${ProjectName})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)

add_executable(${ProjectName}Exec
	src/main.cpp
)
