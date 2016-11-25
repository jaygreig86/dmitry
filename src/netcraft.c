#include "includes/netcraft.h"

int format_c(char *host)
{
        ctr = 0;
        do {
        ch = recvbuff[ctr];
        if ( ch != '\n' ) temp[strlen(temp)] = ch;
        if ( ch == '\n' ) {
		if ( strstr(temp, "bgcolor=\"#bac0ff\"> \t<td>") && ! check ){
			/* This set gathers the Operating System */
			ctr2 = 30;
			tmp = 30;
			memset(write_l, '\0', sizeof(write_l));
                        do {
                        ch = temp[ctr2];
			if ( temp[ctr2] != '>' && temp[ctr2] != '<' && temp[ctr2 + 1] != '>' && temp[ctr2 - 1] != '<' && temp[ctr2 -1] != '\\' && temp[ctr2 + 2] != '>' && temp[ctr2] != '\t'){
                                write_l[ctr2 - tmp] = ch;
                        }
                        else tmp++;

                        ctr2++;

                        } while (ch != '\n' && ch != '\0' && ch != '<');

                        print_line("Operating System: %s\n", write_l);

			/* This set gathers the WebServer Version */
			memset(write_l, '\0', sizeof(write_l));
			ctr2 += 10;
                        tmp = ctr2;
                        do {
                        ch = temp[ctr2];
			if ( temp[ctr2] != '>' && temp[ctr2] != '<' && temp[ctr2 + 1] != '>' && temp[ctr2 - 1] != '<' && temp[ctr2 -1] != '\\' && temp[ctr2 + 2] != '>' && temp[ctr2] != '\t'){
                                write_l[ctr2 - tmp] = ch;
                        }
                        else tmp++;

                        ctr2++;

                        } while (ch != '\n' && ch != '\0' && ch != '<');

                        print_line("WebServer: %s\n", write_l);

                        tmp = 0;
			check = 1;
		}
		if ( temp[4] == '<' && temp[5] == 't' && temp[6] == 'd' && temp[7] == '>' ){
			tmp++;
			if ( tmp == 1 ){
				print_line("Uptime Information:\n\n");
			}
			memset(os, '\0', sizeof(os));
			ctr3 = 10;
			do {
			if ( temp[ctr3] != '<' ) os[ctr3 - 10] = temp[ctr3];
			ctr3++;
			} while ( temp[ctr3] != '<' && temp[ctr3] != '\0' );
			print_line("%s\n", os);
			os[strlen(os)] = '\n';
		}
		if ( temp[4] == '<' && temp[5] == 't' && temp[6] == 'd' && temp[21] == '>' ){
			memset(uptime, '\0', sizeof(uptime));
			ctr3 = 21;
			while ( temp[ctr3] != '\0' && temp[ctr3] != '<' && ctr3 <= strlen(temp)){
				ctr3++;
				if (temp[ctr3] == ' ') ctr3++;
				if ( temp[ctr3] != '\0' && temp[ctr3] != '<') uptime[strlen(uptime)] = temp[ctr3];
			}
			if ( temp[strlen(temp) - 2] == 45 ) strcat(uptime, " - \tRecord Max (days)\n");
			if ( temp[31] == 'd' && (strlen(temp) - 2 == 31)) strcat(uptime, " - \tLatest (days)\n");
			if ( temp[22] != ' ' && temp[strlen(temp) -6] == ' ' && temp[strlen(temp) - 5] == '<' ) strcat(uptime, "\t - \tNo. Samples\n");

			print_line("%s", uptime);
			ch = 1;
		}
		if ( temp[0] == 'N' && temp[1] == 'o' && temp[31] == 'u' && temp[32] == 'p' ) {
			print_line("No uptime reports available for host: %s\n", host);
		}
                memset(temp, '\0', sizeof(temp));
        }
        if ( ch == '\0' ) {
                if ( recvbuff[ctr - 1] == '\n' ) memset(temp, '\0', sizeof(temp));
                return 0;
        }
        ctr++;
        } while ( ch != '\0' );
        return 0;
}

int get_netcraft(char *host)
{
	if ( strlen(outputfile) ) file_open();
	snprintf(temp, sizeof(temp), "Gathered Netcraft information for %s\n---------------------------------\n", host);
	print_line("\n%s\n", temp);

	check = 0;

	print_line("Retrieving Netcraft.com information for %s\n", host);
	tcp_socket("uptime.netcraft.com", 80);

	memset(temp, '\0', sizeof(temp));
//http://toolbar.netcraft.com/site_report?url=
//http://uptime.netcraft.com/up/graph?site=
	snprintf(sendbuff, sizeof(sendbuff), "GET http://uptime.netcraft.com/up/graph?site=%s HTTP/1.0\r\n\r\n", host);
	sendData(sendbuff, strlen(sendbuff));

	while(1){
		memset(recvbuff, '\0', sizeof(recvbuff));

		readData(recvbuff, sizeof(recvbuff));
		format_c(host);
			
		if ( recvbuff[0] == '\0' ){
			print_line("Netcraft.com Information gathered\n");
			close(tcp_sock);
			tcp_sock = 0;
			if ( strlen(outputfile) ) file_close();
			return 0;
		}
	}
}
