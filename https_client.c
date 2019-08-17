//
// Created by liushan on 19-6-1.
//

#include "https_client.h"

//#include <stdio.h>
//#include <memory.h>
//#include <errno.h>
//#include <sys/types.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
//#include <arpa/inet.h>
//#include <netdb.h>
//#include <zconf.h>

//#include <openssl/crypto.h>
//#include <openssl/x509.h>
//#include <openssl/pem.h>
//#include <openssl/ssl.h>
//#include <openssl/err.h>

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

int create_socket(int port)
{
    int s;
    struct sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) {
        perror("Unable to create socket");
        exit(EXIT_FAILURE);
    }

    if (bind(s, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("Unable to bind");
        exit(EXIT_FAILURE);
    }

    if (listen(s, 1) < 0) {
        perror("Unable to listen");
        exit(EXIT_FAILURE);
    }

    return s;
}

void init_openssl()
{
    SSL_load_error_strings();
    OpenSSL_add_ssl_algorithms();
}

void cleanup_openssl()
{
    EVP_cleanup();
}

SSL_CTX *create_context()
{
    const SSL_METHOD *method;
    SSL_CTX *ctx;

    method = SSLv23_server_method();

    ctx = SSL_CTX_new(method);
    if (!ctx) {
        perror("Unable to create SSL context");
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }

    return ctx;
}

void configure_context(SSL_CTX *ctx)
{
    SSL_CTX_set_ecdh_auto(ctx, 1);

    /* Set the key and cert */
    if (SSL_CTX_use_certificate_file(ctx, "/home/liushan/mylab/clang/cert/kubelet_node-4.crt", SSL_FILETYPE_PEM) <= 0) {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }

    if (SSL_CTX_use_PrivateKey_file(ctx, "/home/liushan/mylab/clang/cert/kubelet_node-4.key", SSL_FILETYPE_PEM) <= 0 ) {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }
}

int run_https_server(int argc, char **argv)
{
    int sock;
    SSL_CTX *ctx;

    init_openssl();
    ctx = create_context();

    configure_context(ctx);

    sock = create_socket(4433);

    /* Handle connections */
    while(1) {
        struct sockaddr_in addr;
        uint len = sizeof(addr);
        SSL *ssl;
        const char reply[] = "test\n";

        int client = accept(sock, (struct sockaddr*)&addr, &len);
        if (client < 0) {
            perror("Unable to accept");
            exit(EXIT_FAILURE);
        }

        ssl = SSL_new(ctx);
        SSL_set_fd(ssl, client);

        if (SSL_accept(ssl) <= 0) {
            ERR_print_errors_fp(stderr);
        }
        else {
            SSL_write(ssl, reply, strlen(reply));
        }

        SSL_free(ssl);
        close(client);
    }

    close(sock);
    SSL_CTX_free(ctx);
    cleanup_openssl();
}

















//void run_https_client(int argc, char ** argv)
//{
//    SSL * ssl;
//    SSL_CTX *ctx;
//    SSL_METHOD * client_method;
//    X509 * server_cert;
//    int sd, err;
//
//    char * str, * hostname, outbuf[4096], inbuf[4096], host_header[512];
//    struct hostent * host_entry;
//    struct sockaddr_in server_socket_address;
//    struct in_addr ip;
//
//    SSLeay_add_ssl_algorithms();
//    client_method = SSLv23_client_method();
//    SSL_load_error_strings();
//    ctx = SSL_CTX_new(client_method);
//    printf("1) SSL context initialized\n");
//
//    hostname = argv[1];
//    host_entry = gethostbyname(hostname);
//    bcopy(host_entry->h_addr_list, &(ip.s_addr), host_entry->h_length);
//    printf("2) %s -> %s", hostname, inet_ntoa(ip));
//
//    sd = socket(AF_INET, SOCK_STREAM, 0);
//    memset(&server_socket_address, 0, sizeof(server_socket_address));
//    server_socket_address.sin_family = AF_INET;
//    server_socket_address.sin_port = htons(443);
//    memcpy(&(server_socket_address.sin_addr.s_addr), host_entry->h_addr_list, host_entry->h_length);
//    err = connect(sd, (struct sockaddr *) &server_socket_address, sizeof(server_socket_address));
//    if (err < 0)
//    {
//        printf("can't connect to server port\n");
//        exit(EXIT_FAILURE);
//    }
//
//    printf("3) TCP connection open to host %s port %d\n", hostname, server_socket_address.sin_port);
//
//    ssl = SSL_new(ctx);
//    SSL_set_fd(ssl, sd);
//    err = SSL_connect(ssl);
//    printf("4) SSL handshake completed\n");
//    printf("cipher: %s\n", SSL_get_cipher(ssl));
//
//    server_cert = SSL_get_peer_certificate(ssl);
//    printf("recd cert\n");
//    str = X509_NAME_oneline(X509_get_subject_name(server_cert), 0, 0);
//    printf("subject: %s\n", str);
//    str = X509_NAME_oneline(X509_get_issuer_name(server_cert), 0, 0);
//    printf("issuer: %s\n", str);
//    X509_free(server_cert);
//
//    sprintf(host_header, "Host: %s:443\r\n", hostname);
//    strcpy(outbuf, "GET / HTTP/1.1\r\n");
//    strcat(outbuf, host_header);
//    strcat(outbuf, "Connection: close\r\n");
//    strcat(outbuf, "\r\n");
//
//    err = SSL_write(ssl, outbuf, strlen(outbuf));
//    shutdown(sd, 1);
//
//    printf("sent http header\n");
//
//    err = SSL_read(ssl, inbuf, sizeof(inbuf) - 1);
//    inbuf[err] = '\0';
//    printf("rec response: %s\n", inbuf);
//
//
//
//
//    SSL_shutdown(ssl);
//    close(sd);
//    SSL_free(ssl);
//    SSL_CTX_free(ctx);
//    printf("done\n");
//
//}
//


