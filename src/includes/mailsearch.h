#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define NCOL 50
extern int tcp_socket(char *host, int port);
extern void readData(char *readbuff, int readsize);
extern void sendData(char *sendbuff, int sendsize);
extern int get_host();
extern void tcp_sockdcon();
extern char outputfile[64];
extern int file_open();
extern void file_close();
extern void print_line(char *string, char *string2);
extern int tcp_sock;
extern int get_email_hoststring(char *host);
extern int emailcount;
extern int grab_emails(char *buff, int pointer, char *host);
extern int emaillist(char *email, char *host);
extern char **emailbuff;
extern int pagenumber; /* Used as a variable to store current page number (of results)*/
extern char pagestring[32]; /* The string to request a new page */

