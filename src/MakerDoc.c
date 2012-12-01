#include "MakerDoc.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Html.h"


/**
 * \fn			int baliseCom(char* buff, char* string)
 * \brief		Return the code of an html tag.
 * \param		buff	is a string which contains a special tag corresponding to an html tag
 * \param		string	is a pointer on a string to put in the html tag.
 * \return		An integer which corresponds to a special exit code.
 */
 int baliseCom(char* buff, char** string)
 {
	if( (*string = strstr(buff,"\\file")) != NULL)
	{
		*string += 5;
		return 0;
	}

	if((*string = strstr(buff,"\\author")) != NULL)
	{
		*string += 7;
		return 1; 		
	}

	if((*string = strstr(buff,"\\version")) != NULL)
	{
		*string += 8;
		return 2; 		
	}
	
	if((*string = strstr(buff,"\\date")) != NULL)
	{
		*string += 5;
		return 3; 		
	}
	
	if((*string = strstr(buff,"\\brief")) != NULL)
	{
		*string += 6;
		return 4; 		
	}
	
	if((*string = strstr(buff,"\\details")) != NULL)
	{
		*string += 8;
		return 5; 		
	}
	
	if((*string = strstr(buff,"\\fn")) != NULL)
	{
		*string += 3;
		return 6; 		
	}
	
	if((*string = strstr(buff,"\\param")) != NULL)
	{
		*string += 6;
		return 7; 		
	}
	
	if((*string = strstr(buff,"\\return")) != NULL)
	{
		*string += 7;
		return 8; 		
	}
	
	if((*string = strstr(buff,"\\bug")) != NULL)
	{
		*string += 4;
		return 9; 		
	}
	
	if((*string=strstr(buff,"///"))!=NULL)
	{
		*string += 3;
	}
	
	else if((*string=strstr(buff, "*"))!=NULL)
	{
		*string += 1;
	}
	
	return -1; 		
}

int makeDoc(char* file)
{
	char read_com = 0;
	char list_balise = 0;
	int balise;
	int size_file = strlen(file);
	char * string;
	char buffer [1024];
	char * fout_name = (char*) malloc(sizeof(char) * (size_file + 12));
	FILE * fin;
	FILE * fout;

	if(fout_name == NULL)
	{	
		return -1;
	}

	if( (string = strrchr(file,'/')) == NULL)
	{
	 	strcpy(fout_name, "doc/");
	 	strcat(fout_name, file);
	 	size_file = strlen(fout_name);
	 	fout_name[size_file - 1] = 'h';
		fout_name[size_file] = 't';
		fout_name[size_file + 1] = 'm';
		fout_name[size_file + 2] = 'l';
		fout_name[size_file + 3] = '\0';	
	}

	else
	{
		strcpy(fout_name,file);
		string = strrchr(fout_name,'/');
		string[1] = '\0';
		strcat(string,"../doc/");
		string = strrchr(fout_name,'/');
		string[1] = '\0';
		strcat(string,strrchr(file,'/') + 1);
		size_file = strlen(fout_name);
		fout_name[size_file - 1] = 'h';
		fout_name[size_file] = 't';
		fout_name[size_file + 1] = 'm';
		fout_name[size_file + 2] = 'l';
		fout_name[size_file + 3] = '\0';		
	}

	fin = fopen(file,"r");
	fout = newHtml(fout_name);
		
	while(feof(fin) == 0)
	{
		fgets(buffer, 1024, fin);	
	
		if(strstr(buffer, "/*") != NULL )
		{
			read_com = 1;
			continue;			
		}

		if( strstr(buffer,"///")!=NULL)
		{
			read_com = 2;
		}

		if( strstr(buffer,"*/") != NULL || read_com == 3)
		{
			read_com = 0;
			newBalise(fout, 10, NULL);
			continue;		
		}		
	
		if( read_com != 0)
		{
			balise = baliseCom(buffer, &string);

			if(list_balise == 1 && balise != 1)
			{
				newBalise(fout, -3, NULL);
				list_balise = 0;
			}

			if(list_balise == 2 && balise != 7)
			{
				newBalise(fout, -3, NULL);
				list_balise = 0;
			}

			if(list_balise == 0 && balise == 1)
			{
				newBalise(fout, -2, "Auteur(s)");
				list_balise = 1; 
			}

			if(list_balise == 0 && balise == 7)
			{
				newBalise(fout, -2, "Paramètre(s)");
				list_balise = 2;
			}
	
			newBalise(fout, balise, string);	
		}	
	
		if(read_com == 2)
		{
			read_com=0;
		}
	}
	
	closeHtml(fout);
	fclose(fin);
	free(fout_name);
		
	return 1;
}
