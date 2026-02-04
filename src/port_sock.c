/* TCP Socket header (Modified for Portscan.c)
 * Coded by James Greig
 *
 * James@mor-pah.net
 * Date: 16/06/03
 */
/* TCP Socket construction */
#include "includes/port_sock.h"
#include "includes/tcp_sock.h" // For tcp_sock
#include "includes/config.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/uio.h>
#include <unistd.h>
#include <setjmp.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>


static sigjmp_buf _port_sock_jmpbuf;

// extern int tmp;


// struct hostent* ph;
// int tcp_sock;
// struct in_addr** pptr;
// int con_sock;

int sock_con(char* host, int port, int ttl)
{
    struct sockaddr_in sock; /* Structure for socket address         */
    long address; /* Remote IP (4 octet) address          */
    signal(SIGALRM, sig_alrm);
    close(tcp_sock);
    tcp_sock = 0;

    address = inet_addr(host);
    sock.sin_addr.s_addr = address;
    sock.sin_family = AF_INET;
    sock.sin_port = htons(port);

    if ((tcp_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        return 3;
    }
    alarm(ttl);

#ifdef HAVE_SIGSETJMP_F
    if (sigsetjmp(_port_sock_jmpbuf, 1) != 0) {
#else
    if (__sigsetjmp(_port_sock_jmpbuf, 1) != 0) {
#endif
        return 2;
    }

    if (connect(tcp_sock, (struct sockaddr*)&sock, sizeof(sock)) < 0) {
        return 1;
    }

    return 0;
}

void banner(char* readbuff, int readsize)
{
    ssize_t bytes_read;

    if (readsize <= 0) {
        return;
    }

    memset(readbuff, '\0', readsize); /* Clear read buffer (null) */
    bytes_read = read((int)tcp_sock, (char*)readbuff, (int)readsize - 1);
    if (bytes_read <= 0) {
        readbuff[0] = '\0';
        return;
    }
    readbuff[bytes_read] = '\0';
    printf(">> %s\n", readbuff);
}

void sig_alrm(__attribute__((unused)) int signo)
{
    siglongjmp(_port_sock_jmpbuf, 1);
    printf("werd\n");
    return;
}
