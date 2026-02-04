#include "includes/netcraft.h"

#include <string.h>
#include <unistd.h>

#include "includes/file.h"
#include "includes/output.h"
#include "includes/tcp_sock.h"

// char ch;
// char write_l[128];
// char uptime[128];
// char os[32];
char _netcraft_recvbuff[128];
char _netcraft_sendbuff[255];
char _netcraft_temp[1024];
int _netcraft_check;
// unsigned int ctr;
// unsigned int ctr2;
// unsigned int ctr3;
// unsigned int tmp = 0;
// extern char outputfile[64];

int format_c(char* host, size_t recv_len)
{
    unsigned int ctr = 0;
    unsigned int tmp = 0;
    char ch;


    char write_l[128];

    unsigned int ctr3;
    char os[32];
    char uptime[128];

    for (ctr = 0; ctr < recv_len; ctr++) {
        ch = _netcraft_recvbuff[ctr];
        if (ch != '\n') {
            size_t temp_len = strlen(_netcraft_temp);
            if (temp_len + 1 < sizeof(_netcraft_temp)) {
                _netcraft_temp[temp_len] = ch;
                _netcraft_temp[temp_len + 1] = '\0';
            }
        }
        if (ch == '\n') {
            if (strstr(_netcraft_temp, "bgcolor=\"#bac0ff\"> \t<td>") && !_netcraft_check) {
                /* This set gathers the Operating System */
                unsigned int ctr2 = 30;
                tmp = 30;

                memset(write_l, '\0', sizeof(write_l));
                do {
                    ch = _netcraft_temp[ctr2];
                    if (_netcraft_temp[ctr2] != '>'
                        && _netcraft_temp[ctr2] != '<'
                        && _netcraft_temp[ctr2 + 1] != '>'
                        && _netcraft_temp[ctr2 - 1] != '<'
                        && _netcraft_temp[ctr2 - 1] != '\\'
                        && _netcraft_temp[ctr2 + 2] != '>'
                        && _netcraft_temp[ctr2] != '\t')
                    {
                        if ((ctr2 - tmp) < sizeof(write_l) - 1) {
                            write_l[ctr2 - tmp] = ch;
                        }
                    } else {
                        tmp++;
                    }

                    ctr2++;

                } while (ch != '\n' && ch != '\0' && ch != '<');

                print_line("Operating System: %s\n", write_l);

                /* This set gathers the WebServer Version */
                memset(write_l, '\0', sizeof(write_l));
                ctr2 += 10;
                tmp = ctr2;
                do {
                    ch = _netcraft_temp[ctr2];
                    if (
                        _netcraft_temp[ctr2] != '>'
                        && _netcraft_temp[ctr2] != '<'
                        && _netcraft_temp[ctr2 + 1] != '>'
                        && _netcraft_temp[ctr2 - 1] != '<'
                        && _netcraft_temp[ctr2 - 1] != '\\'
                        && _netcraft_temp[ctr2 + 2] != '>'
                        && _netcraft_temp[ctr2] != '\t') {
                        if ((ctr2 - tmp) < sizeof(write_l) - 1) {
                            write_l[ctr2 - tmp] = ch;
                        }
                    } else {
                        tmp++;
                    }

                    ctr2++;
                } while (ch != '\n' && ch != '\0' && ch != '<');

                print_line("WebServer: %s\n", write_l);
                tmp = 0;
                _netcraft_check = 1;
            }

            size_t temp_len = strlen(_netcraft_temp);
            if (temp_len > 7 && _netcraft_temp[4] == '<' && _netcraft_temp[5] == 't' && _netcraft_temp[6] == 'd' && _netcraft_temp[7] == '>') {
                tmp++;
                if (tmp == 1) {
                    print_line("Uptime Information:\n\n");
                }

                memset(os, '\0', sizeof(os));
                ctr3 = 10;

                do {
                    if (_netcraft_temp[ctr3] != '<') {
                        if ((ctr3 - 10) < sizeof(os) - 1) {
                            os[ctr3 - 10] = _netcraft_temp[ctr3];
                        }
                    }
                    ctr3++;
                } while (_netcraft_temp[ctr3] != '<' && _netcraft_temp[ctr3] != '\0');

                print_line("%s\n", os);
                os[strlen(os)] = '\n';
            }
            if (temp_len > 21 && _netcraft_temp[4] == '<' && _netcraft_temp[5] == 't' && _netcraft_temp[6] == 'd' && _netcraft_temp[21] == '>') {
                memset(uptime, '\0', sizeof(uptime));
                ctr3 = 21;

                while (_netcraft_temp[ctr3] != '\0' && _netcraft_temp[ctr3] != '<' && ctr3 <= temp_len) {
                    ctr3++;
                    if (_netcraft_temp[ctr3] == ' ')
                        ctr3++;
                    if (_netcraft_temp[ctr3] != '\0' && _netcraft_temp[ctr3] != '<') {
                        size_t uptime_len = strlen(uptime);
                        if (uptime_len + 1 < sizeof(uptime)) {
                            uptime[uptime_len] = _netcraft_temp[ctr3];
                            uptime[uptime_len + 1] = '\0';
                        }
                    }
                }

                if (temp_len >= 2 && _netcraft_temp[temp_len - 2] == 45)
                    strcat(uptime, " - \tRecord Max (days)\n");
                if (temp_len > 31 && _netcraft_temp[31] == 'd' && (temp_len - 2 == 31))
                    strcat(uptime, " - \tLatest (days)\n");
                if (temp_len > 22 && temp_len >= 6 && _netcraft_temp[22] != ' ' && _netcraft_temp[temp_len - 6] == ' ' && _netcraft_temp[temp_len - 5] == '<')
                    strcat(uptime, "\t - \tNo. Samples\n");

                print_line("%s", uptime);
                ch = 1;
            }
            if (temp_len > 32 && _netcraft_temp[0] == 'N' && _netcraft_temp[1] == 'o' && _netcraft_temp[31] == 'u' && _netcraft_temp[32] == 'p') {
                print_line("No uptime reports available for host: %s\n", host);
            }

            memset(_netcraft_temp, '\0', sizeof(_netcraft_temp));
        }
    }
    return 0;
}

