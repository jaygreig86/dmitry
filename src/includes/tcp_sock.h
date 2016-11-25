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
        struct sockaddr_in sock;        /* Structure for socket address         */
        long address;                   /* Remote IP (4 octet) address          */
        struct hostent *ph;
        int tcp_sock;
        int args[2][1];
        char print[512];
	struct in_addr **pptr;
	int bind_sock;
	int con_sock;
	int irc_sock;
