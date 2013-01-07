#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Html.h"
#include "ModifFile.h"
#include "MakerDoc.h"


/**
 * \fn			int baliseCom(char* buff, char* string)
 * \brief		Function which return the code of an html tag
 * \details	buff contains a string which is a special tag and the contain of this tag.
 * \param		buff is a string which contains a special tag which correspond to an html tag.
 * \param		string is a pointer on a string to put in the html tag.
 * \return 	An integer which corresponds to an html tag.
 */
int baliseCom(char* buff, char** string)
{
	if((*string = strstr(buff, "\\file")) != NULL)
	{
		*string += 5;
		return 0;
	}
	
	if((*string = strstr(buff, "\\author")) != NULL)
	{
		*string += 7;
		return 1; 		
	}
	
	if((*string = strstr(buff, "\\version")) != NULL)
	{
		*string += 8;
		return 2; 		
	}
	
	if((*string = strstr(buff, "\\date")) != NULL)
	{
		*string += 5;
		return 3; 		
	}
	
	if((*string = strstr(buff, "\\brief")) != NULL)
	{
		*string += 6;
		return 4; 		
	}
	
	if((*string = strstr(buff, "\\details")) != NULL)
	{
		*string += 8;
		return 5; 		
	}
	
	if((*string = strstr(buff, "\\fn")) != NULL)
	{
		*string += 3;
		return 6; 		
	}
	
	if((*string = strstr(buff, "\\param")) != NULL)
	{
		*string += 6;
		return 7; 		
	}
	
	if((*string = strstr(buff, "\\return")) != NULL)
	{
		*string += 7;
		return 8; 		
	}
	
	if((*string = strstr(buff, "\\bug")) != NULL)
	{
		*string += 4;
		return 9; 		
	}
	
	if((*string = strstr(buff, "///")) != NULL)
	{
		*string += 3;
	}
	
	else if((*string = strstr(buff,"*")) != NULL)
	{
		*string += 1;
	}
	
	return -1; 		
}

int makeDoc(Ens * ens)
{
	FILE* fin;
	FILE* fout;
	char read_com = 0;
	char list_balise = 0;
	char buffer [1024];
	int balise;
	char* string;

	fout = newHtml(ens->file);
	fin = fusionFile(ens->path_file_c, ens->path_file_h, fout);

	Fonc_num = 0;
	
	while(feof(fin) == 0)
	{
		fgets(buffer, 1024, fin);	
			
		if(strstr(buffer,"/**") != NULL )
		{
			read_com = 1;
			continue;			
		}
		
		else if( strstr(buffer,"///")!=NULL)
		{
			read_com = 2;
		}
		
		else if( strstr(buffer,"*/")!=NULL )
		{
			read_com = 3;
			continue;
		}		
		
		else if(read_com == 3)
		{
			if(list_balise != 0)
			{
				newBalise(fout, -3, NULL);
				list_balise = 0;
			}
			read_com = 0;
			newBalise(fout, 10, NULL);
			continue;
		}
	
		if( read_com != 0)
		{
			if( (balise = baliseCom(buffer,&string)) == 0)
			{
				continue;
			}
		  
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
				newBalise(fout, -2, "Author(s)");
				list_balise = 1; 
			}
			
			if(list_balise == 0 && balise == 7)
			{
				newBalise(fout, -2, "Arguments(s)");
				list_balise = 2;
			}
			
			newBalise(fout, balise, string);	
		}	
		
		if(read_com == 2)
		{
			read_com = 3;
		}
	}
	
	closeHtml(fout);
	close_fusion(fin);
	return 1;
}
