//
// Created by liushan on 18-7-30.
//


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <zconf.h>
#include "list.h"
#include "film3.h"

void show_films(Item * item);



void film3(unsigned long num)
{
    List mylist;
    unsigned int count;
    bool flag;
    int i = 0;
    Item item;


    InitializeList(&mylist);


    if ( (flag = ListIsEmpty(&mylist) ) == true)
        printf("list is empty\n");
    else
        printf("list is not empty\n");

    if ( (flag = ListIsFull(&mylist) ) == true)
        printf("list is full\n");
    else
        printf("list is not full\n");

    count = ListCount(&mylist);
    printf("list count is: %lu\n", count);

    for (i = 0; i < 100000; i++)
    {
        snprintf(item.name, NAME_SIZE - 1, "name_%lu", i);
        item.name[NAME_SIZE - 1] = 0;
        item.rating = i;
        if ( (flag = ListAddItem(&mylist, &item) ) == false)
            fprintf(stderr, "add item name: %s  rating: %d error\n", item.name, item.rating);
        if (i % 2000 == 0)
        {
            printf("molloc 1 i: %ld\n", i);
            sleep(1);
        }
    }

    count = ListCount(&mylist);
    printf("list count is: %lu\n", count);


    if ( (flag = ListIsEmpty(&mylist) ) == true)
        printf("list is empty\n");
    else
        printf("list is not empty\n");

    if ( (flag = ListIsFull(&mylist) ) == true)
        printf("list is full\n");
    else
        printf("list is not full\n");

    ListTraverse(&mylist, show_films);
    ListEmpty(&mylist);

    if ( (flag = ListIsEmpty(&mylist) ) == true)
        printf("list is empty\n");
    else
        printf("list is not empty\n");

    if ( (flag = ListIsFull(&mylist) ) == true)
        printf("list is full\n");
    else
        printf("list is not full\n");

    sleep(30);

    count = ListCount(&mylist);
    printf("list count is: %lu\n", count);

    for (i = 0; i < 100000; i++)
    {
        snprintf(item.name, NAME_SIZE - 1, "name_%lu", i);
        item.name[NAME_SIZE - 1] = 0;
        item.rating = i;
        if ( (flag = ListAddItem(&mylist, &item) ) == false)
            fprintf(stderr, "add item name: %s  rating: %d error\n", item.name, item.rating);
        if (i % 2000 == 0)
        {
            printf("molloc 2 i: %ld\n", i);
            sleep(1);
        }
    }

    ListTraverse(&mylist, show_films);
}



void show_films(Item * item)
{
    printf("name->%s, rating->%d\n", item->name, item->rating);
}