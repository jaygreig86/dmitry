#ifndef _PORT_SOCK_H
#define _PORT_SOCK_H

int sock_con(char *host, int port, int ttl);
void banner(char *readbuff, int readsize);
void sig_alrm(int signo);

#endif
