//
// Created by liushan on 18-8-3.
//


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "test_bin_tree.h"
#include "binary_tree.h"


/*
    1. 添加成员
    2. 显示全部成员
    3. 显示成员数量
    4. 某个项目是否是该树的成员
    5. 删除某个成员
 */


void show_tree(Item * item);

void test_bin_tree(void)
{
    Item item;
    int i;
    int num[] = {5, 3, 2, 1, 4, 8, 7, 9, 10, 4, 7, 11, 12, 13, 14};
    BinTree tree;
    Item item_temp = {.name = "name_3", .kind = "kind_3"};

    BinTreeInitialize(&tree);



    if (BinTreeIsEmpty(&tree) )
        printf("#1 tree is empty\n");
    if (BinTreeIsFull(&tree) )
        printf("#1 tree is full\n");

    printf("#1 all items:\n");
    BinTreeTranverse(&tree, show_tree);

    // 添加项目
    for (i = 0; i < sizeof(num) / sizeof(int); i++)
    {
        snprintf(item.name, ITEM_NAME_MAX_SIZE - 1, "name_%d", num[i]);
        snprintf(item.kind, ITEM_NAME_MAX_SIZE - 1, "kind_%d", num[i]);
        BinTreeAddItem(&item, &tree);
    }


    printf("#1 bintree count: %d\n", BinTreeItemsCount(&tree) );


    if (BinTreeIsEmpty(&tree) )
        printf("#2 tree is empty\n");
    if (BinTreeIsFull(&tree) )
        printf("#2 tree is full\n");

    // 显示所有项目
    printf("#2 all items:\n");
    BinTreeTranverse(&tree, show_tree);

    // 查找某个项目
    printf("search %s  %s    ", item_temp.name, item_temp.kind);
    if (BinTreeItemIsIn(&item_temp, &tree) )
        printf("find \n");
    else
        printf("find not\n");



    // 删除某个成员
    if (BinTreeDeleteItem(&item_temp, &tree) )
        printf("delete item ok\n");
    else
        printf("delete item error\n");

    printf("#2 bintree count: %d\n", BinTreeItemsCount(&tree) );

    // 查找某个项目
    printf("#2 search %s  %s    ", item_temp.name, item_temp.kind);
    if (BinTreeItemIsIn(&item_temp, &tree) )
        printf("find \n");
    else
        printf("find not\n");

    printf("#3 all items:\n");
    BinTreeTranverse(&tree, show_tree);

    printf("\n\n");

    // 添加项目
    for (i = 0; i < sizeof(num) / sizeof(int); i++)
    {
        snprintf(item.name, ITEM_NAME_MAX_SIZE - 1, "name_%d", num[i]);
        snprintf(item.kind, ITEM_NAME_MAX_SIZE - 1, "kind_%d", num[i]);
        if (BinTreeDeleteItem(&item, &tree) )
            printf("delete item ok: %s  %s\n", item.name, item.kind);
        else
            printf("delete item fail: %s  %s\n", item.name, item.kind);
        // 显示所有项目
        printf("#last # %d all items count: %d:\n", i, BinTreeItemsCount(&tree));
        BinTreeTranverse(&tree, show_tree);
        printf("\n\n");
    }

    // 删除所有成员
    BinTreeDeleteAll(&tree);

    // 显示所有成员
    printf("---------\n");
    BinTreeTranverse(&tree, show_tree);





}



void show_tree(Item * item)
{
    printf("name: %s  kind: %s\n", item->name, item->kind);
}