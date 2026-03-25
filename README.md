# DMitry (Deepmagic Information Gathering Tool)

DMitry is a historical UNIX/(GNU)Linux command-line information gathering utility.  
Conceptually created during a deepmagic brainstorming session and coded by kernel.

Downloadable from: http://www.mor-pah.net  
Featured in "Gray Hat Hacking: The Ethical Hacker's Handbook".

## Table of Contents

- [Introduction](#introduction)
- [Greetz](#greetz)
- [Version](#version)
- [What is DMitry?](#what-is-dmitry)
- [Fixes](#fixes)
- [TO DO](#to-do)
- [Feature Status](#feature-status)
- [Usage](#usage-command-line-functionality)
- [Collaborators](#collaborators)
- [Contact](#contact)

## Introduction

DMitry (Deepmagic Information Gathering Tool)

Conceptual design result of deepmagic brainstorming session.  
Coded by kernel.

Downloadable @ http://www.mor-pah.net

As featured in "Gray Hat Hacking : The Ethical Hacker's Handbook".

## Greetz

Greetz to... phased, di0aD, wh1sky, high_towe, big dave, mister pand0r, phool312, remedy, number5 and anyone I've missed!

"There be some deep magic going on"

## Version

DMitry
Version "1.3a"

## What is DMitry?

DMitry (Deepmagic Information Gathering Tool) is a UNIX/(GNU)Linux command-line program coded purely in C with the ability to gather as much information as possible about a host.

DMitry has a base functionality with the ability to add new functions. Basic functionality of DMitry allows for information to be gathered about a target host from a simple whois lookup on the target to uptime reports and TCP portscans.

The application is considered a tool to assist in information gathering when information is required quickly by removing the need to enter multiple commands and the timely process of searching through data from multiple sources.

To get straight into DMitry without reading this document, you can initially type `dmitry target`; this will perform the majority of functions on the target.

## Fixes

### Version 1.3a

A quick release to address two malloc issues with mailsearch and subsearch. Found that increasing the initializing size to two rows instead of one resolved this issue. Seems to only appear in newer versions of *BSD, e.g. FreeBSD 6.

### Version 1.3

- Fixed netcraft function output
- Fixed command line typo to include `-e`
- Removed dmitrybot

### Version 1.2a

Remodeled the InetWhois function entirely: now much more reliable and reports errors correctly where possible.

Remodeled the InicWhois function entirely:
- Better TLD support (.fr, .uk, .us, etc.)
- Output is now sent directly to stdout for the two whois functions
- No longer prints DMitry server-jump messages; uses one server unless redirected
- No longer uses `fpurge()` or `__fpurge()`

Remodeled the Sub Domain Search function, eliminated *alloc() problems.

Remodeled the host resolve function, and fixed a bug causing a crash when entering an IP that would not resolve to a hostname.

### Version 1.2

- Improved portscan feature and ttl option handling
- Added `whois.opensrs.net` to the whois list
- Continue if resolve fails at startup
- Portscan filtered ports no longer default
- Netcraft OS parsing is more robust

### Version 1.1

- Full portability across common GNU/Linux and BSD distros
- Rebuilt Subdomain Search module; fixed search string bugs and malloc issue
- Added auto `www.` fallback lookup
- Improved Google query handling and parsing
- Fixed `.uk` whois redirection (reg.nic.uk -> whois.nic.uk)

## TO DO

- FIX Google subdomain searches (likely requires SSL/cURL support)
- FIX Netcraft page parsing

## Feature Status

### Fully working functions

- `-o` Save output to `%host.txt` or file specified by `-o file`
- `-i` Perform a whois lookup on the IP address of a host
- `-w` Perform a whois lookup on the domain name of a host
- `-n` Retrieve Netcraft.com information on a host
- `-s` Perform a search for possible subdomains
- `-e` Perform a search for possible email addresses
- `-p` Perform a TCP port scan on a host
- `-f` Perform a TCP port scan showing filtered ports
- `-b` Read banner from scanned port
- `-t 0-9` Set the TTL in seconds when scanning a TCP port (default 2)

Example: `dmitry -iwnp -t 7 host.net`

### Functions in the code

- `get_host()`
- `get_netcraft()`
- `get_nwhois()`
- `get_iwhois()`
- `get_subdomains()`
- `get_emails()`
- `portscan()`

## Usage: Command Line Functionality

Check the man page for complete usage details (requires `make install`):

```sh
man dmitry
```

Once installed or built locally, run:

```sh
./dmitry
```

Running with a hostname executes default function set and saves output to `./example-host.com.txt`.

```sh
./dmitry example-host.com
```

## Collaborators

- Original author: `kernel`
- Early contributors: phased, di0aD, wh1sky, high_towe, big dave, mister pand0r, phool312, remedy, number5
- New contributors: `0zitro`

## Contact

Please use GitHub issues to submit questions, bug reports, or suggestions.

(removed personal email address from project documentation)
