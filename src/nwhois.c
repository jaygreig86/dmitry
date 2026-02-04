#include "includes/nwhois.h"

#include <stdio.h>
#include <string.h>

#include "includes/file.h"
#include "includes/tcp_sock.h"
#include "includes/output.h"


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

char _nwhois_td[10];
char _nwhois_query[128];
int _nwhois_linetodo; /* This is used to symbolise to nic_format_buff() that there is a line still to format */
// extern char outputfile[64];

int get_nwhois(char* host)
{
    int hostn;
    char fhost[128]; /* Host with www removed */
    char linebuff[256];
    char server[64];

    int ctr;
    _nwhois_linetodo = 0;
    if (strlen(outputfile))
        file_open();

    /* remove www. */
    memset(fhost, '\0', sizeof(fhost));
    if (host[0] == 'w' && host[1] == 'w' && host[2] == 'w' && host[3] == '.' && strlen(host) > 9) {
        ctr = 4;
        do {
            if (host[ctr] != '\n' && host[ctr] != '\0')
                fhost[ctr - 4] = host[ctr];
            ctr++;
        } while (host[ctr] != '\n' && host[ctr] != '\0');
    } else
        strcpy(fhost, host);

    /* Print introduction to function */
    memset(linebuff, '\0', sizeof(linebuff));
    snprintf(linebuff, sizeof(linebuff), "\nGathered Inic-whois information for %s\n", fhost);
    print_line("%s", linebuff);

    memset(linebuff, '\0', sizeof(linebuff));
    snprintf(linebuff, sizeof(linebuff), "---------------------------------\n");
    print_line("%s", linebuff);

    /* TopLevelDomain output */
    if (!(hostn = get_td(fhost))) {
        snprintf(server, sizeof(server), "%s.whois-servers.net", _nwhois_td);
    } else
        strcpy(server, nic_whois_hosts[hostn - 1]);

    if (!tcp_socket(server, 43)) {
        nic_string_search(fhost);
    } else
        print_line("ERROR: Connection to InicWhois Server %s failed\n", server);
    if (strlen(outputfile))
        file_close();
    tcp_sockdcon();
    return 0;
}

int nic_string_search(char* host)
{
    char buff[512];
    int listn;
    int found = 0; /* Has the domain been found */
    /* Send query string */
    sendData(_nwhois_query, strlen(_nwhois_query));
    do {
        memset(buff, '\0', sizeof(buff));
        readData(buff, 500);
        for (listn = 0; listn < 12; listn++) {
            if (strstr(buff, nic_error_find[listn])) {
                print_line("ERROR: Unable to locate Name Whois data on %s\n", host);
                return 0;
            }
        }
        for (listn = 0; listn < 7; listn++) {
            if (strstr(buff, nic_read_begin[listn]) || found == 1) {
                if (nic_format_buff(buff, listn))
                    return 0;
                found = 1;
                break;
            }
        }
    } while (buff[0] != '\0');

    return 0;
}

int get_td(char* host)
{
    /* Get the top level domain in reverse order .uk .com etc*/
    int ctr;
    memset(_nwhois_query, '\0', sizeof(_nwhois_query));
    memset(_nwhois_td, '\0', sizeof(_nwhois_td));
    ctr = strlen(host) - 1;
    do {
        ctr--;
    } while (host[ctr] != '.' && ctr > 0);

    ctr++;

    do {
        _nwhois_td[strlen(_nwhois_td)] = host[ctr];
        ctr++;
    } while (host[ctr] != '\0');

    if (!strcmp(_nwhois_td, "com") || !strcmp(_nwhois_td, "net")) {
        snprintf(_nwhois_query, sizeof(_nwhois_query), "=%s\r\n", host);
        return 1;
    }
    if (!strcmp(_nwhois_td, "jp")) {
        snprintf(_nwhois_query, sizeof(_nwhois_query), "%s/e\r\n", host);
        return 2;
    }
    if (!strcmp(_nwhois_td, "de")) {
        snprintf(_nwhois_query, sizeof(_nwhois_query), "-T dn %s\r\n", host);
        return 0;
    }

    snprintf(_nwhois_query, sizeof(_nwhois_query), "%s\r\n", host);
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

int nic_format_buff(char* buff, int listn)
{
    char frmtdbuff[128]; /* This is the buffer containing formatted lines */
    int ctr = 0; /* Character Counter */
    int firstpacket = 0;
    if (!_nwhois_linetodo)
        memset(frmtdbuff, '\0', sizeof(frmtdbuff));
    if (strstr(buff, nic_read_begin[listn]))
        firstpacket = 1;
    while (buff[ctr] != '\0') {
        if (buff[ctr] == '\n') {
            if (firstpacket == 0 || (firstpacket == 1 && strstr(frmtdbuff, nic_read_begin[listn]))) {
                print_line("%s\n", frmtdbuff);
                firstpacket = 0;
                if (buff[ctr] == '\n' && buff[ctr + 1] == '\n' && buff[ctr + 2] == '\n')
                    return 1;
            }
            memset(frmtdbuff, '\0', sizeof(frmtdbuff));
            _nwhois_linetodo = 0;
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
    if (strlen(frmtdbuff))
        _nwhois_linetodo = 1;
    return 0;
}
