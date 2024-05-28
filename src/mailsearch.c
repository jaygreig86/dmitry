#include "includes/mailsearch.h"

int get_emails(char *host)
{
	char hostwww[64];
	char sendbuff[256];
	int ctr = 0;
	int i = 0;
	int engine = 0;
	int totalpages = 0;
	emailcount = 0;

	/* Remove the www. */
	memset(hostwww, '\0', sizeof(hostwww));
        if ( host[0] == 'w' && host[1] == 'w' && host[2] == 'w' && host[3] == '.' && strlen(host) > 9 ) {
                ctr = 4;
                do {
                if ( host[ctr] != '\0' && host[ctr] != '\n' ) hostwww[ctr-4] = host[ctr];
                ctr++;
                } while ( host[ctr] != '\n' && host[ctr] != '\0' );
                hostwww[strlen(hostwww)] = '\0';
        }
        else {
            strncpy(hostwww, host, sizeof(hostwww) - 1);
            hostwww[sizeof(hostwww) - 1] = '\0';
        }

	if (strlen(outputfile)) file_open();

	print_line("\nGathered E-Mail information for %s\n", hostwww);
	print_line("---------------------------------\n");

	
	/* This constructs the string to signal a new page (if it's found that is) */
	pagenumber = 0;
	engine = 1;  
	while(1){
	        memset(pagestring, '\0', sizeof(pagestring));
		memset(sendbuff, '\0', sizeof(sendbuff));
		switch(engine){
			case 1:
				if (! pagenumber ) print_line("Searching Google.com:80...\n");
				tcp_socket("google.com", 80);
				snprintf(sendbuff, sizeof(sendbuff), "GET http://www.google.com/search?hl=en&lr=&ie=UTF-8&oe=UTF-8&q=allintext:+%%3Ca+href%%3Dmailto+%s&start=%d&sa=N&filter=1&num=100 HTTP/1.0\r\n\r\n", (char *)hostwww, pagenumber*100);
				snprintf(pagestring, sizeof(pagestring), "rt=%d&sa=N", (pagenumber+1)*100);
				break;
			case 2:
				if (! pagenumber ) print_line("Searching Altavista.com:80...\n");
				tcp_socket("uk.altavista.com", 80);
				snprintf(sendbuff, sizeof(sendbuff), "GET http://uk.altavista.com/web/results?q=%%3Ca+href%%3Dmailto+%s&kgs=0&kls=0&avkw=aapt&stq=%d&nbq=100 HTTP/1.0\r\n\r\n", hostwww, pagenumber*100);
				snprintf(pagestring, sizeof(pagestring), "&stq=%d", (pagenumber+1)*100);
				break;
/*			case 3:
				if (! pagenumber ) print_line("Searching Dogpile.com:80...\n");
				tcp_socket("dogpile.com", 80);
				snprintf(sendbuff, sizeof(sendbuff), "GET http://www.dogpile.com/info.dogpl/search/web/%%3Ca+href%%3Dmailto+%s/%d/10/%d/-/0/0/1/0/1/1/-/-/-/ HTTP/1.0\r\n\r\n", hostwww, pagenumber, pagenumber*100);
				snprintf(pagestring, sizeof(pagestring), ">Next >");
				break; */
			default:
				break;
		}
		sendData(sendbuff, strlen(sendbuff));
		if ( get_email_hoststring((char *) hostwww) ) pagenumber++;
		else {
			if ( engine == 2) break;
			else{
				engine++;
				totalpages += pagenumber;
				pagenumber = 0;
			}
		}
		tcp_sockdcon();
	}
	if ( tcp_sock ) tcp_sockdcon();
	/* Clean up */
	if (emailbuff) for(i=0;i < emailcount;i++) free(emailbuff[i]);

	if (emailcount == -1) emailcount = 0;
	
	memset(sendbuff, '\0', sizeof(sendbuff));
	snprintf(sendbuff, sizeof(sendbuff), "Found %d E-Mail(s) for host %s, Searched %d pages containing %d results\n", emailcount, hostwww, totalpages, totalpages*100);
	print_line("%s", sendbuff);
	if (strlen(outputfile)) file_close();
	return 0;
}

