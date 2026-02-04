#ifndef _IWHOIS_H
#define _IWHOIS_H

#define MAXHOSTS 4


extern char *ip_whois_hosts[];
extern char *ip_error_find[];
extern char *ip_read_begin[];
extern char *ip_read_end[];

int get_iwhois(char *host);
int ip_string_search(int server);
int ip_format_buff(char *buff, int server);

#endif
