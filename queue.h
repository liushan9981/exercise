//
// Created by liushan on 18-8-1.
//

#ifndef EXERCISE_QUEUE_H
#define EXERCISE_QUEUE_H

#include <stdbool.h>

#define QueueMaxSize 10

// typedef int Item;

typedef struct item {
    long arrive;
    int processtime;
} Item;

typedef struct node {
    Item item;
    struct node * next;
} Node;

typedef struct queue {
    Node * start;
    Node * end;
    int count;
} Queue;

void QueueInitialize(Queue * qptr);
bool QueueIsEmpty(const Queue * qptr);
bool QueueIsFull(const Queue * qptr);
int QueueCount(const Queue * qptr);
bool QueueProd(Queue * qptr, Item * item);
bool QueueCons(Queue * qptr, Item * item);
void QueueEmpty(Queue * qptr);

#endif //EXERCISE_QUEUE_H
