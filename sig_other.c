//
// Created by liushan on 19-10-27.
//


#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>

#include "sig_other.h"





void sig_test_other(void)
{
    char * sig_str = "./exercise";

    psignal(SIGTERM, sig_str);

    sig_str = strsignal(SIGPIPE);
    printf("%s\n", sig_str);

    // printf("")

}