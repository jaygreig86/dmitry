#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "file.h"
#include <time.h>
extern char user[10];
extern int irc;
extern void irc_sendData();
extern void print_line(char *string, char *string2);
extern char outputfile[64];

