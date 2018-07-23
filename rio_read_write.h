#define RIO_BUFSIZE 4096

typedef struct {
    int rio_fd;
    int rio_cnt;
    char * rio_bufptr;
    char rio_buf[RIO_BUFSIZE];
} rio_t;

void rio_readinitb(rio_t * rp, int fd);
ssize_t rio_writen(int fd, char * userch, size_t n);
ssize_t rio_readn(int fd, char * userch, size_t n);
void rio_run(void);
ssize_t rio_readlinb(rio_t * rp, void * usrbuf, size_t maxlen);
ssize_t rio_readnb(rio_t * rp, void * usrbuf, size_t n);
