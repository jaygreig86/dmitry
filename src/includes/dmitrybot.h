int irc_connect();
char host_ip[128];
char host_name[255];
extern int get_host();
extern int file_prep();
extern int get_nwhois();
extern int get_iwhois();
extern int get_subdomains();
extern int get_emails();
extern int get_netcraft();
extern int portscan(char *entry, int ttl, int options);
extern void print_line();
char outputfile[64];
extern int tcp_socket();
extern int irc_readData();
extern int irc_sendData();
extern int irc_sock;
void irc_command(char *);
void irc_join(char *);
void irc_help();
void irc_welcome();

char *ircmessage[]={
"  get_host:host\t Gather Host Name and IP address information of a host\n",
"  get_nwhois:host\t Perform a whois lookup on the IP address of a host\n",
"  get_iwhois:host\t Perform a whois lookup on the domain name of a host\n",
"  get_netcraft:host\t Retrieve Netcraft.com information on a host\n",
"  sub_search:host\t Perform a search for possible subdomains\n",
"  portscan:host\t Perform a TCP port scan on a host\n",
"* portscan:host+b\t Read in the banner received from the scanned port\n",
"* portscan:host+t 0-9 Set the TTL in seconds when scanning a TCP port ( Default 2 )\n",
"*Requires portscan to be passed\n",
"Example: portscan:uber.net+bt 3\n"
};

