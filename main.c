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
#include "test_queue.h"
#include "mall.h"
#include "test_bin_tree.h"
#include "myprintf.h"
#include "create_tempfile.h"
#include "myfork.h"
#include "pr_exit.h"
#include "fork_twice.h"
#include "run_exec.h"
#include "run_setuid.h"
#include "interpreter.h"
#include "mysystem.h"
#include "proc_nice.h"
#include "proc_time.h"
#include "orphan_process.h"

#include <string.h>
#include <errno.h>


int main(int argc, char *argv[])
{
    run_orphan_process();

    return 0;
}


