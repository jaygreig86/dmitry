#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define NCOL 40
#define MAXIPLEN 17
extern int tcp_socket();
extern void readData();
extern void sendData();
extern int get_host();
extern void tcp_sockdcon();
extern char outputfile[64];
extern void file_open();
extern void file_close();
extern void print_line();
extern int tcp_sock;
int get_hoststring();
int subcount;
int grab_sub();
int sublist();
char **subbuff;
int pagenumber; /* Used as a variable to store current page number (of results)*/
char pagestring[32]; /* The string to request a new page */

