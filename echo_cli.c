#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <limits.h>
#include <errno.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <memory.h>
#include <zconf.h>
#include <sys/stat.h>

#include "writen_readn_readline.h"
#include "echo_sum.h"


void str_cli(FILE * fp, int sockfd)
{
    const int buffer_size = 4096;
    char sendline[buffer_size], recvline[buffer_size];

    struct args_t args;
    struct result_t result;

    while (fgets(sendline, buffer_size, fp) != NULL)
    {
        if (sscanf(sendline, "%ld%ld", &args.arg1, &args.arg2) != 2)
        {
            fprintf(stderr, "input error\n");
            continue;
        }

        writen(sockfd, &args, sizeof(args) );
        if (readn(sockfd, &result, sizeof(result) ) == 0)
        {
            fprintf(stderr, "str_cli: server terminated prematurely\n");
            exit(EXIT_FAILURE);
        }
        printf("result: %ld\n", result.sum);

//        if (readline(sockfd, recvline, buffer_size) == 0)
//        {
//            fprintf(stderr, "str_cli: server terminated prematurely\n");
//            exit(EXIT_FAILURE);
//        }
//        fputs(recvline, stdout);
    }
}


void echo_cli(char * ipaddr)
{
    int sockfd;
    struct sockaddr_in servaddr, cliaddr;
    int cliaddr_len;
    char addr_buf[INET_ADDRSTRLEN];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr) );
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(8000);
    inet_pton(AF_INET, ipaddr, &servaddr.sin_addr);


    if ( connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr) ) < 0)
    {
        fprintf(stderr, "connect error\n");
        exit(EXIT_FAILURE);
    }

    cliaddr_len = sizeof(cliaddr);
    if (getsockname(sockfd, (struct sockaddr * )&cliaddr, &cliaddr_len) == -1)
        printf("getsockname error!\n");
    else
    {
        printf("local ip: %s\n", inet_ntop(AF_INET, &cliaddr.sin_addr, addr_buf, INET_ADDRSTRLEN) );
        printf("local port: %d\n", ntohs(cliaddr.sin_port) );
    }

    str_cli(stdin, sockfd);

    exit(EXIT_SUCCESS);
}
