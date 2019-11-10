//
// Created by liushan on 19-11-10.
//

#include "test.h"

#include <string.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>


void init_conninfo(struct conninfo * conn_ptr, int num);


void temp_test(void)
{
    // char * ch = "User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:70.0) Gecko/20100101 Firefox/70.0";
    char * ch = "User-Agent:Mozilla/5.0 (X11; Linux x86_64; rv:70.0) Gecko/20100101 Firefox/70.0";
    char key[64], value[128];

    strcpy(key, "User-Agent");

    int blank_num = 0;
    int index = 0;

    for (index = strlen(key) + 1, blank_num = 0; index < strlen(ch); index++, blank_num++)
    {
        if (ch[index] != ' ')
            break;
    }

    memcpy(value, ch + strlen(key) + 1 + blank_num, strlen(ch) - (strlen(key) + 1) );
    printf("#key:%s\n", key);
    printf("#value:%s\n", value);

}



void init_conninfo(struct conninfo * conn_ptr, int num)
{
    conn_ptr[0].a = 1;
    conn_ptr[0].b = 2;
    conn_ptr[0].c = 'a';
}