int get_netcraft(char* host)
{
    if (strlen(outputfile))
        file_open();
    snprintf(_netcraft_temp, sizeof(_netcraft_temp), "Gathered Netcraft information for %s\n---------------------------------\n", host);
    print_line("\n%s\n", _netcraft_temp);

    _netcraft_check = 0;

    print_line("Retrieving Netcraft.com information for %s\n", host);
    tcp_socket("uptime.netcraft.com", 80);

    memset(_netcraft_temp, '\0', sizeof(_netcraft_temp));
    // http://toolbar.netcraft.com/site_report?url=
    // http://uptime.netcraft.com/up/graph?site=
    snprintf(_netcraft_sendbuff, sizeof(_netcraft_sendbuff), "GET http://uptime.netcraft.com/up/graph?site=%s HTTP/1.0\r\n\r\n", host);
    sendData(_netcraft_sendbuff, strlen(_netcraft_sendbuff));

    while (1) {
        ssize_t bytes_read;

        memset(_netcraft_recvbuff, '\0', sizeof(_netcraft_recvbuff));

        bytes_read = read(tcp_sock, _netcraft_recvbuff, sizeof(_netcraft_recvbuff) - 1);
        if (bytes_read <= 0) {
            print_line("Netcraft.com Information gathered\n");

            close(tcp_sock);
            tcp_sock = 0;

            if (strlen(outputfile))
                file_close();
            return 0;
        }
        _netcraft_recvbuff[bytes_read] = '\0';
        format_c(host, (size_t)bytes_read);
    }
}
