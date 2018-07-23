#include <stdio.h>
#include <stdlib.h>



void iore_print(void)
{
    char * error_log_file = "/home/liushan/mylab/clab/exercise/temp/error.log";
    char * output_log_file = "/home/liushan/mylab/clab/exercise/temp/output.log";
    FILE * fd_err;
    FILE * fd_output;


    if ( (fd_err = freopen(error_log_file, "a+", stderr)) == NULL)
    {
        fprintf(stderr, "freopen file %s error\n", error_log_file);
        exit(EXIT_FAILURE);
    }

    if ( (fd_output = freopen(output_log_file, "a+", stdout)) == NULL)
    {
        fprintf(stderr, "freopen file %s error\n", output_log_file);
        exit(EXIT_FAILURE);
    }

    printf("Hello World!\n");
    fprintf(stderr, "hehhe\n");
}
