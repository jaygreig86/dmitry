#include "includes/output.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "includes/file.h"

// extern char user[10];
// extern int irc;
// extern char outputfile[64];

void print_line(const char* format, ...)
{
    int ctr;
    char sendbuff[255];

    va_list args;
    va_list args_copy;

    va_start(args, format);
    va_copy(args_copy, args);

    if (strlen(outputfile)) {
        memset(sendbuff, '\0', sizeof(sendbuff));
        ctr = 0;

        do {
            if (format[ctr] == '%') {
                ++ctr;
                switch (format[ctr]) {
                case 's':
                    strcat(sendbuff, _format_string(args));
                    break;
                default:
                    // Unknown format placeholder
                    sendbuff[strlen(sendbuff)] = '%';
                    sendbuff[strlen(sendbuff)] = format[ctr];
                }
            }

            sendbuff[strlen(sendbuff)] = format[ctr];
            ++ctr;
        } while (format[ctr] != '\0');

        fputs(sendbuff, wfp);
    }

    vprintf(format, args_copy);

    va_end(args);
    va_end(args_copy);

    return;
}

char* _format_string(va_list args)
{
    char* str = va_arg(args, char*);
    if (str == NULL) {
        str = "(null)"; // Handle NULL strings
    }
    return str;
}
