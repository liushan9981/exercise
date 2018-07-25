//
// Created by liushan on 18-7-25.
//

#include <stdio.h>
#include <time.h>
#include <zconf.h>


void mytime(void)
{
    time_t t;
    struct tm * tmptr;
    struct tm tm;
    char buf1[16];
    char buf2[64];
    // clock_id 定义为不同的值
    clockid_t clock_id = CLOCK_REALTIME;
//    clockid_t clock_id = CLOCK_MONOTONIC;
//    clockid_t clock_id = CLOCK_PROCESS_CPUTIME_ID;
    struct timespec  tsp;
    char * mytime = "2017-07-13 17:00:00";
    int flag = 3;


    if (flag == 1)
    {
        clock_gettime(clock_id, &tsp);
        // 系统时区
        tmptr = localtime(&tsp.tv_sec);
        // UTC
//        tmptr = gmtime(&tsp.tv_sec);

        printf("%ld  %ld\n", tsp.tv_sec, tsp.tv_nsec);

        if (strftime(buf1, 16, "%Y-%m-%d %H:%M:%S", tmptr) == 0)
            printf("lenth %d is too small\n", 16);
        else
            printf("%s\n", buf1);

        if (strftime(buf2, 64, "%Y-%m-%d %H:%M:%S", tmptr) == 0)
            printf("lenth %d is too small\n", 16);
        else
            printf("%s\n", buf2);

    }
    else if (flag == 2)
    {
        time(&t);
        printf("%ld\n", t);
        tmptr = localtime(&t);

        if (strftime(buf2, 64, "%Y-%m-%d %H:%M:%S", tmptr) == 0)
            printf("lenth %d is too small\n", 16);
        else
            printf("%s\n", buf2);
    }
    else if (flag == 3)
    {
        if (strptime(mytime, "%Y-%m-%d %H:%M:%S", &tm) == NULL)
            printf("format error\n");

        t = mktime(&tm);
        printf("%ld\n", t);
    }

}