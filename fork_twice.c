//
// Created by liushan on 18-10-20.
//

#include "fork_twice.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>


// fork 两次
void fork_twice(void)
{
    pid_t pid;


    if ( (pid = fork() ) < 0)
    {
        printf("fork error, now exit!\n");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        // 儿子
        if ( (pid = fork() ) < 0)
        {
            printf("fork error, now exit!\n");
            exit(EXIT_FAILURE);
        }
        else if (pid > 0)
            // 儿子退出
            exit(0);
        else
        {
            // 这是孙子
            sleep(2);
            printf("parent pid: %ld\n", (long) getppid());
            exit(0);
        }
    }


    // 这是老子
    if (waitpid(pid, NULL, 0) != pid)
        printf("wait error\n");
    exit(0);
}