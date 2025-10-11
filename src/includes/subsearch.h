#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define NCOL 40
#define MAXIPLEN 17
extern int tcp_socket(char *host, int port);
extern void readData(char *readbuff, int readsize);
extern void sendData(char *sendbuff, int sendsize);
extern int get_host(char *host, char *dest);
extern void tcp_sockdcon();
extern char outputfile[64];
extern int file_open();
extern void file_close();
extern void print_line(char *string, char *string2);
extern int tcp_sock;
extern int get_hoststring(char *host);
extern int subcount;
extern int grab_sub(char *buff, int pointer, char *host);
extern int sublist(char *sub, char *host);
extern char **subbuff;
extern int pagenumber; /* Used as a variable to store current page number (of results)*/
extern char pagestring[32]; /* The string to request a new page */

