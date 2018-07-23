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
        if ( (n = readn(sockfd, &args, sizeof(args) ) ) == 0)
            return;
        result.sum = args.arg1 + args.arg2;
        writen(sockfd, &result, sizeof(result) );

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
