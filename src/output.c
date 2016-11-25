#include "includes/output.h"

void print_line(char *string, char *string2)
{
	int ctr;
	int ctr2;
	char sendbuff[255];
	char timebuff[5];
	char timebuff2[5];
	struct tm *timenow;
	time_t now;

	if ( strlen(outputfile) ){
		memset(sendbuff, '\0', sizeof(sendbuff));
		ctr = 0;
		ctr2 = 0;
                do {
                        if ( string[ctr] == '%' && string[ctr + 1] == 's' ){
				strcat(sendbuff, string2);
				ctr += 2;
                        }
                        sendbuff[strlen(sendbuff)] = string[ctr];
                        ctr ++;
                } while ( string[ctr] != '\0' );
		
		fputs(sendbuff, wfp);
	}

	printf(string, string2);

	return;
}

