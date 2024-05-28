#include "includes/iwhois.h"

int get_iwhois(char *host)
{
	int hostn;
	char linebuff[128];
	linetodo = 0;
	if ( strlen(outputfile) ) file_open();	/* Are we outputting to a file? */
	/* Print introduction to function */
	memset(linebuff, '\0', sizeof(linebuff));
	snprintf(linebuff, sizeof(linebuff), "\nGathered Inet-whois information for %s\n", host);
	print_line("%s", linebuff);

	memset(linebuff, '\0', sizeof(linebuff));
	snprintf(linebuff, sizeof(linebuff), "---------------------------------\n\n");
	print_line("%s", linebuff);
	if (! host[0] ){
		print_line("ERROR: No Host IP to work from\n");
		if ( strlen(outputfile) ) file_close();
		return 0;
	}
	for(hostn=0;hostn < MAXHOSTS;hostn++){
		if (!tcp_socket(ip_whois_hosts[hostn], 43)){
			if ( hostn == 1 ) snprintf(query, sizeof(query), "+%s\n", host);
			else snprintf(query, sizeof(query), "%s\r\n", host);

			if (ip_string_search(hostn) == 1){
				tcp_sockdcon();
				if ( strlen(outputfile) ) file_close();
				return 0;
			}
			else if ( hostn == 3 ) print_line("ERROR: Unable to locate Inetnum Whois data on %s\n", host);
		}
		else print_line("ERROR: Connection to InetWhois Server %s failed\n", ip_whois_hosts[hostn]);
		tcp_sockdcon();
	}
	if ( strlen(outputfile) ) file_close();
	return 0;
}

int ip_string_search(int server)
{
	char buff[512];
	int found = 0;	/* Has the domain been found */

	/* Send query string */

	sendData(query, strlen(query));

	do {
		memset(buff, '\0', sizeof(buff));
		readData(buff, 500);
		if ( strstr(buff, ip_error_find[server]) || strstr(buff, "0.0.0.0") || strstr(buff, "Not assigned to ")){
			return 0;
		}
		if (strstr(buff, ip_read_begin[server]) || found ){
			found = 1;
			if ( ip_format_buff(buff, server) ) return 1;
		}
	} while(buff[0] != '\0');

	tcp_sockdcon();
	return 1;
}

/* Format the lines within the received buffer
   each new line is printed seperately i.e.
   blah\n > sent
   blahblah\n > sent
   hello\n > sent
   instead of
   blah\nblahblah\nhello\n > sent
*/ 

int ip_format_buff(char *buff, int server)
{
	char frmtdbuff[256]; 	/* This is the buffer containing formatted lines */
	int ctr;		/* Character Counter */
	int firstpacket;
	firstpacket = 0;
	ctr = 0;
	if ( strstr(buff, ip_read_begin[server]) ) firstpacket = 1; /* This packet contains the first line to output... somewhere */
	if (!linetodo) memset(frmtdbuff, '\0', sizeof(frmtdbuff)); 
	while(buff[ctr] != '\0'){
		if ( buff[ctr] == '\n' ){
			if ( firstpacket == 0 || ( firstpacket == 1 && strstr(frmtdbuff, ip_read_begin[server]))){
				print_line("%s\n", frmtdbuff);
				firstpacket = 0;
			}
			if (strstr(frmtdbuff, ip_read_end[server]) && strstr(buff, "\n\n\n\n")) return 1;
			memset(frmtdbuff, '\0', sizeof(frmtdbuff));
			
			linetodo = 0;
			ctr++;
		}
		frmtdbuff[strlen(frmtdbuff)] = buff[ctr];
		ctr++;
	}
	if ( strlen(frmtdbuff) ) linetodo = 1;
	return 0;
}
