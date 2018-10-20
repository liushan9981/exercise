//
// Created by liushan on 18-10-20.
//

#include "myfork.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int global_var = 123;
char buf[] = "this is liushan\n";

void myfork(void)
{
    int var;
    pid_t pid;

    var = 1;

    write(STDOUT_FILENO, buf, sizeof(buf) - 1);
    printf("before fork\n");
    if ( (pid = fork() ) < 0)
    {
        printf("fork error, now exit\n");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        var++;
        global_var++;
    }
    else
    {
        sleep(2);
    }

    printf("pid: %ld, ppid: %ld, global_var: %d, var: %d\n", (long) getpid(), (long) getppid(), global_var, var);

}