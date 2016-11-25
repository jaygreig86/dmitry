/* TCP Socket header (Modified for Portscan.c)
 * Coded by James Greig
 *
 * James@mor-pah.net
 * Date: 16/06/03
 */
/* TCP Socket construction */
#include "includes/port_sock.h"
#include <signal.h>
#include <setjmp.h>
#include "includes/config.h"
#include <string.h>
#include <stdio.h>
static sigjmp_buf jmpbuf;

static void sig_alrm();
extern int tmp;
int sock_con(char *host, int port, int ttl)
{
signal(SIGALRM, sig_alrm);
close(tcp_sock);
tcp_sock = 0;

address = inet_addr(host);

sock.sin_addr.s_addr = address;

sock.sin_family = AF_INET;

sock.sin_port = htons(port);

if((tcp_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
	return 3;
}
alarm(ttl);
#ifdef HAVE_SIGSETJMP_F
if (sigsetjmp(jmpbuf, 1) != 0 ) {
#else
if (__sigsetjmp(jmpbuf, 1) != 0 ) {
#endif
return 2;
}
if(connect(tcp_sock, (struct sockaddr *) &sock, sizeof (sock)) < 0) {
	return 1;
}

return 0;
}

void banner(char *readbuff, int readsize)
{
	memset(readbuff, '\0', readsize);      	/* Clear read buffer (null) */
	read((int) tcp_sock, (char *) readbuff, (int) readsize);
	printf(">> %s\n", readbuff);
}

void sig_alrm()
{
        siglongjmp(jmpbuf, 1);
	printf("werd\n");
        return;
}

