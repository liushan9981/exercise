//
// Created by liushan on 18-8-3.
//

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "binary_tree.h"

typedef struct pair {
    Trnode * parent;
    Trnode * child;
} Pair;


static bool left_node(Trnode * trnodeptr, const Item * item);

static bool right_node(Trnode * trnodeptr, const Item * item);

static bool AddNode(Trnode * trnodeptr, Trnode * root);

static Pair SeekItem(const Item *item, BinTree *btptr);

static void DeleteNode(Trnode ** ptr);

static void InOrder(Trnode * ptr, void (*func) (Item * item) );

static void DeleteAllNode(Trnode * ptr);







void BinTreeInitialize(BinTree * btptr)
{
    btptr->root = NULL;
    btptr->size = 0;
}

bool BinTreeIsEmpty(const BinTree * btptr)
{
    return btptr->size == 0;
}


bool BinTreeIsFull(const BinTree * btptr)
{
    return (btptr->size == BINTREE_MAX_SIZE) ? true: false;
}



int BinTreeItemsCount(const BinTree * btptr)
{
    return btptr->size;
}



bool BinTreeAddItem(Item * item, BinTree * btptr)
{
    if (BinTreeIsFull(btptr) )
    {
        fprintf(stderr, "bintree is full\n");
        return false;
    }

    if (SeekItem(item, btptr).child != NULL)
    {
        fprintf(stderr, "attempt to add duplicate item\n");
        return false;
    }

    Trnode * trnodeptr;
    trnodeptr = (Trnode *) malloc(sizeof(Trnode) );
    if (trnodeptr == NULL)
    {
        fprintf(stderr, "malloc trnodeptr error\n");
        return false;
    }

    trnodeptr->item = *item;
    trnodeptr->left = NULL;
    trnodeptr->right = NULL;

    if (btptr->root == NULL)
    {
        btptr->root = trnodeptr;
        btptr->size++;
    }
    else
    {
        if (AddNode(trnodeptr, btptr->root))
            btptr->size++;
        else
            return false;
    }

    return true;
}


bool BinTreeItemIsIn(Item * item, BinTree * btptr)
{
    return (SeekItem(item, btptr).child == NULL) ? false: true;
}


bool BinTreeDeleteItem(const Item * item, BinTree * btptr)
{
    Pair look;

    look = SeekItem(item, btptr);
    if (look.child == NULL)
        return false;

    if (look.parent == NULL)
        DeleteNode(&btptr->root);
    else if (look.parent->left == look.child)
        DeleteNode(&look.parent->left);
    else if (look.parent->right == look.child)
        DeleteNode(&look.parent->right);

    btptr->size--;
    return true;
}


void BinTreeTranverse(const BinTree * btptr, void (*func) (Item * item) )
{
    if (btptr != NULL)
        InOrder(btptr->root, func);
}


void BinTreeDeleteAll(BinTree * btptr)
{
    if (btptr != NULL)
    {
        DeleteAllNode(btptr->root);
        btptr->root = NULL;
        btptr->size = 0;
    }

}


static void DeleteAllNode(Trnode * ptr)
{
    Trnode * right_ptr;

    if (ptr != NULL)
    {
        // 右侧的地址信息，在free ptr前需要保存到当前的变量
        right_ptr = ptr->right;
        DeleteAllNode(ptr->left);
        free(ptr);
        DeleteAllNode(right_ptr);
    }

}


static void InOrder(Trnode * ptr, void (*func) (Item * item) )
{
    if (ptr != NULL)
    {
        InOrder(ptr->left, func);
        func(&ptr->item);
        InOrder(ptr->right, func);
    }
}


static Pair SeekItem(const Item *item, BinTree *btptr)
{
    Pair look;

    look.parent = NULL;
    look.child = btptr->root;

    if (look.child == NULL)
        return look;

    while (look.child != NULL)
    {
        if (left_node(look.child, item) )
        {
            look.parent = look.child;
            look.child = look.child->left;
        }
        else if (right_node(look.child, item) )
        {
            look.parent = look.child;
            look.child = look.child->right;
        }
        else
            return look;
    }

    return look;
}



static bool AddNode(Trnode * trnodeptr, Trnode * root)
{

    if (left_node(root, &trnodeptr->item) )
    {
        if (root->left == NULL)
            root->left = trnodeptr;
        else
        {
            root = root->left;
            return AddNode(trnodeptr, root);
        }

    }
    else if (right_node(root, &trnodeptr->item) )
    {
        if (root->right == NULL)
            root->right = trnodeptr;
        else
        {
            root = root->right;
            return AddNode(trnodeptr, root);
        }
    }
    else
    {
        printf("from AddNode: find location error!\n");
        return false;
    }

    return true;
}


static void DeleteNode(Trnode ** ptr)
{
    Trnode * temp_ptr;

    if ( (*ptr)->left == NULL)
    {
        temp_ptr = *ptr;
        *ptr = (*ptr)->right;
        free(temp_ptr);
    }
    else if ( (*ptr)->right == NULL)
    {
        temp_ptr = *ptr;
        *ptr = (*ptr)->left;
        free(temp_ptr);
    }
    else
    {
        for (temp_ptr = (*ptr)->left; temp_ptr->right != NULL; temp_ptr = temp_ptr->right)
            continue;
        temp_ptr->right = (*ptr)->right;
        temp_ptr = *ptr;
        *ptr = (*ptr)->left;
        free(temp_ptr);
    }

}



static bool left_node(Trnode * trnodeptr, const Item * item)
{
    int comp1, comp2;

    if ( (comp1 = strcmp(trnodeptr->item.name, item->name) ) > 0)
        return true;
    else if (comp1 == 0 && (comp2 = strcmp(trnodeptr->item.kind, item->kind) ) > 0)
        return true;

    return false;
}


static bool right_node(Trnode * trnodeptr, const Item * item)
{
    int comp1, comp2;

    if ( (comp1 = strcmp(trnodeptr->item.name,  item->name) ) < 0)
        return true;
    else if (comp1 == 0 && (comp2 = strcmp(trnodeptr->item.kind, item->kind) ) < 0)
        return true;

    return false;
}






