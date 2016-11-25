#include <string.h>
#include "tcp_sock.h"
#include "file.h"
char ch;
char write_l[128];
char uptime[128];
char os[32];
char recvbuff[128];
char sendbuff[255];
char temp[1024];
int check;
int ctr;
int ctr2;
int ctr3;
int tmp = 0;
extern int tcp_socket(char *host, int port);
extern void readData(char *readbuff, int readsize);
extern void sendData(char *sendbuff, int sendsize);
extern int file_open();
extern int file_close();
extern char outputfile[64];
extern void tcp_sockdcon();
extern void print_line();

