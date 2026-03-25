#ifndef _NWOIS_H
#define _NWOIS_H


int get_nwhois(char* host);
int nic_string_search(char* host);
int get_td(char* host);
int nic_format_buff(char* buff, int listn);


extern char *nic_whois_hosts[];
extern char *nic_error_find[];
extern char *nic_read_begin[];
extern char *nic_read_end[];

#endif
