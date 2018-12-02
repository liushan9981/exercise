#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <limits.h>
#include <errno.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <strings.h>
#include <stdlib.h>
#include <memory.h>
#include <zconf.h>
#include <sys/stat.h>
#include <sys/poll.h>
#include <limits.h>

#include "writen_readn_readline.h"
#include "mysignal.h"
#include "echo_sum.h"


void str_srv(int sockfd)
{
    ssize_t n;
    const int buffer_size = 4096;
    char buf[buffer_size];
    struct args_t args;
    struct result_t result;

    while (1)
    {
        while ( (n = read(sockfd, buf, buffer_size) ) > 0)
            writen(sockfd, buf, n);
        if (n < 0 && errno == EINTR)
            continue;
        else if (n < 0)
        {
            fprintf(stderr, "str_echo: read error");
            exit(EXIT_FAILURE);
        }
        break;
    }


// 二进制读写
//    while (1)
//    {
//        if ( (n = readn(sockfd, &args, sizeof(args) ) ) == 0)
//            return;
//        result.sum = args.arg1 + args.arg2;
//        writen(sockfd, &result, sizeof(result) );

//        while ( (n = read(sockfd, buf, buffer_size) ) > 0)
//            writen(sockfd, buf, n);
//        if (n < 0 && errno == EINTR)
//            continue;
//        else if (n < 0)
//        {
//            fprintf(stderr, "str_echo: read error");
//            exit(EXIT_FAILURE);
//        }
//        break;
//    }
}

void echo_srv_select(void)
{
    int listenfd, connfd;
    socklen_t clilen;
    struct sockaddr_in cliaddr, servaddr;
    const int myqueue = 100;
    char addr_buf[INET_ADDRSTRLEN];
    int clifd[FD_SETSIZE];
    int maxfd, max_index, index, readyfdcount;
    fd_set rset, allset;
    ssize_t n;
    const int buffer_size = 4096;
    char buf[buffer_size];

    for (index = 0; index < FD_SETSIZE; index++)
        clifd[index] = -1;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    maxfd = listenfd;
    max_index = -1;

    bzero(&servaddr, sizeof(servaddr) );
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(8000);

    clilen = sizeof(cliaddr);

    FD_ZERO(&allset);
    FD_SET(listenfd, &allset);

    printf("start using select\n");

    if (bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr) ) == -1)
    {
        fprintf(stderr, "bind error\n");
        exit(EXIT_FAILURE);
    }

    if (listen(listenfd, myqueue) == -1)
    {
        fprintf(stderr, "listen error\n");
        exit(EXIT_FAILURE);
    }

    while(1)
    {
        rset = allset;
        printf("maxfd: %d, max_index: %d\n", maxfd, max_index);
        readyfdcount = select(maxfd + 1, &rset, NULL, NULL, NULL);

        if (FD_ISSET(listenfd, &rset) )
        {
            if ( (connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen) ) < 0)
            {
                // 重启被中断的系统调用accept
                if (errno == EINTR)
                    continue;
                    // accept返回前连接终止, SVR4实现
                else if (errno == EPROTO)
                    continue;
                    // accept返回前连接终止, POSIX实现
                else if (errno == ECONNABORTED)
                    continue;
                else
                {
                    printf("accept error!\n");
                    exit(EXIT_FAILURE);
                }
            }

            printf("peer ip: %s\n", inet_ntop(AF_INET, &cliaddr.sin_addr, addr_buf, INET_ADDRSTRLEN) );
            printf("peer port: %d\n", ntohs(cliaddr.sin_port) );

            for (index = 0; index < FD_SETSIZE; index++)
                if (clifd[index] < 0)
                {
                    clifd[index] = connfd;
                    break;
                }

            if (index >= FD_SETSIZE)
            {
                printf("conn is full\n");
                close(connfd);
                continue;
            }
            if (index > max_index)
                max_index = index;
            if (connfd > maxfd)
                maxfd = connfd;

            FD_SET(connfd, &allset);
            if (--readyfdcount <= 0)
                continue;
        }

        for (index = 0; index <= max_index; index++)
        {
            if (clifd[index] < 0)
                continue;

            if (FD_ISSET(clifd[index], &rset) )
            {
                if ( (n = read(clifd[index], buf, buffer_size) ) == 0)
                {
                    close(clifd[index]);
                    clifd[index] = -1;
                    FD_CLR(clifd[index], &allset);
                }
                else if (n < 0 && errno == EINTR)
                    continue;
                else if (n < 0)
                {
                    fprintf(stderr, "str_echo: read error");
                    exit(EXIT_FAILURE);
                }
                else if (n > 0)
                    writen(clifd[index], buf, n);

                if (--readyfdcount <= 0)
                    break;
            }
        }

    }

}




