#include "Css.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void themeCreationD(FILE* fin)
{

}

int makeCss(int theme, char* path)
{
	FILE* fout;
	char* name = (char*)malloc(sizeof(char)*(strlen(path)+12));
	
	strcpy(name,path);
	strcat(name,"theme.css");
	if((fout=fopen(name,"w"))==NULL) 
		return -1;
		
	switch(theme) {
			case 1:
				themeCreationD(fout);
				break;
			default:
				themeCreationD(fout);
	}
	return fclose(fout);
}

