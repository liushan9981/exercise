#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "combination.h"
#include "ioredirect.h"


int main(int argc, char *argv[])
{



    long num;


    for (num = 1; num <= 20; num++)
    {
        printf("%-2ld  ->  %-10ld\n", num, mynum(num) );
    }


    iore_print();





    return 0;
}


