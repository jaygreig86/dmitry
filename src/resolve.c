#include "includes/resolve.h"
#include "includes/file.h"
#include "includes/config.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#define MAXIPLEN 17
#define MAXNAMELEN 128
extern void print_line();
extern char outputfile[64];
extern int file_open();
extern int file_close();
struct hostent *hptr;
int get_host(char *host, char *dest)
{
	char www[128];
        char **pptr;
	unsigned long address;

	if (INADDR_NONE == ( address = inet_addr(host) )){
		/* Grab the IP address using the hostname */

	        if (!(hptr = gethostbyname(host))){
			memset(www, '\0', sizeof(www));
			snprintf(www, sizeof(www), "www.%s", host);
			if (!(hptr = gethostbyname(www))){
				return 0;
			}
		}
		pptr = hptr->h_addr_list;
		inet_ntop(hptr->h_addrtype, *pptr, dest, MAXIPLEN);
		return 1;
	} else {
		/* Grab the hostname using the IP address */
		if (! (hptr = gethostbyaddr((char *) &address, 4, AF_INET) )) return 0;

		snprintf(dest, MAXNAMELEN, "%s", hptr->h_name);
		return 1;
	}
	return 0;

}
