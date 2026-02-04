#ifndef _NETCRAFT_H
#define _NETCRAFT_H

#include <stddef.h>

int format_c(char *host, size_t recv_len);
int get_netcraft(char *host);

#endif

