//
// Created by liushan on 18-10-28.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include "run_exec.h"

// 为便于测试，在另外一个单独的项目，生成单独的可执行文件
void print_argv(int argc, char * argv[]);

void run_exec(void)
{
    pid_t pid;

    // execle
    if ( (pid = fork() ) < 0)
    {
        printf("fork error, now exit.\n");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        char * myenv[] = {"USER=unknown", "PATH=/tmp", NULL};
        if (execle("/home/liushan/a.out", "a.out", "shan", "fan", (char *) 0, myenv) < 0)
        {
           printf("execle error, now exit\n");
           exit(EXIT_FAILURE);
        }
    }

    if (waitpid(pid, NULL, 0) != pid)
    {
        printf("wait error, now exit\n");
        exit(EXIT_FAILURE);
    }



    // execl
    if ( (pid = fork() ) < 0)
    {
        printf("fork error, now exit.\n");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        if (execl("/home/liushan/a.out", "a.out", "hao", "xin", (char *) 0) < 0)
        {
            printf("execl error, now exit\n");
            exit(EXIT_FAILURE);
        }
    }

    if (waitpid(pid, NULL, 0) != pid)
    {
        printf("wait error, now exit\n");
        exit(EXIT_FAILURE);
    }




    // execv
    if ( (pid = fork() ) < 0)
    {
        printf("fork error, now exit.\n");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        char * ptr[] = {"a.out", "123", "456", NULL};
        if (execv("/home/liushan/a.out", ptr) < 0)
        {
            printf("execv error, now exit\n");
            exit(EXIT_FAILURE);
        }
    }

    if (waitpid(pid, NULL, 0) != pid)
    {
        printf("wait error, now exit\n");
        exit(EXIT_FAILURE);
    }



    // execve
    if ( (pid = fork() ) < 0)
    {
        printf("fork error, now exit.\n");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        char * ptr[] = {"a.out", "abc", "efg", NULL};
        char * ptr_env[] = {"POD=haha", "APP=teacher", NULL};
        if (execve("/home/liushan/a.out", ptr, ptr_env) < 0)
        {
            printf("execve error, now exit\n");
            exit(EXIT_FAILURE);
        }
    }

    if (waitpid(pid, NULL, 0) != pid)
    {
        printf("wait error, now exit\n");
        exit(EXIT_FAILURE);
    }

}



void print_argv(int argc, char * argv[])
{
    int i;
    extern char ** environ;
    char ** ptr;

    for (i = 0; i < argc; i++)
        printf("argv[%d]: %s\n", i, argv[i]);
    for (ptr = environ; *ptr != NULL; ptr++)
        printf("%s\n", *ptr);

}
