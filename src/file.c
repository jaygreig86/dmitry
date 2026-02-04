#include "includes/file.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// fpos_t file_loc;
// char filename[64];

FILE *wfp = NULL;
char outputfile[64] = { 0 };

int file_prep()
{
    outputfile[strlen(outputfile)] = '\0';
    if (!(wfp = fopen(outputfile, "w"))) {
        printf("Error: Unable to write to %s\n", outputfile);
        exit(1);
    }
    printf("Writing output to '%s'\n\n", outputfile);
    fclose(wfp);
    return 0;
}

int file_open()
{
    if (!(wfp = fopen(outputfile, "a+"))) {
        printf("Error: Unable to write to %s\n", outputfile);
        exit(1);
    }
    return 0;
}

int file_close()
{
    if (fclose(wfp)) {
        printf("Error: Unable to close file stream writing to %s\n", outputfile);
        exit(1);
    }
    return 0;
}
