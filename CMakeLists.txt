project(exercise)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_C_STANDARD 99)
set(SOURCE_FILES main.c combination.c  combination.h ioredirect.h ioredirect.c fields.h fields.c
    dualview.c dualview.h align.h align.c byte_order.h byte_order.c addr_trans.c addr_trans.h)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
