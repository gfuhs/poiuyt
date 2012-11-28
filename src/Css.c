#include "Css.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void themeCreationD(FILE * fin)
{
	fprintf(fin, "body\n{\n\tbackground-color: black;\n\tbackground-image: url(images/bg.jpg);\n\tfont-family: Helvetica, Arial, sans-serif;\n\tfont-size: 14px;\n\tline-height: 1.6em;\n\tcolor: white;\n}\n\n\n");
	fprintf(fin, "#presentation\n{\n\tbackground: url(images/header.png);\n\tposition: relative;\n\twidth: 800px;\n\theight: 330px;\n\tmargin: 0 auto;\n}\n\n");
	fprintf(fin, "#presentation h1\n{\n\tdisplay: block;\n\tfloat: left;\n\tmargin: 45px 0 0 300px;\n\tposition: relative;\n\ttext-shadow: black 0em 0.1em 0.1em;\n\tfont-size: 28px;\n\tletter-spacing: 0.2em\n}\n\n");
	fprintf(fin, "li\n{\n\tlist-style-image: url(images/puce.png);\n}\n\n");
	fprintf(fin, "ol\n{\n\tmargin: 0 0 27 50;\n}\n\n");
	fprintf(fin, "#fonction\n{\n\tpadding: 10 0 10 10;\n\tdisplay: block;\n\tfloat: left;\n\tmargin: 25px 0 10 300px;\n\tposition: relative;\n\tbackground-color: grey;\n\twidth: 600px;box-shadow: 1px 0px 8px #000000;\n\tborder-top: 1px solid #bababa;\n\tborder-radius: 3px;\n\tmargin-bottom: 20px;\n}\n\n");
	fprintf(fin, "#fonction h2\n{\n\tfont-size: 17px;\n\tfont-style: italic;\n\tdisplay: block;\n\tfloat: left;\n\tmargin: 0 0 0 150px;\n}\n\n");
	fprintf(fin, "#fonction span\n{\n\tpadding: 0 0 0 40;\n}\n\n");
}


void printReset(FILE * reset)
{
		fprintf(reset, "html, body, div, span, h1, h2, h3, h4, h5, h6, p, a, img\n");
		fprintf(reset, "{\n\tmargin: 0; \n\tpadding: 0; \n\tborder: 0; \n\toutline: 0; \n\tfont-weight: inherit; \n\tfont-style: inherit; \n\tfont-size: 100%c; \n\tfont-family: inherit; \n\tvertical-align: baseline; \n}\n", '%');
		fprintf(reset, "\nbody\n{\n\tline-height: 1;\n\tcolor: black;\n\tbackground: white;\n}");
}


int makeCss(int theme, char* path)
{
	FILE * fout;
	FILE * reset;
	char * name = (char *) malloc (sizeof(char) * (strlen(path) + 12));
	char * namereset = (char *) malloc (sizeof(char) * (strlen(path) + 12));
	
	strcpy(name, path);
	strcat(name, "theme.css");

	if((fout = fopen(name,"w")) == NULL) 
	{
		return -1;
	}
	
	strcpy(namereset, path);
	strcat(namereset, "reset.css");
	
	if( (reset = fopen(namereset, "w")) == NULL)
	{
		fclose(fout);
		return -1;
	}
	
	printReset(reset);
	fclose(reset);
		
	switch(theme) 
	{
		case 1:
			themeCreationD(fout);
			break;
		default:
			themeCreationD(fout);
			break;
	}

	return fclose(fout);
}

