#include "includes/nwhois.h"

int get_nwhois(char *host)
{
	int hostn;
	char fhost[128];	/* Host with www removed */
	char linebuff[128];
	char server[64];

	int ctr;
	linetodo = 0;
	if ( strlen(outputfile) ) file_open();

        /* remove www. */
	memset(fhost, '\0', sizeof(fhost));
        if ( host[0] == 'w' && host[1] == 'w' && host[2] == 'w' && host[3] == '.'&& strlen(host) > 9 ) {
                ctr = 4;
                do {
                if ( host[ctr] != '\n' && host[ctr] != '\0' ) fhost[ctr-4] = host[ctr];
                ctr++;
                } while ( host[ctr] != '\n' && host[ctr] != '\0' );
        }
        else strcpy(fhost, host);

	/* Print introduction to function */
	memset(linebuff, '\0', sizeof(linebuff));
	snprintf(linebuff, sizeof(linebuff), "\nGathered Inic-whois information for %s\n", fhost);
	print_line("%s", linebuff);

	memset(linebuff, '\0', sizeof(linebuff));
	snprintf(linebuff, sizeof(linebuff), "---------------------------------\n");
	print_line("%s", linebuff);

	/* TopLevelDomain output */
	if (!( hostn = get_td(fhost) )){
		snprintf(server, sizeof(server), "%s.whois-servers.net", td);
	} else strcpy(server, nic_whois_hosts[hostn - 1]);

	if (!tcp_socket(server, 43)){
		nic_string_search(fhost);
	}
	else print_line("ERROR: Connection to InicWhois Server %s failed\n", server);
	if ( strlen(outputfile) ) file_close();
	tcp_sockdcon();
	return 0;
}

int nic_string_search(char *host)
{
	char buff[512];
	int listn;
	int found = 0;	/* Has the domain been found */
	/* Send query string */
	sendData(query, strlen(query));
	do{
		memset(buff, '\0', sizeof(buff));
		readData(buff, 500);
		for(listn=0;listn < 12;listn++){
			if ( strstr(buff, nic_error_find[listn])){
				print_line("ERROR: Unable to locate Name Whois data on %s\n", host);
				return 0;
			}
		}
		for(listn=0;listn < 7;listn++){
			if ( strstr(buff, nic_read_begin[listn]) || found == 1){
				if ( nic_format_buff(buff, listn) ) return 0;
				found = 1;
				break;
			}
		}
	} while(buff[0] != '\0');

	return 0;
}

int get_td(char *host)
{
	/* Get the top level domain in reverse order .uk .com etc*/
	int ctr;	
	memset(query, '\0', sizeof(query));
	memset(td, '\0', sizeof(td));
	ctr = strlen(host) - 1;
	do {
		ctr--;
	} while(host[ctr] != '.' && ctr > 0);

	ctr++;

	do {
		td[strlen(td)] = host[ctr];
		ctr++;
	} while(host[ctr] != '\0');

	if (! strcmp(td, "com") || ! strcmp(td, "net") ){
		snprintf(query, sizeof(query), "=%s\r\n", host);
		return 1;
	}
        if (! strcmp(td, "jp")){
                snprintf(query, sizeof(query), "%s/e\r\n", host);
                return 2;
        }
        if (! strcmp(td, "de")){
                snprintf(query, sizeof(query), "-T dn %s\r\n", host);
		return 0;
        }

	snprintf(query, sizeof(query), "%s\r\n", host);
	return 0;
}

/* Format the lines within the received buffer
   each new line is printed seperately i.e.
   blah\n > sent
   blahblah\n > sent
   hello\n > sent
   instead of
   blah\nblahblah\nhello\n > sent
*/ 

int nic_format_buff(char *buff, int listn)
{
	char frmtdbuff[128]; 	/* This is the buffer containing formatted lines */
	int ctr = 0;		/* Character Counter */
	int firstpacket = 0;
	if (!linetodo) memset(frmtdbuff, '\0', sizeof(frmtdbuff)); 
	if ( strstr(buff, nic_read_begin[listn]) ) firstpacket = 1;
	while(buff[ctr] != '\0'){
		if ( buff[ctr] == '\n' ){
			if ( firstpacket == 0 || ( firstpacket == 1 && strstr(frmtdbuff, nic_read_begin[listn]))){
				print_line("%s\n", frmtdbuff);
				firstpacket = 0;
				if ( buff[ctr] == '\n' && buff[ctr + 1] == '\n' && buff[ctr + 2] == '\n' ) return 1;
			}
			memset(frmtdbuff, '\0', sizeof(frmtdbuff));
			linetodo = 0;
			ctr++;
		}
		frmtdbuff[strlen(frmtdbuff)] = buff[ctr];
		ctr++;
		if (strlen(frmtdbuff) >= sizeof(frmtdbuff) - 1) {
			/* frmtdbuff is full, do not let it overflow */
			print_line("%s", frmtdbuff);
			memset(frmtdbuff, '\0', sizeof(frmtdbuff));
		}
	}
	if ( strlen(frmtdbuff) ) linetodo = 1;
	return 0;
}
