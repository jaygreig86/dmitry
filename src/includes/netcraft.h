#include <string.h>
#include "tcp_sock.h"
#include "file.h"
extern char ch;
extern char write_l[128];
extern char uptime[128];
extern char os[32];
extern char recvbuff[128];
extern char sendbuff[255];
extern char temp[1024];
extern int check;
extern int ctr;
extern int ctr2;
extern int ctr3;
extern int tmp;
extern int tcp_socket(char *host, int port);
extern void readData(char *readbuff, int readsize);
extern void sendData(char *sendbuff, int sendsize);
extern int file_open();
extern int file_close();
extern char outputfile[64];
extern void tcp_sockdcon();
extern void print_line(char *string, char *string2);

