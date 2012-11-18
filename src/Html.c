#include "Html.h"
#include <stdio.h>
#include <string.h>

FILE* newHtml(char *name)
{
 	FILE* fout;
 	
 	if((fout=fopen(name,"w"))== NULL)
 		return NULL;
 		
 	fprintf(fout,"<html>\n<head>\n\t<title>%s</title>\n\t<meta http-equiv=\"content-type\" content=\"text/html;charset=UTF-8\"/>\n\t<link rel=\"stylesheet\" type=\"text/css\" href=\"theme.css\">\n</head>\n<body>\n",name);
 	return fout;	
}
 
int closeHtml(FILE* file)
{
	fprintf(file,"</body>\n</html>\n"); 
	return fclose(file); 	
}

 void newBalise(FILE* file, int code, char* String)
{
	switch(code) {
		case -3 :
			fprintf(file,"</ol>\n");
			break;	
		case -2 :	
			fprintf(file,"<b>%s :</b>\n<ol>\n",String);
			break;
		case -1 :
			fprintf(file,"%s\n",String);
			break;
		case 0 :
			fprintf(file,"<div id=\"presentation\">\n\t<h1>%s</h1>\n",String);
			break;

		case 2 :
			fprintf(file,"<b>Version :</b> %s <br> \n",String);
			break;
		case 3 :
			fprintf(file,"<b>Date :</b> %s <br>\n",String);
			break;
		case 4 :
			fprintf(file,"<p>%s</p>\n",String);
			break;
		case 5 :
			fprintf(file,"<p>%s</p>",String);
			break;
		case 6 :
			fprintf(file,"<div id=\"fonction\">\n\t<h2>%s</h2>\n",String);
			break;
		case 1 :
		case 7 :
			fprintf(file,"<li>%s</li>\n",String);
			break;
		case 8 :
			fprintf(file,"<p><b>Return</b> %s </p>",String);
			break;
		case 9 :
			fprintf(file,"<p><b>Bug</b> %s</p>",String);
			break;		
		case 10 :
			fprintf(file,"</div>\n");
			break;
	}
}