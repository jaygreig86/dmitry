#include <sys/time.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include "tcp_sock.h"
#include "file.h"
#define MAXHOSTS 4
extern int result;
extern int check;
extern int ctr2;
extern int check2;
extern int tmp;
extern int ctr3;
extern int ctr4;
extern int ctr;
extern char ch;
extern char netb[64];
extern char filebuff[1024];
extern char recvbuff[128];
extern char sendbuff[255];
extern int tcp_socket(char *host, int port);
extern void tcp_sockdcon();
extern void readData(char *readbuff, int readsize);
extern void print_line(char *string, char *string2);
extern void sendData(char *sendbuff, int sendsize);
int ip_string_search(int server);
extern int get_iwhois(char *host);
int ip_format_buff(char *buff, int server);
extern int linetodo;   /* This is used to symbolise to ip_format_buff() that there is a line still to format */
extern char query[26];
extern char outputfile[64];
extern int file_open();
extern void file_close();

char *ip_whois_hosts[] = {
"whois.ripe.net",
"whois.arin.net",
"whois.lacnic.net",
"whois.apnic.net",
};

char *ip_error_find[]={
"No entries found",
"No match found ",
"No match for ",
"No entries found "
};

char *ip_read_begin[]={
"inetnum:",
"OrgName:",
"inetnum:",
"inetnum:",
};

/* Not all servers require an end string as the
   data may just end when the connection is closed
*/

char *ip_read_end[]={
"source",
"# ARIN WHOIS database",
"changed:",
"source:",
};

