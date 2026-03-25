#ifndef _FILE_H
#define _FILE_H

#include <stdio.h>

#define OUTPUT_LOCALITY "output.txt"

extern FILE *wfp;
extern char outputfile[64];

int file_prep();
int file_open();
int file_close();

#endif
