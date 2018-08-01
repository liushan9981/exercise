//
// Created by liushan on 18-8-1.
//


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "queue.h"


void QueueInitialize(Queue * qptr)
{
    qptr->start = qptr->end = NULL;
    qptr->count = 0;
}

bool QueueIsEmpty(const Queue * qptr)
{
    return qptr->count == 0;
}

bool QueueIsFull(const Queue * qptr)
{
    return qptr->count == QueueMaxSize;
}

int QueueCount(const Queue * qptr)
{
    return qptr->count;
}

bool QueueProd(Queue * qptr, Item * item)
{
    Node * new_node;

    if (QueueIsFull(qptr) )
        return false;

    if ( (new_node = (Node *) malloc(sizeof(Node) ) ) == NULL)
    {
        fprintf(stderr, "malloc memory error\n");
        return false;
    }

    new_node->item = *item;
    new_node->next = NULL;

    if (QueueIsEmpty(qptr) )
        qptr->start = new_node;
    else
        qptr->end->next = new_node;

    qptr->end = new_node;
    qptr->count++;

    return true;
}


bool QueueCons(Queue * qptr, Item * item)
{
    Node * temp_ptr;

    if (QueueIsEmpty(qptr) )
        return false;

    *item = qptr->start->item;

    temp_ptr = qptr->start;
    qptr->start = qptr->start->next;
    free(temp_ptr);
    qptr->count--;
    if (QueueIsEmpty(qptr) )
        qptr->end = NULL;

    return true;
}

void QueueEmpty(Queue * qptr)
{
    Item item;

    while (! QueueIsEmpty(qptr) )
        QueueCons(qptr, &item);
}