//
// Created by liushan on 18-7-30.
//


#include <stdio.h>
#include <stdlib.h>
#include "list.h"




bool InitializeList(List * plist)
{
    (*plist) = NULL;
}



bool ListIsEmpty(const List * plist)
{
    if ( (*plist) == NULL)
        return true;
    else
        return false;
}



bool ListIsFull(List * plist)
{
    Node * nodeptr;


    if ( (nodeptr = (Node *) malloc(sizeof(Node) ) ) == NULL)
    {
        fprintf(stderr, "plist is full\n");
        return true;
    }
    else
    {
        free(nodeptr);
        return false;
    }

}


unsigned int ListCount(const List * plist)
{
    unsigned int count = 0;
    Node * seek = (*plist);

    while (seek != NULL)
    {
        ++count;
        seek = seek->next;
    }

    return count;
}


bool ListAddItem(List * plist, const Item * item)
{
    Node * seek;
    Node * node_temp;

    if ( (node_temp = (Node *)malloc(sizeof(Node) ) ) != NULL)
    {
        node_temp->item = *item;
        node_temp->next = NULL;
    }
    else
        return false;

    if ( (*plist) == NULL)
        (*plist) = node_temp;
    else
    {
        seek = (*plist);
        while (seek->next != NULL)
            seek = seek->next;
        seek->next = node_temp;
    }

    return true;

}


void ListTraverse(const List * plist, void (* item_func) (Item * item) )
{
    Node * seek = (*plist);

    while (seek != NULL)
    {
        item_func(&(seek->item) );
        seek = seek->next;
    }

}



void ListEmpty(List * plist)
{
    Node * seek = (*plist);

    while (seek != NULL)
    {
        (*plist) = seek->next;
        free(seek);
        seek = (*plist);
    }
}

