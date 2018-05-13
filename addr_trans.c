#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

void run_addr_trans(void)
{
    struct sockaddr_in sock;
    char temp[INET_ADDRSTRLEN] = "172.16.29.1";
    char temp2[INET_ADDRSTRLEN];
    char temp3[INET_ADDRSTRLEN];
    u_char * p_uc = (u_char *)&sock.sin_addr.s_addr;

    bzero(&sock, sizeof(sock) );
    // temp字符串转化为二进制存入到sock.sin_addr
    inet_pton(AF_INET, temp, &(sock.sin_addr));
    // sock.sin_addr的二进制转化为字符串存入到temp2
    inet_ntop(AF_INET, &(sock.sin_addr), temp2, INET_ADDRSTRLEN);
    printf("%d\n", sock.sin_addr.s_addr);
    printf("%s\n", temp2);
    printf("sizeof(u_char)  ->  %lu\n", sizeof(p_uc) );
    printf("sizeof(sock.sin_addr.s_addr)  ->  %lu\n", sizeof(sock.sin_addr.s_addr) );
    // 下面故意打印为诡异的格式, u_char 长度为1字节，sock.sin_addr.s_addr长度为4字节,可以使用指针访问
    fprintf(stdout, "%d:%d:%d:%d\n", p_uc[0], p_uc[1], p_uc[2], p_uc[3]);

}
