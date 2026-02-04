#ifndef _OUTPUT_H
#define _OUTPUT_H

#include <stdarg.h>
#include "file.h"

void print_line(const char *format, ...);
char* _format_string(va_list args);

#endif
