#ifndef RIO_H
#define RIO_h

#include<stdio.h>

#define RIO_BUFSIZE 8192

typedef struct{
	int rio_fd;
	int rio_cnt;
	char *rio_bufptr;
	char rio_buf[RIO_BUFSIZE];
}rio_t;

ssize_t rio_readn(int fd,void *usrbuf, size_t n);
ssize_t rio_written(int fd, void *usrbuf, size_t n);
void rio_readinitb(rio_t *rp, int fd);
ssize_t rio_readlineb(rio_t *rp, void *usrbuf, size_t maxlen);
ssize_t rio_readnb(rio_t *rp, void *usrbuf, size_t n);

#endif
