#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "combination.h"
#include "ioredirect.h"
#include "fields.h"
#include "dualview.h"
#include "aliases.h"
#include "byte_order.h"
#include "addr_trans.h"
#include "mysignal.h"

#include "echo_run.h"
#include "rio_read_write.h"
#include "myreaddir.h"
#include "mypasswd.h"
#include "myuname.h"
#include "mytime.h"
#include "film2.h"
#include "film3.h"


int main(int argc, char *argv[])
{
    film3(100000);

    return 0;
}