void echo_srv_poll(void)
{
    int listenfd, connfd;
    socklen_t clilen;
    struct sockaddr_in cliaddr, servaddr;
    const int myqueue = 100;
    char addr_buf[INET_ADDRSTRLEN];
    const int myopen_max = 1024;
    struct pollfd clifd[myopen_max];
    int max_index, index, readyfdcount;
    ssize_t n;
    const int buffer_size = 4096;
    char buf[buffer_size];

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    max_index = 0;
    clifd[0].fd = listenfd;
    clifd[0].events = POLLRDNORM;

    for (index = 1; index < myopen_max; index++)
        clifd[index].fd = -1;

    bzero(&servaddr, sizeof(servaddr) );
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(8000);

    clilen = sizeof(cliaddr);
    if (bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr) ) == -1)
    {
        fprintf(stderr, "bind error\n");
        exit(EXIT_FAILURE);
    }

    if (listen(listenfd, myqueue) == -1)
    {
        fprintf(stderr, "listen error\n");
        exit(EXIT_FAILURE);
    }

    printf("start using poll\n");
    while(1)
    {
        readyfdcount = poll(clifd, max_index + 1, -1);

        if (clifd[0].revents & POLLRDNORM)
        {
            if ( (connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen) ) < 0)
            {
                // 重启被中断的系统调用accept
                if (errno == EINTR)
                    continue;
                    // accept返回前连接终止, SVR4实现
                else if (errno == EPROTO)
                    continue;
                    // accept返回前连接终止, POSIX实现
                else if (errno == ECONNABORTED)
                    continue;
                else
                {
                    printf("accept error!\n");
                    exit(EXIT_FAILURE);
                }
            }

            printf("peer ip: %s\n", inet_ntop(AF_INET, &cliaddr.sin_addr, addr_buf, INET_ADDRSTRLEN) );
            printf("peer port: %d\n", ntohs(cliaddr.sin_port) );

            for (index = 1; index < myopen_max; index++)
                if (clifd[index].fd < 0)
                {
                    clifd[index].fd = connfd;
                    clifd[index].events = POLLRDNORM;
                    break;
                }

            if (index >= myopen_max)
            {
                printf("conn is full\n");
                close(connfd);
                continue;
            }

            if (index > max_index)
                max_index = index;

            if (--readyfdcount <= 0)
                continue;
        }

        for (index = 1; index <= max_index; index++)
        {
            if (clifd[index].fd < 0)
                continue;

            if (clifd[index].revents & (POLLRDNORM | POLL_ERR) )
            {
                if ( (n = read(clifd[index].fd, buf, buffer_size) ) == 0)
                {
                    close(clifd[index].fd);
                    clifd[index].fd = -1;
                }
                else if (n < 0 && errno == EINTR)
                    continue;
                else if (n < 0 && errno == ECONNRESET)
                {
                    close(clifd[index].fd);
                    clifd[index].fd = -1;
                }
                else if (n < 0)
                {
                    fprintf(stderr, "str_echo: read error");
                    exit(EXIT_FAILURE);
                }
                else if (n > 0)
                    writen(clifd[index].fd, buf, n);

                if (--readyfdcount <= 0)
                    break;
            }
        }

    }

}




void echo_srv(void)
{
    int listenfd, connfd;
    pid_t childpid;
    socklen_t clilen;
    struct sockaddr_in cliaddr, servaddr;
    void sig_child(int);
    const int myqueue = 100;
    char addr_buf[INET_ADDRSTRLEN];

    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr) );
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(8000);

    if (bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr) ) == -1)
    {
        fprintf(stderr, "bind error\n");
        exit(EXIT_FAILURE);
    }

    if (listen(listenfd, myqueue) == -1)
    {
        fprintf(stderr, "listen error\n");
        exit(EXIT_FAILURE);
    }

    printf("start using fork child\n");

    // 处理子进程，以防变成僵死进程
    signal(SIGCHLD, sig_chld);

    while (1)
    {
        clilen = sizeof(cliaddr);
        if ( (connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen) ) < 0)
        {
            // 重启被中断的系统调用accept
            if (errno == EINTR)
                continue;
            // accept返回前连接终止, SVR4实现
            else if (errno == EPROTO)
                continue;
            // accept返回前连接终止, POSIX实现
            else if (errno == ECONNABORTED)
                continue;
            else
            {
                printf("accept error!\n");
                exit(EXIT_FAILURE);
            }
        }

        printf("peer ip: %s\n", inet_ntop(AF_INET, &cliaddr.sin_addr, addr_buf, INET_ADDRSTRLEN) );
        printf("peer port: %d\n", ntohs(cliaddr.sin_port) );

        if ( (childpid = fork() ) < 0)
        {
            printf("fork error\n");
            exit(EXIT_FAILURE);
        }
        else if (childpid != 0)
        {
            // parent
            printf("fork child: %d\n", childpid);
            close(connfd);
        }
        else if (childpid == 0)
        {
            // child
            close(listenfd);
            str_srv(connfd);
            close(connfd);
            exit(0);
        }

    }


}
