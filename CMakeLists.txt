project(exercise)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_C_STANDARD 99)
set(SOURCE_FILES main.c combination.c  combination.h ioredirect.h ioredirect.c fields.h fields.c
    dualview.c dualview.h align.h align.c byte_order.h byte_order.c addr_trans.c addr_trans.h
    writen_readn_readline.c writen_readn_readline.h mysignal.c  mysignal.h echo_srv.c echo_srv.h
    echo_cli.c echo_cli.h echo_run.h echo_run.c echo_sum.h
        rio_read_write.h rio_read_write.c myreaddir.h myreaddir.c mypasswd.h mypasswd.c myuname.h myuname.c mytime.h mytime.c)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
