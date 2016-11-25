#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/uio.h>
#include <unistd.h>
        struct sockaddr_in sock;        /* Structure for socket address         */
        long address;                   /* Remote IP (4 octet) address          */
        struct hostent *ph;
        int tcp_sock;
	struct in_addr **pptr;
	int con_sock;
