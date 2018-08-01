//
// Created by liushan on 18-8-1.
//

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#include "queue.h"
#include "mall.h"

#define MIN_PER_HR 60.0

bool newcustomer(double x);
Item customertime(long when);


void mall(void)
{
    Queue line;
    Item temp;
    int hours;
    int perhour;
    long cycle, cyclelimit;
    long turnaways = 0;
    long customers = 0;
    long served = 0;
    long sum_line = 0;
    int wait_time = 0;
    double min_per_cust;
    long line_wait = 0;



    QueueInitialize(&line);
    srand( (unsigned int) time(0) );

    // 输入的样本
    hours = 800;
    perhour = 20;


    cyclelimit = MIN_PER_HR * hours;
    min_per_cust = MIN_PER_HR / perhour;


    // 用循环，来抽象时间，类似unix时间戳
    for (cycle = 0; cycle < cyclelimit; cycle++)
    {
        if (newcustomer(min_per_cust) )
        {
            if (QueueIsFull(&line) )
                turnaways++;
            else
            {
                customers++;
                temp = customertime(cycle);
                QueueProd(&line, &temp);
            }
        }

        // wait_time为每个客户的服务时间，客户的服务时间降至0，则从队列中获取下一个客户
        if (wait_time <= 0 && !QueueIsEmpty(&line) )
        {
            QueueCons(&line, &temp);
            wait_time = temp.processtime;
            // 类似这样： 当前时间戳，减去用户到达时的时间戳，即为用户的等待时间
            line_wait += cycle - temp.arrive;
            served++;
        }
        // 随着时间过去1秒， wait_time自减1
        if (wait_time > 0)
            wait_time--;
        sum_line += QueueCount(&line);
    }


    if (customers > 0)
    {
        printf("customers: %ld\n", customers);
        printf("served: %ld\n", served);
        printf("turnaways: %ld\n", turnaways);
        printf("average queue size: %.2f\n", (double) sum_line / cyclelimit);
        printf("average wait time: %.2f minutes\n", (double) line_wait / served);
    }
    else
        printf("No customers\n");

    QueueEmpty(&line);

}


// x分之一的可能为true
bool newcustomer(double x)
{
    if (rand() * x / RAND_MAX < 1)
        return true;
    else
        return false;
}


Item customertime(long when)
{
    Item cust;

    cust.processtime = rand() % 3 + 1;
    cust.arrive = when;

    return cust;
}


