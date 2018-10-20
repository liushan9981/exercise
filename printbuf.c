//
// Created by liushan on 18-8-11.
//



#include <stdio.h>
#include <stdlib.h>
#include "printbuf.h"



int isunbuffered(FILE * fp);

int is_linebuffered(FILE * fp);

int buffer_size(FILE * fp);


void pr_stdio(const char * name, FILE * fp);

void printbuf(void)
{
    FILE * fp;


    fputs("enter any character\n", stdout);
    if (getchar() == EOF)
    {
        printf("get char error\n");
        exit(EXIT_FAILURE);
    }

    fputs("one line to standard error\n", stderr);


    if ( (fp = fopen("/home/liushan/mylab/clang/liushan.txt", "r") ) == NULL)
    {
        printf("open file error\n");
        exit(EXIT_FAILURE);
    }

    if (getc(fp) == EOF)
    {
        printf("getc error\n");
        exit(EXIT_FAILURE);
    }

    pr_stdio("stdin", stdin);
    pr_stdio("stdout", stdout);
    pr_stdio("stderr", stderr);

    pr_stdio("/home/liushan/mylab/clang/liushan.txt", fp);

}

#if defined(_IO_UNBUFFERED)
int isunbuffered(FILE * fp)
{
    return (fp->_flags & _IO_UNBUFFERED);
}

int is_linebuffered(FILE * fp)
{
    return (fp->_flags & _IO_LINE_BUF);
}


int buffer_size(FILE * fp)
{
    return (fp->_IO_buf_end - fp->_IO_buf_base);
}


void pr_stdio(const char * name, FILE * fp)
{
    printf("stream = %s ", name);
    if (isunbuffered(fp) )
        printf("unbuffered");
    else if (is_linebuffered(fp) )
        printf("line_buffered");
    else
        printf("fully_buffered");
    printf(", buffer size = %d\n", buffer_size(fp) );
}

#endif