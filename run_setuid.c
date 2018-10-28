//
// Created by liushan on 18-10-28.
//

#include "run_setuid.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void run_exec_setuid(void);

void run_setuid(void)
{
    pid_t pid;

    printf("uid: %d euid: %d\n", getuid(), geteuid());

    if ( (pid = fork() ) < 0)
    {
        printf("fork error\n");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        if (execl("/home/liushan/a.out", "a.out", NULL) < 0)
        {
            printf("execl error\n");
            exit(EXIT_FAILURE);
        }
    }

    waitpid(pid, NULL, 0);

}


/*
 * 使用setuid时，输出如下：
    uid: 0 euid: 0
    child uid before: 0 euid: 0
    setuid ok
    child uid after: 1000 euid: 1000
 * 使用seteuid时，输出如下：
    uid: 0 euid: 0
    child uid before: 0 euid: 0
    setuid ok
    child uid after: 0 euid: 1000
   关于进程信息，如下：
    [liushan@liushan-pc ~]$
    [liushan@liushan-pc ~]$ ps aux | grep a.out
    liushan  18539  0.0  0.0   2296   748 pts/2    S+   17:26   0:00 a.out
    liushan  18543  0.0  0.0  11252  2208 pts/3    S+   17:26   0:00 grep --colour=auto a.out
    [liushan@liushan-pc ~]$ ps aux | grep exer
    root     18537  0.0  0.0  50576  6092 pts/2    S+   17:26   0:00 sudo /home/liushan/mylab/clang/exercise/cmake-build-debug/exercise
    root     18538  0.0  0.0   2328   756 pts/2    S+   17:26   0:00 /home/liushan/mylab/clang/exercise/cmake-build-debug/exercise
    liushan  18545  0.0  0.0  11252  2280 pts/3    S+   17:26   0:00 grep --colour=auto exer
    [liushan@liushan-pc ~]$

*/

// 如下代码，测试时放在单独的项目，生成单独的可执行文件
void run_exec_setuid(void)
{
    printf("child uid before: %d euid: %d\n", getuid(), geteuid());

    // if (setuid(1000) < 0)
    if (seteuid(1000) < 0)
    {
        printf("setuid error\n");
        sleep(30);
    }
    else
    {
        printf("setuid ok\n");
        printf("child uid after: %d euid: %d\n", getuid(), geteuid());
        sleep(30);
    }
}
