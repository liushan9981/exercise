
void echo_srv(void);
void str_srv(int sockfd);

void echo_srv_select(void);
void str_srv_select(int sockfd);
void echo_srv_poll(void);
void echo_srv_epoll(void);