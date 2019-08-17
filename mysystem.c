//
// Created by liushan on 18-11-11.
//

#include "mysystem.h"
#include "pr_exit.h"
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/acct.h>

/*
 * 执行和输出结果如下：
    [liushan@liushan-pc 下载]$ /home/liushan/mylab/clang/exercise/cmake-build-debug/exercise
    2018年 11月 11日 星期日 17:44:12 CST
    normal termination, exit status: 0
    bash: liushan: 未找到命令
    normal termination, exit status: 127
    liushan  tty1         2018-11-10 15:46 (:0)
    liushan  pts/0        2018-11-10 15:47 (:0)
    liushan  pts/1        2018-11-10 15:47 (:0)
    liushan  pts/2        2018-11-11 15:51 (:0)
    liushan  pts/3        2018-11-11 15:57 (:0)
    liushan  pts/7        2018-11-11 16:25 (:0)
    normal termination, exit status: 44
    [liushan@liushan-pc 下载]$
 */

int mysystem(const char * cmdstring);



int mysystem(const char * cmdstring)
{
    /*
     * 没有对信号进行处理的版本
     */
    pid_t pid;
    int status;
    /*
     * 查看acct数据类型
    struct acct acdata;
    */


    if (cmdstring == NULL)
        return 1;

    if ( (pid = fork() ) < 0)
        status = -1;
    else if (pid == 0)
    {
        execl("/bin/bash", "bash", "-c", cmdstring, (char *) 0);
        _exit(127);
    }
    else
    {
        while (waitpid(pid, &status, 0) < 0)
        {
            if (errno != EINTR)
            {
                status = -1;
                break;
            }
        }
    }

    return status;

}


void test_system(void)
{
    int status;

    if ( (status = mysystem("date")) < 0)
    {
        printf("mysystem() error\n");
        exit(EXIT_FAILURE);
    }
    pr_exit(status);

    if ( (status = mysystem("liushan")) < 0)
    {
        printf("mysystem() error\n");
        exit(EXIT_FAILURE);
    }
    pr_exit(status);

    if ( (status = mysystem("who;exit 44")) < 0)
    {
        printf("mysystem() error\n");
        exit(EXIT_FAILURE);
    }
    pr_exit(status);

}


void sig_user(int);

void sig_user(int signo)
{
    if (signo == SIGUSR1)
        printf("received SIGUSR1\n");
    else if (signo == SIGUSR2)
        printf("received SIGUSR2\n");
    else
    {
        printf("received signal %d\n", signo);
        exit(1);
    }
}



void run_signal_usr(void)
{
    if (signal(SIGUSR1, sig_user) == SIG_ERR)
    {
        printf("can't catch SIGUSR1");
        exit(1);
    }

    if (signal(SIGUSR2, sig_user) == SIG_ERR)
    {
        printf("can't catch SIGUSR2");
        exit(1);
    }

    for ( ; ; )
        sleep(3);

}