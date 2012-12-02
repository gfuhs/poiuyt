#include "MakerDoc.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Html.h"
#include "ModifFile.h"


/**
 * \fn			int baliseCom(char* buff, char* string)
 * \brief		Fonction qui renvoie le code d'une balise html 
 * \details	On fournit dans buff une chaine de caractère une balise spécial ainsi que le contenu de cette balise
 * \param		buff est une chaine de caractère qui contient une balise spécial correspondant à une balise html
 * \param		string est un pointeur sur une chaine de caractère à mettre dans la balise html
 * \return 	un int correspondant à la balise html
 */
 int baliseCom(char* buff, char** string)
 {
		 if( (*string=strstr(buff,"\\file"))!=NULL)
		 {
			*string += 5;
 			return 0;
		 }
 		
 		if((*string=strstr(buff,"\\author"))!=NULL)
 		{
			*string += 7;
			return 1; 		
 		}
 		
 		if((*string=strstr(buff,"\\version"))!=NULL)
 		{
			*string += 8;
			return 2; 		
 		}
 		
 		if((*string=strstr(buff,"\\date"))!=NULL)
 		{
			*string += 5;
			return 3; 		
 		}
 		
 		if((*string=strstr(buff,"\\brief"))!=NULL)
 		{
			*string += 6;
			return 4; 		
 		}
 		
 		if((*string=strstr(buff,"\\details"))!=NULL)
 		{
			*string += 8;
			return 5; 		
 		}
 		
 		if((*string=strstr(buff,"\\fn"))!=NULL)
 		{
			*string += 3;
			return 6; 		
 		}
 		
 		if((*string=strstr(buff,"\\param"))!=NULL)
 		{
			*string += 6;
			return 7; 		
 		}
 		
 		if((*string=strstr(buff,"\\return"))!=NULL)
 		{
			*string += 7;
			return 8; 		
 		}
 		
 		if((*string=strstr(buff,"\\bug"))!=NULL)
 		{
			*string += 4;
			return 9; 		
 		}
 		
 		if((*string=strstr(buff,"///"))!=NULL)
 			*string += 3;
 		else if((*string=strstr(buff,"*"))!=NULL)
 			*string += 1;
		return -1; 		
 }

int makeDoc(Ens* ens)
{
	FILE* fin;
	FILE* fout;
	char read_com =0;
	char list_balise=0;
	char buffer [1024];
	int balise;
	char* string;

	fout = newHtml(ens->file);
	fin = fusionFile(ens-> path_file_c, ens-> path_file_h, fout);

	Fonc_num = 0;
	while(feof(fin)==0)
	{
		fgets(buffer,1024,fin);		
		if(strstr(buffer,"/**") != NULL )
		{
			read_com = 1;
			continue;			
		}
		if( strstr(buffer,"///")!=NULL)
			read_com = 2;
		if( strstr(buffer,"*/")!=NULL || read_com == 3)
		{
			read_com = 0;
			newBalise(fout,10,NULL);
			continue;		
		}		
	
		if( read_com != 0)
		{
			if( (balise = baliseCom(buffer,&string)) == 0)
			  continue;
			if(list_balise == 1 && balise != 1)
			{
				newBalise(fout,-3,NULL);
				list_balise = 0;
			}
			if(list_balise == 2 && balise != 7)
			{
				newBalise(fout,-3,NULL);
				list_balise = 0;
			}
			if(list_balise == 0 && balise == 1)
			{
				newBalise(fout,-2,"Auteur(s)");
				list_balise = 1; 
			}
			if(list_balise == 0 && balise == 7)
			{
				newBalise(fout,-2,"Paramètre(s)");
				list_balise = 2;
			}
			newBalise(fout, balise, string);	
		}	
		if(read_com == 2)
			read_com=0;
	}
	
	closeHtml(fout);
	close_fusion(fin);
	return 1;
}
