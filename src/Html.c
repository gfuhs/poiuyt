#include "Html.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int Fonc_num = 0;

FILE* newHtml(char *name)
{
 	FILE* fout;
 	
 	if( (fout = fopen(name, "w")) == NULL)
	{
 		return NULL;
	}
 		
 	fprintf(fout, "<html>\n\t<head>\n\t\t<title>%s</title>\n\t\t<meta http-equiv=\"content-type\" content=\"text/html;charset=UTF-8\"/>\n\t\t<link rel=\"stylesheet\" type=\"text/css\" href=\"reset.css\">\n\t\t<link rel=\"stylesheet\" type=\"text/css\" href=\"theme.css\">\n\t</head>\n\n\t<body>\n", name);

 	return fout;	
}

 
int closeHtml(FILE* file)
{
	fprintf(file, "\t</body>\n\n</html>\n"); 
	return fclose(file); 	
}


void putTab (FILE * file, int nb)
{
	int i;
	
	for(i = 0; i < nb; i++)
	{
		fprintf(file, "\t");
	}
}


void putSpace (FILE * file, int nb)
{
	int i;
	
	for(i = 0; i < nb; i++)
	{
		fprintf(file, "\t\t\t<p>\n\t\t\t\t&nbsp\n\t\t\t</p>\n\n");
	}
}


void newBalise(FILE* file, int code, char* String)
{
	char * tmp;
	
	switch(code) 
	{
		case -3 :
			putTab(file, 3);
			fprintf(file, "</ol>\n\n");
			break;	

		case -2 :	
			putTab(file, 3);
			fprintf(file, "<b>%s :</b>\n", String);
			putTab(file, 3);
			fprintf(file, "<ol>\n");
			break;
	
		case -1 :
			putTab(file, 2);
			fprintf(file, "\t%s", String);
			break;

		case 0 :
			putTab(file, 2);
			fprintf(file, "<div id=\"presentation\">\n");
			putTab(file, 3);
			
			tmp = (char *)malloc(sizeof(char) * (strlen(String) + 1));
			if(tmp == NULL)
			{	
				fprintf(stderr, "Error in memory\n");
				exit(1);
			}
			
			strcpy(tmp, String);
			tmp[strlen(String) - 1] = '\0';
			
			fprintf(file, "<h1>%s</h1>\n", tmp);
			putSpace(file, 4);
			free(tmp);
			break;

		case 2 :
			putTab(file, 3);
			fprintf(file, "<b>Version :</b>%s", String);
			putTab(file, 3);
			fprintf(file, "<br>\n\n");
			break;
		case 3 :
			putTab(file, 3);
			fprintf(file, "<b>Date :</b> %s", String);
			putTab(file, 3);
			fprintf(file, "<br>\n\n");
			putSpace(file, 1);
			break;

		case 4 :
			putTab(file, 3);
			fprintf(file, "<p>\n");
			putTab(file, 2);
			fprintf(file, "\t%s", String);
			putTab(file, 3);
			fprintf(file, "</p>\n\n");
			putSpace(file, 1);
			break;

		case 5 :
			putTab(file, 3);
			fprintf(file, "<p>\n%s", String);
			putTab(file, 3);
			fprintf(file, "</p>\n\n");
			putSpace(file, 1);
			break;

		case 6 :
			putTab(file, 2);
			fprintf(file, "<div id=\"fonction\">\n");
			putTab(file, 3);
			
			tmp = (char *)malloc(sizeof(char) * (strlen(String) + 1));
			if(tmp == NULL)
			{	
				fprintf(stderr, "Error in memory\n");
				exit(1);
			}
			
			strcpy(tmp, String);
			tmp[strlen(String) - 1] = '\0';
			
			fprintf(file, "<h2 id=\"fonc_%d\">%s</h2>\n", Fonc_num, tmp);
			Fonc_num++;
			
			free(tmp);
			putSpace(file, 2);
			break;

		case 1 :
		case 7 :
			putTab(file, 4);
			
			tmp = (char *)malloc(sizeof(char) * (strlen(String) + 1));
			if(tmp == NULL)
			{	
				fprintf(stderr, "Error in memory\n");
				exit(1);
			}
			
			strcpy(tmp, String);
			tmp[strlen(String) - 1] = '\0';
			
			fprintf(file, "<li>%s</li>\n", tmp);
			free(tmp);
			break;

		case 8 :
			putTab(file, 3);
			fprintf(file, "<p>\n");
			putTab(file, 4);
			
			tmp = (char *)malloc(sizeof(char) * (strlen(String) + 1));
			if(tmp == NULL)
			{	
				fprintf(stderr, "Error in memory\n");
				exit(1);
			}
			
			strcpy(tmp, String);
			tmp[strlen(String) - 1] = '\0';
			
			fprintf(file, "<b>Return</b><br><span>%s</span>\n", tmp);
			free(tmp);
			
			putTab(file, 3);
			fprintf(file, "</p>\n\n");
			putSpace(file, 1);
			break;

		case 9 :
			putTab(file, 3);
			fprintf(file, "<p>\n");
			putTab(file, 3);
			
			tmp = (char *)malloc(sizeof(char) * (strlen(String) + 1));
			if(tmp == NULL)
			{	
				fprintf(stderr, "Error in memory\n");
				exit(1);
			}
			
			strcpy(tmp, String);
			tmp[strlen(String) - 1] = '\0';
			
			fprintf(file, "<b>Bug</b>%s", tmp);
			free(tmp);
			
			putTab(file, 2);
			fprintf(file, "</p>\n");
			putSpace(file, 1);
			break;	
	
		case 10 :
			putTab(file, 2);
			fprintf(file, "</div>\n\n");
			break;
			
		case 11 :
			putTab(file, 3);
			
			tmp = (char *)malloc(sizeof(char) * (strlen(String) + 1));
			if(tmp == NULL)
			{	
				fprintf(stderr, "Error in memory\n");
				exit(1);
			}
			
			strcpy(tmp, String);
			tmp[strlen(String) - 1] = '\0';
			
			fprintf(file, "<a name=\"%s\">%s</a>", tmp, tmp);
			break;
			
		case 12 :
			putTab(file, 3);
			
			tmp = (char *)malloc(sizeof(char) * (strlen(String) + 1));
			if(tmp == NULL)
			{	
				fprintf(stderr, "Error in memory\n");
				exit(1);
			}
			
			strcpy(tmp, String);
			tmp[strlen(String) - 1] = '\0';
			
			fprintf(file, "<li><a href=\"#fonc_%d\">%s</a></li>\n", Fonc_num, tmp);
			Fonc_num++;
			free(tmp);
			break;
		
	}
}
