//
// Created by liushan on 18-7-28.
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zconf.h>
#include "film2.h"


/* 链表 */


void film2(unsigned long num)
{
    struct film * head = NULL;
    struct film * pre;
    struct film * current;
    unsigned long i;

    // 创建链表
    for (i = 0; i < num; i++)
    {
        // printf("name_%ld  %d\n", i, (int ) i % 10000);
        if (head == NULL)
        {
            if ( (head = (struct film * )malloc(sizeof(struct film) ) ) == NULL)
            {
                fprintf(stderr, "malloc error, now exit!\n");
                exit(EXIT_FAILURE);
            }
            else
            {
                snprintf(head->name, 44, "name_%ld", i);
                head->rating = (int ) i % 10000;
                head->next = NULL;
                current = head;
            }
        }
        else
        {
            if ( (current = (struct film * )malloc(sizeof(struct film) ) ) == NULL)
            {
                fprintf(stderr, "malloc error, now exit!\n");
                exit(EXIT_FAILURE);
            }
            else
            {
                snprintf(current->name, 44, "name_%ld", i);
                current->rating = (int ) i % 10000;
                current->next = NULL;
                pre->next = current;
            }

        }

        if (i % 2000 == 0)
        {
            printf("malloc i: %ld\n", i);
            sleep(1);
        }


        pre = current;
    }

    // 显示链表
    current = head;
    if (current == NULL)
        printf("no data input!\n");
    else
        printf("movie_name    rating\n");

    while (current != NULL)
    {
        printf("%s  %d\n", current->name, current->rating);
        current = current->next;
    }


    // 释放链表
    current = head;
    for (i = 0; current != NULL; i++)
    {
        head = current->next;
        free(current);
        current = head;

        if (i % 2000 == 0)
        {
            printf("free i: %ld\n", i);
            sleep(1);
        }

    }


//    for (i = 0; i < 100000; i++)
//    {
//        (struct film * )malloc(sizeof(struct film) );
//
//        if (i % 2000 == 0)
//        {
//            printf("molloc again i: %ld\n", i);
//            sleep(1);
//        }
//    }
//




//    while (current != NULL)
//    {
//        head = current->next;
//        free(current);
//        current = head;
//    }


}