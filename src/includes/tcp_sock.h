#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/uio.h>
#include <unistd.h>
#define MAX_TCP_CON 9
#define MAX_PART 20
#define STD_MSN_PORT 1863
        extern struct sockaddr_in sock;        /* Structure for socket address         */
        extern long address;                   /* Remote IP (4 octet) address          */
        extern struct hostent *ph;
        extern int tcp_sock;
        extern int args[2][1];
        extern char print[512];
        extern struct in_addr **pptr;
        extern int bind_sock;
        extern int con_sock;
        extern int irc_sock;
