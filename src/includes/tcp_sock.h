#ifndef _TCP_SOCK_H
#define _TCP_SOCK_H

#define MAX_TCP_CON 9
#define MAX_PART 20
#define STD_MSN_PORT 1863

// For `close`
#include <unistd.h>

extern int tcp_sock;

int tcp_socket(char *host, int port);
void tcp_sockdcon();
void readData(char *readbuff, int readsize);
void sendData(char *sendbuff, int sendsize);

#endif
