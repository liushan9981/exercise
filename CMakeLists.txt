project(exercise)
cmake_minimum_required(VERSION 2.8)
set(SOURCE_FILES main.c combination.c  combination.h)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
