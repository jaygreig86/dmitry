#include "includes/config.h"

#if HAVE_GETOPT_H
#include <getopt.h>
#endif

#include <arpa/inet.h>
#include <ctype.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "includes/dmitry.h"
#include "includes/file.h"
#include "includes/global.h"
#include "includes/output.h"
#include "includes/portscan.h"

#include "includes/iwhois.h" // get_iwhois
#include "includes/mailsearch.h" // get_emails
#include "includes/netcraft.h" // get_netcraft
#include "includes/nwhois.h" // get_nwhois
#include "includes/resolve.h" // get_host
#include "includes/subsearch.h" // get_subdomains

// int optchar;
// int options[10];
// int ctr;
// char outputfile[64];

char* message[] = {
    "  -o\t Save output to %host.txt or to file specified by -o file\n",
    "  -i\t Perform a whois lookup on the IP address of a host\n",
    "  -w\t Perform a whois lookup on the domain name of a host\n",
    "  -n\t Retrieve Netcraft.com information on a host\n",
    "  -s\t Perform a search for possible subdomains\n",
    "  -e\t Perform a search for possible email addresses\n",
    "  -p\t Perform a TCP port scan on a host\n",
    "* -f\t Perform a TCP port scan on a host showing output reporting filtered ports\n",
    "* -b\t Read in the banner received from the scanned port\n",
    "* -t 0-9 Set the TTL in seconds when scanning a TCP port ( Default 2 )\n",
    "*Requires the -p flagged to be passed\n",
    "Example: dmitry -iwnpt 7 -o host.net\n"
};

int main(int argc, char** argv)
{
    int ttl = 2; /*Portscan TimeToLive*/
    int otherops = 0; /*Are there any other options selected other than fileoutput (-o) */
    char host_ip[MAXIPLEN];
    char host_name[MAXNAMELEN];

    memset(host_name, '\0', MAXNAMELEN);
    memset(host_ip, '\0', MAXIPLEN);

    printf("Deepmagic Information Gathering Tool\n\"There be some deep magic going on\"\n\n");

    memset(outputfile, '\0', sizeof(outputfile));

    if (argc == 1) {
        printf("Usage: %s [-winsepfb] [-t 0-9] [-o %%host.txt] host\n", argv[0]);
        for (unsigned int ctr = 0; ctr < 11; ctr++) {
            printf("%s", message[ctr]);
        }

        exit(1);
    }

    int optchar;
    int options[10];

    /* The following set is for the command line options used (-winspfto) */
    while ((optchar = getopt(argc, argv, "viwenspbfo:t:")) != -1) {
        switch (optchar) {
        case 'i':
            options[0] = 1;
            otherops = 1;
            break;

        case 'w':
            options[1] = 1;
            otherops = 1;
            break;

        case 'n':
            options[2] = 1;
            otherops = 1;
            break;

        case 'p':
            options[3] += 1;
            otherops = 1;
            break;

        case 't':
            if (!isdigit(optarg[0])) {
                printf("Error: TTL invalid, acceptable range 0-9\n");
                printf("Example: %s -p -t 9 host\n", argv[0]);
                exit(0);
            } else
                ttl = optarg[0] - 48;
            otherops = 1;
            break;

        case 'f':
            options[3] += 10;
            otherops = 1;
            break;

        case 'b':
            options[3] += 100;
            otherops = 1;
            break;

        case 's':
            options[4] = 1;
            otherops = 1;
            break;

        case 'e':
            options[5] = 1;
            otherops = 1;
            break;

        case 'o':
            if (!strcmp(optarg, argv[argc - 1])) {
                snprintf(outputfile, sizeof(outputfile), "%s.txt", argv[argc - 1]);
            } else {
                strncpy(outputfile, optarg, sizeof(outputfile) - 1);
                outputfile[sizeof(outputfile) - 1] = '\0';
            }
            break;
        case 'v':
            printf("Version: DMitry/1.3a (Unix)\n");
            exit(1);
        default:
            printf("Usage: %s [-winsepfb] [-t 0-9] [-o %%host.txt] host\n", argv[0]);
            for (int ctr = 0; ctr < 11; ctr++) {
                printf("%s", message[ctr]);
            }

            exit(1);
        }
    }

    /* If no options are select then assume
    default that are all to be carried out */

    if (!otherops) {
        options[0] = 1;
        options[1] = 1;
        options[2] = 1;
        options[3] = 1;
        options[4] = 1;
        options[5] = 1;
    }

    /* Portscan options */

    if (options[3] == 100 || options[3] == 10 || options[3] == 110) {
        printf("Error: No '-p' flag passed with TTL, assuming -p\n");
        options[3] += 1;
    }

    /* Is the data to be output to a file? */

    if (strlen(outputfile))
        file_prep();
    if (strlen(outputfile))
        file_open();
    /* Check if host exists/is available and resolve */

    switch (inet_addr(argv[argc - 1])) {
    case INADDR_NONE:
        if (!get_host(argv[argc - 1], host_ip)) {
            print_line("ERROR: Unable to locate Host IP addr. for %s\n", argv[argc - 1]);
            print_line("Continuing with limited modules\n");
        }
        strncpy(host_name, argv[argc - 1], MAXNAMELEN - 1);
        host_name[MAXNAMELEN - 1] = '\0';
        break;
    default:
        if (!get_host(argv[argc - 1], host_name)) {
            print_line("ERROR: Unable to locate Host Name for %s\n", argv[argc - 1]);
            print_line("Continuing with limited modules\n");
        }
        strncpy(host_ip, argv[argc - 1], MAXIPLEN - 1);
        host_ip[MAXIPLEN - 1] = '\0';
        break;
    }
    print_line("Host IP:%s\n", host_ip);
    print_line("Host Name:%s\n", host_name);
    if (strlen(outputfile))
        file_close();
    /* Scanning Functions */

    if (options[0] && strlen(host_ip))
        get_iwhois(host_ip);
    if (options[1] && strlen(host_name))
        get_nwhois(host_name);
    if (options[2] && strlen(host_name))
        get_netcraft(host_name);
    if (options[4] && strlen(host_name))
        get_subdomains(host_name);
    if (options[5] && strlen(host_name))
        get_emails(host_name);
    if (options[3] >= 1 && strlen(host_ip))
        portscan(host_ip, ttl, options[3]);
    print_line("\nAll scans completed, exiting\n");

    return 0;
}
