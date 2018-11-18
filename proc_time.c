//
// Created by liushan on 18-11-18.
//

#include "proc_time.h"
#include "pr_exit.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/times.h>
#include <zconf.h>


static void pr_times(clock_t, struct tms *, struct tms *);

static void do_cmd(char *);




void run_proc_time(void)
{
    int index;
    char * cmd_all[] = {
            "sleep 4",
            "date",
            "man tar > /dev/null"
    };

    setbuf(stdout, NULL);

    for (index = 0; index < (sizeof(cmd_all) / sizeof(char *) ); index++)
    {
        do_cmd(cmd_all[index]);
    }

}


static void do_cmd(char * cmd)
{
    struct tms tms_start, tms_end;
    clock_t start, end;
    int status;

    printf("command: %s\n", cmd);

    if ( (start = times(&tms_start) ) < 0)
    {
        printf("times exec error\n");
        exit(EXIT_FAILURE);
    }

    if ( (status = system(cmd) ) < 0)
    {
        printf("system exec cmd error cmd: %s\n", cmd);
        exit(EXIT_FAILURE);
    }

    if ( (end = times(&tms_end) ) < 0)
    {
        printf("times exec error\n");
        exit(EXIT_FAILURE);
    }

    pr_exit(status);
    pr_times(end - start, &tms_start, &tms_end);

}


static void pr_times(clock_t real, struct tms * tms_start, struct tms * tms_end)
{
    static long tick_sec = 0;


    if (tick_sec == 0)
        if ( (tick_sec = sysconf(_SC_CLK_TCK) ) < 0)
        {
            printf("sysconf get _SC_CLK_TCK error\n");
            exit(EXIT_FAILURE);
        }

    printf("real: %.2f\n", real / (double) tick_sec);
    printf("user: %.2f\n", (tms_end->tms_utime - tms_start->tms_utime) / (double) tick_sec);
    printf("sys: %.2f\n", (tms_end->tms_stime - tms_start->tms_stime) / (double) tick_sec);
    printf("child user: %.2f\n", (tms_end->tms_cutime - tms_start->tms_cutime) / (double) tick_sec);
    printf("child sys: %.2f\n", (tms_end->tms_cstime - tms_start->tms_cstime) / (double) tick_sec);




}
