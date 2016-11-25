char optchar;
int options[10];
int ctr;
extern void print_line();
extern int get_host(char *host, char *dest);
extern int get_emails();
extern int file_prep();
extern int file_open();
extern int file_close();
extern int get_iwhois();
extern int get_nwhois();
extern int get_subdomains();
extern int get_netcraft();
extern int portscan(char *entry, int ttl, int options);
char outputfile[64];

char *message[]={
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

