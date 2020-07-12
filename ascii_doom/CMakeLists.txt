project(ascii_doom)
cmake_minimum_required(VERSION 3.15)

set(CMAKE_BUILD_TYPE Debug)
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /DUNICODE /utf-8")

add_library(olcConsoleGameEngine STATIC third_party/lib.cpp)


add_executable(ascii_doom
	"src/main_doom.c"
)

target_link_libraries(ascii_doom olcConsoleGameEngine)
target_include_directories(ascii_doom PRIVATE third_party)

