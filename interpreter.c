//
// Created by liushan on 18-11-11.
//

#include "interpreter.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/unistd.h>
#include <sys/wait.h>


/*
 * /home/liushan/mylab/clang/test_interpreter 文件内容如下
 * #!/home/liushan/mylab/clang/prargv foo
 * 此示例执行和输出如下：
    [liushan@liushan-pc clang]$ /home/liushan/mylab/clang/exercise/cmake-build-debug/exercise
    argv[0]: /home/liushan/mylab/clang/prargv
    argv[1]: foo
    argv[2]: /home/liushan/mylab/clang/test_interpreter
    argv[3]: arg1
    argv[4]: arg2
    GS_LIB=/home/liushan/.fonts
    KDE_FULL_SESSION=true
    此处略去部分内容
 */

void run_interpreter(void)
{
    pid_t pid;

    if ( (pid = fork() ) < 0)
    {
        printf("fork error\n");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        if (execl("/home/liushan/mylab/clang/test_interpreter", "test_interpreter", "arg1", "arg2", (char * ) 0) < 0)
        {
            printf("execl error\n");
            exit(EXIT_FAILURE);
        }
    }

    if (waitpid(pid, NULL, 0) < 0)
    {
        printf("wait error\n");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}