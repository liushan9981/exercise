//
// Created by liushan on 18-8-7.
//

#include <stdio.h>

#include "myprintf.h"


void myprintf(void)
{
    char temp[10];
    int num;

    // 位置引用变量
    printf("%2$d, %1$d, %1$d\n", 23, 45);
    printf("%5d\n", 6);
    // 第三个位置变量作为宽度
    printf("%*3$d,%*3$d\n", 2, 3, 5);

    num = snprintf(temp, 9, "0123456789abc");

    printf("%d, %s\n", num, temp);

}
