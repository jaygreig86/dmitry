#include "includes/portscan.h"

#include <string.h>

#include "includes/file.h"
#include "includes/port_sock.h"
#include "includes/tcp_sock.h"

// char recvbuff[128];
// char filebuff[255];
// int tmp;
// int result;
// int closed;

// extern char outputfile[64];

/*
1	0	1
1	1	1
0	1	1
banner	filter	scan

*/

int portscan(char* entry, int ttl, int options)
{
    char recvbuff[128];
    char filebuff[255];
    int closed = 0;

    if (strlen(outputfile))
        file_open();
    tcp_sock = 0;
    memset(filebuff, '\0', sizeof(filebuff));

    snprintf(filebuff, sizeof(filebuff), "\nGathered TCP Port information for %s\n---------------------------------\n\n Port\t\tState\n", entry);
    printf("%s\n", filebuff);
    if (strlen(outputfile))
        fputs(filebuff, wfp);
    for (int tmp = 1; tmp < 150; tmp++) {
        int result = sock_con(entry, tmp, ttl);
        if (result == 0) {
            memset(filebuff, '\0', sizeof(filebuff));
            if (tmp < 1000)
                snprintf(filebuff, sizeof(filebuff), "%d/tcp\t\topen\n", tmp);
            if (tmp > 1000)
                snprintf(filebuff, sizeof(filebuff), "%d/tcp\topen\n", tmp);
            if (strlen(outputfile))
                fputs(filebuff, wfp);
            printf("%s", filebuff);
            if (options >= 100) {
                banner(recvbuff, sizeof(recvbuff));
                if (recvbuff[strlen(recvbuff) - 1] != '\n')
                    recvbuff[strlen(recvbuff) - 1] = '\n';
                if (strlen(outputfile))
                    fputs(recvbuff, wfp);
            }
        }
        if (result == 1) {
            closed++;
        }
        if (result == 2) {
            memset(filebuff, '\0', sizeof(filebuff));
            if (options == 11 || options == 111) {
                if (tmp < 1000)
                    snprintf(filebuff, sizeof(filebuff), "%d/tcp\t\tfiltered\n", tmp);
                if (tmp > 1000)
                    snprintf(filebuff, sizeof(filebuff), "%d/tcp\tfiltered\n", tmp);
                if (strlen(outputfile))
                    fputs(filebuff, wfp);
                printf("%s", filebuff);
            }
        }
    }
    memset(filebuff, '\0', sizeof(filebuff));
    snprintf(filebuff, sizeof(filebuff), "\nPortscan Finished: Scanned 150 ports, %d ports were in state closed\n", closed);
    printf("%s\n", filebuff);
    if (strlen(outputfile)) {
        fputs(filebuff, wfp);
        file_close();
    }
    return 0;
}
