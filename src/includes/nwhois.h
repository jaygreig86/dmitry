#include <stdio.h>
#include <string.h>
#include "file.h"
#include "tcp_sock.h"
extern int tcp_socket(char *host, int port);
extern void tcp_sockdcon();
extern void readData(char *readbuff, int readsize);
extern void print_line(char *string, char *string2);
extern void sendData(char *sendbuff, int sendsize);
int nic_string_search(char *host);
int get_td(char *host);
int get_whois();
extern int nic_format_buff(char *buff, int listn);
extern char td[10];
extern char query[128];
extern int linetodo;   /* This is used to symbolise to nic_format_buff() that there is a line still to format */
extern char outputfile[64];
extern int file_open();
extern void file_close();


char *nic_whois_hosts[]={
"whois.crsnic.net",
"whois.nic.ad.jp",
};

char *nic_error_find[]={
"No match",
"no match",
"No entries found for ",
"No domain records ",
"is not registered",
"NOT FOUND",
"not found",
"No Data Found",
"No data ",
"Not found:",
"no entries found",
"NO MATCH",
};

char *nic_read_begin[]={
"Domain Name: ",
"Registrant:",
"Domain Information:",
"domain:",
"Domain:",
"Domain-name",
"Domain Name",
};

/* Not all servers require an end string as the 
   data may just end when the connection is closed
*/

char *nic_read_end[]={
">>> Last update",
"",
"--",
"[Fax]",
"source:",
"",
"",
"",
};

