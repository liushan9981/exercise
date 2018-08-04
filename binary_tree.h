//
// Created by liushan on 18-8-3.
//

#ifndef EXERCISE_BINARY_TREE_H
#define EXERCISE_BINARY_TREE_H

#include <stdbool.h>

#define ITEM_NAME_MAX_SIZE 45
#define BINTREE_MAX_SIZE 10

typedef struct item {
    char name[ITEM_NAME_MAX_SIZE];
    char kind[ITEM_NAME_MAX_SIZE];
} Item;

typedef struct trnode {
    Item item;
    struct trnode * left;
    struct trnode * right;
} Trnode;


typedef struct bin_tree {
    Trnode * root;
    int size;
} BinTree;


void BinTreeInitialize(BinTree * btptr);

bool BinTreeIsEmpty(const BinTree * btptr);

bool BinTreeIsFull(const BinTree * btptr);

int BinTreeItemsCount(const BinTree * btptr);

bool BinTreeAddItem(Item * item, BinTree * btptr);

bool BinTreeItemIsIn(Item * item, BinTree * btptr);

bool BinTreeDeleteItem(const Item * item, BinTree * btptr);

void BinTreeTranverse(const BinTree * btptr, void (*func) (Item * item) );

void BinTreeDeleteAll(BinTree * btptr);

#endif //EXERCISE_BINARY_TREE_H