int get_email_hoststring(char *host)
{
	char readbuff[2048];
	int crpos = 0;	/* Current readbuff position */
	int ckpos = 0;  /* Current check position */
	int newpage = 0; /* Is there a 'next page' */
	do {
		memset(readbuff, '\0', sizeof(readbuff));
		readData(readbuff, 2000);
		if ( strstr(readbuff, pagestring) ) newpage = 1;
		if ( strstr(readbuff, host) ){
			ckpos = 0;
			for(crpos=0;readbuff[crpos + 1] != '\0' && crpos < (int)strlen(readbuff);crpos++){
				if ( readbuff[crpos] == '<' && readbuff[crpos + 1] == '/' && readbuff[crpos + 2] == 'b' && readbuff[crpos + 3] == '>' && (crpos + 5) < (int)strlen(readbuff) ) crpos += 4;
				if ( readbuff[crpos] == '<' && readbuff[crpos + 1] == 'b' && readbuff[crpos + 2] == '>' && (crpos + 4) < (int)strlen(readbuff)) crpos += 3;
				if ( readbuff[crpos] == host[ckpos] ) ckpos++;
				else ckpos = 0;

				/* The following IF is for strings that contain <b> and </b> -10 compensates for this */

				if ( ckpos == (int) strlen(host) && ( readbuff[(crpos-ckpos) - 10] == '@' || readbuff[(crpos-ckpos) - 10] == '.' )){
					if ( grab_emails(readbuff, (crpos-(ckpos+10)), host)) return 0;
					ckpos = 0;
				}
				if ( ckpos == (int) strlen(host) && ( readbuff[crpos-ckpos] == '@' || readbuff[crpos-ckpos] == '.' )) {
					if ( grab_emails(readbuff, (crpos-ckpos), host)) return 0;
					ckpos = 0;
				}
			}
		}
/*	if ( strstr(readbuff, "</body>") ) printf("\\%s\\\n%d\n", readbuff, pagenumber); */
	} while(strlen(readbuff) > 0 );

	return newpage;
}

int grab_emails(char *buff, int pointer, char *host)
{
	int ctr = 0;
	char flippedemail[NCOL];
	char email[NCOL];

	memset(email, '\0', sizeof(email));
	memset(flippedemail, '\0', sizeof(flippedemail));

	while(pointer >= 0 && ctr < NCOL && ( buff[pointer] == '-' || buff[pointer] == 64 || buff[pointer] == 46 || 
	     ( buff[pointer] >=48 && buff[pointer] <= 57) || ( buff[pointer] >=65 && buff[pointer] <= 90) || 
		( buff[pointer] >=97 && buff[pointer] <= 122))){

		/* Sometimes strings can contain %3Dhost.com %3D being an equals sign, sometimes seen in
		   php query strings etc. */

		if ( buff[pointer] == 'D' && buff[pointer - 1] == '3' && buff[pointer - 2] == '%') break;

		flippedemail[ctr] = buff[pointer];

		if ( buff[pointer] == '>' && buff[pointer - 1] == 'b' && buff[pointer - 2] == '/' && buff[pointer - 3] == '<' ) pointer -= 4;
		if ( buff[pointer] == '>' && buff[pointer - 1] == 'b' && buff[pointer - 2] == '<' ) pointer -= 3;
		ctr++;
		pointer--;
	}

	/* This stops possible buffer overflows */
	if ( strlen(flippedemail) >= NCOL) return 0;

	for(ctr=(int)strlen(flippedemail);ctr >= 0;ctr--){
		email[strlen(email)] = flippedemail[ctr];
	}
	if (! strlen(email) || strlen(email) >= NCOL || email[0] == '@' || !strstr(email, "@")) return 0;
	if ( emaillist(email, host) ) return 1;

	return 0 ;
}

int emaillist(char *email, char *host)
{
	char output[128];
	int i = 0;

        for(i=0;i < emailcount && emailcount > 0;i++){
		if (! strcmp(emailbuff[i], email) ){
			return 0;
		}
        }

	emailbuff = realloc(emailbuff, (emailcount+1) * (sizeof(char) * NCOL));
	if (!emailbuff){
		print_line("ERROR: Realloc in E-MailSearch module failed\n");
		return 1;
	}
	emailbuff[emailcount] = malloc(NCOL*sizeof(char));
	if (!emailbuff[emailcount]) print_line("ERROR: Malloc in E-MailSearch module failed\n");	

        strcpy(emailbuff[emailcount], email);

        snprintf(output, sizeof(output), "%s%s\n", emailbuff[emailcount], host);
	print_line("%s", output);
	emailcount++;
	return 0;
}
