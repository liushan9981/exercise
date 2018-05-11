#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "combination.h"




int main(int argc, char *argv[])
{

    char * error_log_file = "/home/liushan/mylab/clab/mytemp/temp/error.log";
    char * output_log_file = "/home/liushan/mylab/clab/mytemp/temp/output.log";
    FILE * fd_err;
    FILE * fd_output;

    long num;


    for (num = 1; num <= 20; num++)
    {
        printf("%-2ld  ->  %-10ld\n", num, mynum(num) );
    }






//    if ( (fd_err = freopen(error_log_file, "a+", stderr)) == NULL)
//    {
//        fprintf(stderr, "freopen file %s error\n", error_log_file);
//        exit(EXIT_FAILURE);
//    }

//    if ( (fd_output = freopen(output_log_file, "a+", stdout)) == NULL)
//    {
//        fprintf(stderr, "freopen file %s error\n", output_log_file);
//        exit(EXIT_FAILURE);
//    }





    // printf("Hello World!\n");
    // fprintf(stderr, "hehhe\n");
    return 0;
}


