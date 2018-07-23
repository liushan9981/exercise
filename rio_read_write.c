#include <stdio.h>
#include <stdlib.h>
#include <zconf.h>
#include <errno.h>
#include <memory.h>
#include <fcntl.h>
#include "rio_read_write.h"

void rio_readinitb(rio_t * rp, int fd)
{
    rp->rio_fd = fd;
    rp->rio_cnt = 0;
    rp->rio_bufptr = rp->rio_buf;
}


static ssize_t rio_read(rio_t * rp, char * userbuf, size_t n);
// 带缓冲，线程安全的IO
static ssize_t rio_read(rio_t * rp, char * userbuf, size_t n)
{
    int cnt;

    while (rp->rio_cnt <= 0)
    {
        rp->rio_cnt = read(rp->rio_fd, rp->rio_buf, sizeof(rp->rio_buf) );
        if (rp->rio_cnt < 0)
        {
            if (errno != EINTR)
                return -1;
        }
        else if (rp->rio_cnt == 0)
            return 0;
        else
            rp->rio_bufptr = rp->rio_buf;
    }

    cnt = n;
    if (rp->rio_cnt < n)
        cnt = rp->rio_cnt;
    memcpy(userbuf, rp->rio_bufptr, cnt);
    rp->rio_bufptr += cnt;
    rp->rio_cnt -= cnt;

    return cnt;
}

// 不带缓冲，写n字节，返回写的字节数
ssize_t rio_writen(int fd, char * userch, size_t n)
{
    ssize_t nleft = n;
    ssize_t nwrite;
    char * write_pos = userch;

    while (nleft >  0)
    {
        if ( (nwrite = write(fd, write_pos, nleft) ) < 0)
        {
            if (errno = EINTR)
                nwrite = 0;
            else
                return -1;
        }
        nleft -= nwrite;
        write_pos += nwrite;

    }

    return n;
}

// 不带缓冲，读n字节，返回读取的字节数
ssize_t rio_readn(int fd, char * userch, size_t n)
{
    ssize_t nleft = n;
    char * read_pos = userch;
    ssize_t read_bytes;


    while (nleft > 0)
    {
        if ( (read_bytes = read(fd, read_pos, nleft) ) < 0)
        {
            if (errno = EINTR)
                read_bytes = 0;
            else
                return -1;
        }
        else if (read_bytes == 0)
            break;

        nleft -= read_bytes;
        read_pos += read_bytes;
    }

    return n - nleft;
}


// 测试读写
void rio_run(void)
{
    rio_t rio;
    int fd;

    char usrbuf[5000];

    fd = open("/home/liushan/untitled/addr2.txt", O_RDONLY, 0);
    rio_readinitb(&rio, fd);
// 使用如下的语句，读取4999个字符的时候，会有异常，事实上只能正常读取少于4096个字符
//    rio_read(&rio, usrbuf, 4999);
//    usrbuf[4999] = 0;
//    printf("%s\n", usrbuf);

// 使用如下的语句，读取大于或者小于4096个字符的时候，表现正常。这是rio_readnb存在的意义
//    rio_readnb(&rio, usrbuf, 4999);
//    usrbuf[4999] = 0;
//    printf("%s\n", usrbuf);


    rio_readlinb(&rio, usrbuf, 4999);
    usrbuf[4999] = 0;
    printf("%s\n", usrbuf);
}

// 使用带缓冲的读，读取行
ssize_t rio_readlinb(rio_t * rp, void * usrbuf, size_t maxlen)
{
    int n, rc;
    char c, * bufp = usrbuf;

    for (n = 1; n < maxlen; n++)
    {
        if ( (rc = rio_read(rp, &c, 1)) == 1)
        {
            *bufp++ = c;
            if (c == '\n')
            {
                n++;
                break;
            }
        }
        else if (rc == 0)
        {
            if (n == 1)
                return 0;
            else
                break;
        }
        else
            return -1;
    }
    *bufp = 0;
    return n -1;
}

// 使用带缓冲的读，读取n字节
ssize_t rio_readnb(rio_t * rp, void * usrbuf, size_t n)
{
    size_t nleft = n;
    ssize_t nread;
    char *bufp = usrbuf;

    while (nleft > 0)
    {
        if ( (nread = rio_read(rp, bufp, nleft)) < 0)
            return -1;
        else if (nread == 0)
            break;
        nleft -= nread;
        bufp += nread;
        printf("debug nleft: %d\n", nleft);
    }

    return n - nleft;
}



