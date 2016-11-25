/* TCP Socket header
 * Coded by James Greig
 * James@mor-pah.net
 * Date: 16/06/03
 */
/* TCP Socket construction */
#include "includes/tcp_sock.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>
int tcp_socket(char *host, int port)
{
	memset(&sock, '\0', sizeof(sock));
	if(isdigit(host[0])) {
		if ((address = inet_addr(host)) == -1) {
	                printf("Error: Unable to connect - Invalid Host\n");
			return 1;
			}

	        sock.sin_addr.s_addr = address;
	        
		}
        else {
                if(!(ph = gethostbyname(host))) {
                printf("Error: Unable to connect - Invalid Host\n");
		return 2;
                }

		pptr = (struct in_addr **) ph->h_addr_list;
		memcpy(&sock.sin_addr, *pptr, sizeof(struct in_addr));
        }

	sock.sin_family = AF_INET;

	/* Place port in sock information structure */

	sock.sin_port = htons(port);

	/* open socket */

	if(tcp_sock == 0) {
		if((tcp_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        		printf("Unable to connect: Error at socket build\n");
			return 3;
        	}
	
		/* Connet to remote host */

		if(connect(tcp_sock, (struct sockaddr *) &sock, sizeof (sock)) < 0) {
        		printf("Unable to connect: Socket Connect Error\n");
			return 4;
	        }
	return 0;
	}

	printf("Socket Error\n");
	return 1;
}

/* TCP Socket Disconnect */

void tcp_sockdcon()
{
if (close((int) tcp_sock)) printf("close error\n");
	tcp_sock = 0;

}

/* Read Data Function (Data IN)*/

void readData(char *readbuff, int readsize)
{
	memset(readbuff, '\0', readsize);      	/* Clear read buffer (null) */
	read((int) tcp_sock, (char *) readbuff, (int) readsize);
/*	printf(">> %s\n", readbuff); */
}

/* Send Data Function (Data OUT) */

void sendData(char *sendbuff, int sendsize)
{
	write((int) tcp_sock, (char *) sendbuff, (int) sendsize);
/*	printf("<< %s\n", sendbuff); */
}

