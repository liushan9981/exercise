//
// Created by liushan on 19-10-20.
//

#include <stdio.h>
#include <stdlib.h>

#include "myutils.h"



void err_exit(const char * str)
{
    fprintf(stderr, "%s\n", str);
    exit(2);
}