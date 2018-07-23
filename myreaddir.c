//
// Created by liushan on 18-7-23.
//

#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <errno.h>

int myreaddir(void)
{
    DIR * stream_dir;
    struct dirent * dep;
    char * dirname = "/home/liushan/mylab/clang/hpc";

    stream_dir = opendir(dirname);
    if (stream_dir == NULL)
    {
        fprintf(stderr, "open dir \"%s\" failed\n", dirname);
        exit(EXIT_FAILURE);
    }

    errno = 0;
    while ( (dep = readdir(stream_dir) ) != NULL)
        printf("file: %s    with inode: %d\n", dep->d_name, dep->d_ino);
    if (errno != 0)
    {
        fprintf(stderr, "read directory error\n");
        exit(EXIT_FAILURE);
    }

    if (closedir(stream_dir) == -1)
    {
        fprintf(stderr, "close directory error\n");
        exit(EXIT_FAILURE);
    }

}