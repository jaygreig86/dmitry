#include "includes/config.h"
#include "includes/global.h"
#if HAVE_GETOPT_H
#include <getopt.h>
#endif
#include "includes/dmitry.h"
#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char **argv)
{
	int ttl = 2;		/*Portscan TimeToLive*/
	int otherops = 0;	/*Are there any other options selected other than fileoutput (-o) */
        char host_ip[MAXIPLEN];
        char host_name[MAXNAMELEN];
	
	memset(host_name, '\0', MAXNAMELEN);
	memset(host_ip, '\0', MAXIPLEN);

	printf("Deepmagic Information Gathering Tool\n\"There be some deep magic going on\"\n\n");
	
	memset(outputfile, '\0', sizeof(outputfile));

        if ( argc == 1 ){
                printf("Usage: %s [-winsepfb] [-t 0-9] [-o %%host.txt] host\n", argv[0]);
                for(ctr=0;ctr < 11;ctr++){
                        printf("%s", message[ctr]);
                }

                exit(1);
        }

	/* The following set is for the command line options used (-winspfto) */
	while ( ( optchar = getopt(argc, argv, "viwenspbfo:t:") ) != -1 ){
		switch(optchar){
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
				if (!isdigit(optarg[0])){
					printf("Error: TTL invalid, acceptable range 0-9\n");
					printf("Exampe: %s -p -t 9 host\n", argv[0]);
					exit(0);
				}
				else ttl = optarg[0] - 48;
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
				if (! strcmp(optarg, argv[argc-1])){
					snprintf(outputfile, sizeof(outputfile), "%s.txt", argv[argc-1]);
				}
				else {
					strncpy(outputfile, optarg, sizeof(outputfile) - 1);
					outputfile[sizeof(outputfile) - 1] = '\0';
				}
				break;
			case 'v':
				printf("Version: DMitry/1.3a (Unix)\n");
				exit(1);
			default:
		                printf("Usage: %s [-winsepfb] [-t 0-9] [-o %%host.txt] host\n", argv[0]);
        		        for(ctr=0;ctr < 11;ctr++){
        		                printf("%s", message[ctr]);
                		}

                		exit(1);
		}
	}

	/* If no options are select then assume 
	default that are all to be carried out */

	if (! otherops ){
		options[0] = 1;
		options[1] = 1;
		options[2] = 1;
		options[3] = 1;	
		options[4] = 1;
		options[5] = 1;
	}

	/* Potscan options */

	if ( options[3] == 100 || options[3] == 10 || options[3] == 110 ){
		printf("Error: No '-p' flag passed with TTL, assuming -p\n");
		options[3] += 1;
	}

        /* Is the data to be output to a file? */

        if ( strlen(outputfile) ) file_prep();
	if ( strlen(outputfile) ) file_open();
	/* Check if host exists/is available and resolve */

	switch(inet_addr(argv[argc - 1])){
		case INADDR_NONE:
			if (! get_host(argv[argc - 1], host_ip) ) {
				print_line("ERROR: Unable to locate Host IP addr. for %s\n", argv[argc - 1]);
				print_line("Continuing with limited modules\n");
			}
			strncpy(host_name, argv[argc - 1], MAXNAMELEN - 1);
			host_name[MAXNAMELEN - 1] = '\0';
			break;
		default:
			if (! get_host(argv[argc - 1], host_name) ) {
				print_line("ERROR: Unable to locate Host Name for %s\n", argv[argc - 1]);
				print_line("Continuing with limited modules\n");
			}
			strncpy(host_ip, argv[argc - 1], MAXIPLEN - 1);
			host_ip[MAXIPLEN - 1] = '\0';
			break;
	}
	print_line("HostIP:%s\n", host_ip);
	print_line("HostName:%s\n", host_name);
	if ( strlen(outputfile) ) file_close();
	/* Scanning Functions */

	if ( options[0] && strlen(host_ip)) get_iwhois(host_ip);
	if ( options[1] && strlen(host_name)) get_nwhois(host_name);
	if ( options[2] && strlen(host_name)) get_netcraft(host_name);
	if ( options[4] && strlen(host_name)) get_subdomains(host_name);
	if ( options[5] && strlen(host_name)) get_emails(host_name);
	if ( options[3] >= 1 && strlen(host_ip)) portscan(host_ip, ttl, options[3]);
	print_line("\nAll scans completed, exiting\n");

	return 0;
}

