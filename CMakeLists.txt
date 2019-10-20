project(exercise)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_C_STANDARD 99)


set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lssl")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lcrypto")

set(SOURCE_FILES main.c combination.c  combination.h ioredirect.h ioredirect.c fields.h fields.c
    dualview.c dualview.h align.h align.c byte_order.h byte_order.c addr_trans.c addr_trans.h
    writen_readn_readline.c writen_readn_readline.h mysignal.c  mysignal.h echo_srv.c echo_srv.h
    echo_cli.c echo_cli.h echo_run.h echo_run.c echo_sum.h
        rio_read_write.h rio_read_write.c myreaddir.h myreaddir.c mypasswd.h mypasswd.c myuname.h myuname.c mytime.h mytime.c film2.h film2.c list.h list.c film3.c film3.h queue.h queue.c test_queue.c test_queue.h mall.c mall.h binary_tree.c binary_tree.h test_bin_tree.c test_bin_tree.h myprintf.c myprintf.h create_tempfile.c create_tempfile.h myfork.c myfork.h pr_exit.c pr_exit.h fork_twice.c fork_twice.h run_exec.c run_exec.h run_setuid.c run_setuid.h interpreter.c interpreter.h mysystem.c mysystem.h proc_nice.c proc_nice.h proc_time.c proc_time.h orphan_process.c orphan_process.h https_client.c https_client.h sleep2.c sleep2.h sig_pr_mask.c sig_pr_mask.h sig_sigpending.c sig_sigpending.h myutils.c myutils.h)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
