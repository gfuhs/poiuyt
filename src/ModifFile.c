#include "ModifFile.h"
#include "Html.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * \fn		int ordreFile(char* file, char* name)
 * \brief	Function which determinate if the file contains the head tag	
 * \param		file	is the name of the file to scan
 * \param		name 	is the name of the module if the head tag is found 
 * \return		Retourne 1 si oui sinon 0
 */
int ordreFile(char* file, char* name)
{
	char buffer[1024];
	char *pos;
	FILE* tmp;
	
 	if( (tmp = fopen(file, "r")) == NULL) 
 	{
	 	fprintf(stderr, "Erreur lors de la création d'un fichier temporaire\n");
 		exit(EXIT_FAILURE);
 	}  
 	
	while(feof(tmp) == 0)
 	{
 			fgets(buffer, 1024, tmp);
 			
			if( (pos = strstr(buffer, "\\file")) != NULL)
			{
			    pos += 5;
			    strcpy(name, pos);
			    fclose(tmp);
			    return 1;
			}
			
			else if(strstr(buffer, "\\fn") != NULL)
			{
			    fclose(tmp);
			    return 0;
			}
	}
	
	return 0;
}

/**
 * \fn         void copieCom(FILE* fin, FILE* fout, FILE* html)
 * \brief	   Function which copy the comments of a file in another and do the list of the functions from the source file. 
 * \param      fin	is a pointer on the input file.
 * \param      fout	is a pointer on the output file.
 * \param      html	is a pointer on the html file which contains the documentation of the input file.  
 */
void copieCom(FILE* fin, FILE* fout, FILE* html)
{
	char buffer[1024];
	char code_read = 0;
	char* s;

	while(feof(fin) == 0)
 	{
 			fgets(buffer, 1024, fin);

 			if(strstr(buffer,"/**") != NULL && buffer[0] == '/')
 			{
 				code_read = 1;
			}
			
 			else if(strstr(buffer,"///") != NULL && buffer[0] == '/') 
 			{
 				code_read = 2;
			}
			
			else if(code_read == 2)
			{
			  code_read = 0;
			  fprintf(fout, "\n\n");
			}

 			if(code_read != 0)
			{
				fprintf(fout, "%s", buffer);
			  
				if( (s = strstr(buffer,"\\fn")) != NULL) 
				{
					s += 3;
					newBalise(html, 12, s);
				} 		
			  		
				if(strstr(buffer,"*/")!= NULL)
				{
					code_read = 2;
				}
			}
 			
 	}
 		
} 

/**
 * \fn         FILE* fusionFile(char *fileC, char* fileH, FILE* fileHtml)
 * \brief      Function which merge the comments of two files, one .c and the other .h
 * \param      fileC	is the path of the file.c
 * \param		fileH	is the path of the file.h
 * \param		fileHtml is a pointer on the html file which contains the documentation of both files.
 * \return     A pointer on the file which contains the merging of the comments.
 */
FILE* fusionFile(char *fileC, char* fileH, FILE* fileHtml)
{
	FILE* tmp;
	FILE* fc;
	FILE* fh;
	char string[1024];
	
 	if( (tmp = fopen("tmp", "w")) == NULL) 
 	{
	 	fprintf(stderr, "Erreur lors de la création d'un fichier temporaire\n");
 		exit(EXIT_FAILURE);
 	}	
 	
 	if( (fc = fopen(fileC, "r")) == NULL) 
 	{
	 	fprintf(stderr, "Erreur lors de l'ouverture d'un fichier\n");
 		exit(EXIT_FAILURE);
 	}	
 	
 	if( (fh = fopen(fileH, "r")) == NULL) 
 	{
	 	fprintf(stderr, "Erreur lors de l'ouverture d'un fichier\n");
 		exit(EXIT_FAILURE);
 	}	
 	
 	Fonc_num = 0;
 	
	if(ordreFile(fileC, string))
	{
		newBalise(fileHtml, 0, string);
		newBalise(fileHtml, -2, "Fonction(s)");
	  
		copieCom(fc, tmp, fileHtml);
		copieCom(fh, tmp, fileHtml);
	}
	
	else if (ordreFile(fileH, string))
	{
		newBalise(fileHtml, 0, string);
		newBalise(fileHtml, -2, "Fonction(s)");
		copieCom(fh, tmp, fileHtml);
		copieCom(fc, tmp, fileHtml);	  
	}
	
	else
	{
		fprintf(stderr,"Balise d'en-tête introuvable pour un ensemble de fichier\n");
		exit(EXIT_FAILURE);
	}
	
	fclose (fc);
	fclose(fh); 	
	fclose(tmp);
	
	if( (tmp = fopen("tmp", "r")) == NULL) 
	{
	 	fprintf(stderr, "Erreur lors de la création d'un fichier temporaire\n");
 		exit(EXIT_FAILURE);
 	}
 	
 	newBalise(fileHtml, -3, NULL);
 	
 	return tmp;	
}

/**
 * \fn         void close_fusionFile(FILE* file)
 * \brief      Function which closes a merged file and destroy it.
 * \param      file	is the pointer on the merged file.
 */
  void close_fusion(FILE* file)
  {
    fclose(file);
    unlink("tmp");
  }
