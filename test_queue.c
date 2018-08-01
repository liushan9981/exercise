//
// Created by liushan on 18-8-1.
//


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "test_queue.h"
#include "queue.h"


void test_queue(void)
{
    char ch;
    Item item;

    Queue queue;

    QueueInitialize(&queue);

    printf("input 'a' to add, input 'd' to consume, 'q' to quit: ");
    while ( (ch = getchar() ) != 'q')
    {
        if ( ch != 'a' && ch != 'd')
            continue;

        if (ch == 'a')
        {
            printf("produce an integer: ");
            scanf("%d", &item);

            if (QueueProd(&queue, &item) )
                printf("add integer '%d' OK\n", item);
            else
                printf("add integer '%d' Failed\n", item);
            printf("count item in Queue: %d\n", QueueCount(&queue) );
        }
        else
        {
            if (! QueueIsEmpty(&queue) )
            {
                printf("consume an integer: ");
                QueueCons(&queue, &item);
                printf("%d\n", item);
            }
            else
                printf("no data to consume\n");
        }

        printf("input 'a' to add, input 'd' to consume, 'q' to quit: ");
    }

    printf("#2 count item in Queue: %d\n", QueueCount(&queue) );
    QueueEmpty(&queue);
    printf("#3 count item in Queue: %d\n", QueueCount(&queue) );

}
