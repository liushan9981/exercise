//
// Created by liushan on 18-8-11.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "create_tempfile.h"


void test_tempfile(void);

void test_mkdtemp(void);


void create_temp_file_dir(void)
{
    test_tempfile();
    test_mkdtemp();
}


void test_tempfile(void)
{
    FILE * fp;
    char line[1024];

    if ( (fp = tmpfile() ) == NULL)
    {
        printf("create tempfile error\n");
        exit(EXIT_FAILURE);
    }

    fprintf(fp, "add one line\n");
    rewind(fp);
    while ( fgets(line, sizeof(line), fp) != NULL)
        printf("%s", line);
}

void test_mkdtemp(void)
{
    char dirtemplate[] = "/tmp/liushanXXXXXX";
    char filetemplate[] = "/tmp/shanshanXXXXXX";
    int fd;
    char line[1024];


    printf("dirtemplate: %s\n", dirtemplate);
    printf("filetemplate: %s\n", filetemplate);

    if (mkdtemp(dirtemplate) == NULL)
    {
        printf("create temp dir error\n");
        exit(EXIT_FAILURE);
    }

    if ( (fd = mkstemp(filetemplate) ) == -1)
    {
        printf("create temp file error\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        // 文件的目录项删除，文件仍然被打开，依旧能被当前进程访问
        if (unlink(filetemplate) == -1)
            printf("unlink template file error\n");
    }

    printf("dirtemplate: %s\n", dirtemplate);
    printf("filetemplate: %s\n", filetemplate);

    write(fd, "this is 1\n", sizeof("this is 1\n") );
    lseek(fd, 0, SEEK_SET);

    while ( read(fd, line, sizeof(line) ) != 0)
        printf("%s", line);

    sleep(30);
    printf("bye!\n");

    // 显式的删除临时目录
    if (rmdir(dirtemplate) == -1)
        printf("rmdir error\n");

}