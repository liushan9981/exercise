#include "byte_order.h"
#include <stdio.h>


void run_byte_order(void)
{
    union {
        short s;
        char c[sizeof(short)];
    } un;

    un.s = 0x0102;

    // 低字节存储起始值
    if (un.c[0] == 2 && un.c[1] == 1)
        printf("little\n");
    else if (un.c[0] == 1 && un.c[1] == 2)
        printf("big\n");

    printf("%p  %p\n", &un.c[0], &un.c[1]);


}
