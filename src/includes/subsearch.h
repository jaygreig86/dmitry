#ifndef _SUBSEARCH_H
#define _SUBSEARCH_H

#define MAXIPLEN 17

int get_subdomains(char* host);
int get_hoststring(char* host);
int grab_sub(char* buff, int pointer, char* host);
int sublist(char* sub, char* host);

#endif
