//
// Created by liushan on 18-7-30.
//

#ifndef EXERCISE_LIST_H
#define EXERCISE_LIST_H

#include <stdbool.h>
#define NAME_SIZE 45
struct film {
    char name[NAME_SIZE];
    int rating;
};

typedef struct film Item;

typedef struct node {
    Item item;
    struct node * next;
} Node;

typedef Node * List;

bool InitializeList(List * plist);

bool ListIsEmpty(const List * plist);

bool ListIsFull(List * plist);

unsigned int ListCount(const List * plist);
bool ListAddItem(List * plist, const Item * item);
void ListTraverse(const List * plist, void (* item_func) (Item * item) );
void ListEmpty(List * plist);


#endif //EXERCISE_LIST_H
