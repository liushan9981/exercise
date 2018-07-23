

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "echo_srv.h"
#include "echo_cli.h"



void echo_run(int argc, char * argv[])
{
    if (argc == 3)
    {
        if (strcmp(argv[1], "cli") == 0)
            echo_cli(argv[2]);
    }
    else if (argc == 2)
    {
        if (strcmp(argv[1], "srv") == 0)
            echo_srv();
    }
    else
    {
//        printf("argc: %d\n", argc);
//        printf("argv[1]: %s\n", argv[1]);
//        printf("argv[2]: %s\n", argv[2]);

        printf("usage: \n");
        printf("./exercise cli 127.0.0.1\n");
        printf("./exercise srv\n");
        exit(EXIT_FAILURE);
    }
}
