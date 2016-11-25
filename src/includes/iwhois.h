#include <sys/time.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include "tcp_sock.h"
#include "file.h"
#define MAXHOSTS 4
int result;
int check = 0;
int ctr2 = 0;
int check2 = 0;
int tmp;
int ctr3;
int ctr4;
int ctr;
char ch;
char netb[64];
char filebuff[1024];
char recvbuff[128];
char sendbuff[255];
extern int tcp_socket();
extern void tcp_sockdcon();
extern void readData();
extern void print_line();
extern void sendData();
int ip_string_search();
int get_iwhois();
int ip_format_buff();
int linetodo;   /* This is used to symbolise to ip_format_buff() that there is a line still to format */
char query[26];
extern char outputfile[64];
extern void file_open();
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

