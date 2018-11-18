//
// Created by liushan on 18-11-18.
//

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/time.h>
#include <zconf.h>
#include <pwd.h>

#include "proc_nice.h"

void checktime(char *str);
// 书中没有显式赋值为0，本人觉得为了可读性，应该显式赋值
unsigned long long count = 0;
struct timeval end;


/*
 * 根据时间，判断是否退出
 */
void checktime(char *str)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    if (tv.tv_sec >= end.tv_sec && tv.tv_usec >= end.tv_usec)
    {
        printf("%s count = %lld\n", str, count);
        exit(0);
    }
}


/*
 *
 *
 * 输出如下：
    [liushan@liushan-pc ~]$ /home/liushan/mylab/clang/exercise/cmake-build-debug/exercise
    login name: liushan
    login name get from getpwuid(): liushan
    NZERO = 20
    current nice value in parent is 20
    current nice value in child is 20, incr by 12
    now child nice value is 32
    now nice value in child is 32
    nice again now child nice value is 35
    nice again current nice value in child is 35
    parent count = 380877040
    child count = 357017820
    [liushan@liushan-pc ~]$
*/

void run_proc_nice(void)
{
    pid_t pid;
    char * s;
    int nzero, ret;
    int adj = 12;
    char * login_name;

    setbuf(stdout, NULL);
    nzero = sysconf(_SC_NZERO);

    if ( (login_name = getlogin() ) == NULL)
        printf("get login name error\n");
    else
        printf("login name: %s\n", login_name);

    printf("login name get from getpwuid(): %s\n", getpwuid(getuid())->pw_name);
    printf("NZERO = %d\n", nzero);
    gettimeofday(&end, NULL);
    end.tv_sec += 10;

    if ( (pid = fork() ) < 0)
    {
        printf("fork error\n");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        s = "child";
        printf("current nice value in child is %d, incr by %d\n", nice(0) + nzero, adj);
        errno = 0;
        if ( (ret = nice(adj) ) == -1 && errno != 0)
        {
            printf("run nice error\n");
            exit(EXIT_FAILURE);
        }
        printf("now child nice value is %d\n", ret + nzero);
        printf("now nice value in child is %d\n", nice(0) + nzero);

        if ( (ret = nice(3) ) == -1 && errno != 0)
        {
            printf("run nice error\n");
            exit(EXIT_FAILURE);
        }
        printf("nice again now child nice value is %d\n", ret + nzero);
        printf("nice again current nice value in child is %d\n", nice(0) + nzero);
    }
    else
    {
        s = "parent";
        printf("current nice value in parent is %d\n", nice(0) + nzero);
    }

    for (;;)
    {
        if (++count == 0)
        {
            printf("%s counter wrap", s);
            exit(EXIT_FAILURE);
        }
        checktime(s);
    }

}