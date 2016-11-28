=========================================================================
Intro
=========================================================================

DMitry (Deepmagic Information Gathering Tool)

Conceptual design result of deepmagic brainstorimg session.
Coded by kernel.

Downloadable @ http://www.mor-pah.net

As featured in "Gray Hat Hacking : The Ethical Hacker's Handbook".

=========================================================================
Greetz
=========================================================================

Greetz to... phased, di0aD, wh1sky, high_towe, big dave,
	mister pand0r, phool312, remedy, number5 and anyone
		i've missed!

"There be some deep magic going on"

=========================================================================
Contents
=========================================================================

1. Version Information
2. What is DMitry?
3. Fixes
4. TO DO
5. Feature Status
6. Usage: Command Line Functionality
7. Contact

see INSTALL text file for installation help.

=========================================================================
1. VERSION
=========================================================================

DMitry
Version "1.3a"

=========================================================================
2. What is DMitry?
=========================================================================

DMitry   (Deepmagic   Information  Gathering  Tool)  is  a
UNIX/(GNU)Linux Command Line program  coded  purely  in  C
with the ability to gather as much information as possible
about a host.

DMitry has a base functionality with the  ability  to  add
new  functions.   Basic functionality of DMitry allows for
information to be gathered about a target host from a sim-
ple  whois  lookup on the target to UpTime reports and TCP
portscans.

The application is considered a tool to assist in informa-
tion  gathering  when  information  is required quickly by
removing the need  to  enter  multiple  commands  and  the
timely  process  of  searching  through data from multiple
sources.

To get straight into DMitry without reading this document,
you  can initially type "dmitry target", this will perform
the majority of functions on the target.

=========================================================================
3. Fixes
=========================================================================

Version 1.3a:
A Qucik release to address two malloc issues with mailsearch
and subsearch.  Found that increasing the initalizing size to
two rows instead of one resolved this issue.  Seems to only
appear in newer versions of *BSD. I.e FreeBSD 6.

Version 1.3:
Just a quick release to fix the netcraft function output
Also fixed the command line typo to include -e
Removed the dmitrybot, it will no longer be available

Version 1.2a:

Remodeled the InetWhois function entirely:
Now much more reliable and reports errors correctly where possible

Remodeled the InicWhois function entirely:
This now allows for most TopLevelDomains from .fr to .uk, .us etc.
Output is now sent directly to stdout for the two whois functions
There is no longer output concerning DMitry jumping from one 
server to another.  Instead DMitry will use just one server unless there
is a referral whois server.  This function now no longer uses fpurge() or
__fpurge().

Remodeled the Sub Domain Search function, there are no longer any *alloc()
problems.

Remodeled the host resolve function, and fixed a bug which caused a dump
when an IP address was entered that wouldn't resolve to a hostname.

Version 1.2:

The portscan feature of DMitry isn't so great, gave it a bit of a revamp.
Fixed the command line problems with optarg[] the ttl option now works.

Added whois.opensrs.net to the whois list.

Ability to continue if the resolve fails at the start.

Portscan showing filtered ports is no longer a default.

Netcraft OS information is now less dependent on the netcraft output.

Version 1.1:

DMitry is now fully portable to most common GNU/LINUX distributions and
to all BSD distributions.

Re-made the Subdomain Search module fixing quite a few search string bugs
along with fixing a malloc() problem with some linux distros.

Added a quick feature to allow for a search of www.host if host alone fails
(will add an option to skip resolve in a later release)

Modified google.com query string from %22host%22 ("host") to %2Bhost (+host)

Modified google.com format string to locate bold also

Fixed .uk whois bug => reg.nic.uk => whois.nic.uk

=========================================================================
4. TO DO:
=========================================================================

FIX google subdomain searches (most likely requires CURL to connect over SSL)

FIX Netcraft page reading

=========================================================================
5. Feature Status
=========================================================================

Fully Working Functions:

  -o     Save output to %host.txt or to file specified by -o file
  -i     Perform a whois lookup on the IP address of a host
  -w     Perform a whois lookup on the domain name of a host
  -n     Retrieve Netcraft.com information on a host
  -s     Perform a search for possible subdomains
  -e     Perform a search for possible email addresses
  -p     Perform a TCP port scan on a host
* -f     Perform a TCP port scan on a host showing output reporting filtered ports
* -b     Read in the banner received from the scanned port
* -t 0-9 Set the TTL in seconds when scanning a TCP port ( Default 2 )

Example: dmitry -iwnp -t 7 host.net

Functions:

get_host()
get_netcraft()
get_nwhois()
get_iwhois()
get_subdomains()
get_emails()
portscan()

=========================================================================
6. Usage: Command Line Functionality
=========================================================================

Check the man page for dmitry for an indepth manual on using DMitry
and its functionality. (This requires DMitry to be installed, make install).

	% man dmitry

Once fully installed or localy installed the program can simply be 
executed by the following:

	% ./dmitry

The command above alone will list all the possible options that can be 
passed to it along with a brief explanation.

To execute the program with the default functionality you can simply
pass just the hostname to the program as below:

	% ./dmitry example-host.com

This will run all the functions with their default settings and will print
to the standard output aswell as saving the results to "./example-host.com.txt"

=========================================================================
7. Contact
=========================================================================

Please contact me with any thoughts or suggestions, Bugs and queries etc.

James@mor-pah.net

James Greig (kernel)

url:http://www.mor-pah.net

kernel-- on undernet.org
