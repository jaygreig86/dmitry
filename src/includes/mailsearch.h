#ifndef _MAILSEARCH_H
#define _MAILSEARCH_H

int get_emails(char *host);
int get_email_hoststring(char *host);
int grab_emails(char* buff, int pointer, char* host);
int emaillist(char* email, char* host);

#endif
