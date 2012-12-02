#include "ModifFile.h"
#include "Html.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * \fn		int ordreFile(char* file, char* name)
 * \brief	Fonction qui détermine si le fichier contient la balise d'en-tête	
 * \param		file nom du fichier à tester s'il contient la balise d'en-tête
 * \param		name est la variable où on stockera le nom de l'ensemble de fichier si on trouve la balise d'en-tête 
 * \return		Retourne 1 si oui sinon 0
 */
int ordreFile(char* file,char* name)
{
	char buffer[1024];
	char *pos;
	FILE* tmp;
	
 	if( (tmp=fopen(file,"r"))==NULL) {
	 	fprintf(stderr,"Erreur lors de la création d'un fichier temporaire\n");
 		exit(EXIT_FAILURE);
 	}  
	while(feof(tmp)==0)
 	{
 			fgets(buffer,1024,tmp);
			if((pos=strstr(buffer,"\\file"))!=NULL)
			{
			    pos += 5;
			    strcpy(name,pos);
			    fclose(tmp);
			    return 1;
			}
			else if(strstr(buffer,"\\fn")!=NULL)
			{
			    fclose(tmp);
			    return 0;
			}
	}
	return 0;
}

/**
 * \fn         void copieCom(FILE* fin, FILE* fout, FILE* html)
 * \brief      Fonction copie les commentaires d'un fichier dans un autre et fait la liste des fonctions dans le fichier d'entrée 
 * \param      fin pointeur sur un fichier d'entrée
 * \param      fout pointeur sur un fichier de sortie 
 * \param      html	pointeur sur le fichier HTML qui correspond a la documentation du fichier d'entré  
 */
void copieCom(FILE* fin, FILE* fout, FILE* html)
{
	char buffer[1024];
	char code_read = 0;
	char* s;

	while(feof(fin)==0)
 	{
 			fgets(buffer,1024,fin);

 			if(strstr(buffer,"/**")!= NULL && buffer[0]=='/')
 				code_read = 1;
 			else if(strstr(buffer,"///")!=NULL && buffer[0]=='/') 
 				code_read=2;
			else if(code_read == 2)
			{
			  code_read=0;
			  fprintf(fout,"\n\n");
			}

 			if(code_read != 0)
			{
			  fprintf(fout,"%s",buffer);
			  if((s=strstr(buffer,"\\fn"))!=NULL) 
			  {
				s+=3;
				newBalise(html,12,s);
			  } 				
			  if(strstr(buffer,"*/")!= NULL)
 				code_read=2;
			}
 			
 	}
 		
} 

/**
 * \fn         FILE* fusionFile(char *fileC, char* fileH, FILE* fileHtml)
 * \brief      Fonction qui fusionne les commentaires de 2 fichiers un c et h 
 * \param      fileC	est le chemin vers le fichier c.
 * \param		fileH est le chemin vers le fichier h.
 * \param		fileHtml est un pointeur sur le fichier correspondant à la documentation du fichier c et h
 * \return     Renvoie un pointeur sur le fichier obtenue après fusions des commentaires du fichierc avec le fichier h
 */
FILE* fusionFile(char *fileC, char* fileH, FILE* fileHtml)
{
	FILE* tmp;
	FILE* fc;
	FILE* fh;
	char string[1024];
	
 	if( (tmp=fopen("tmp","w"))==NULL) {
	 	fprintf(stderr,"Erreur lors de la création d'un fichier temporaire\n");
 		exit(EXIT_FAILURE);
 	}	
 	if( (fc=fopen(fileC,"r"))==NULL) {
	 	fprintf(stderr,"Erreur lors de l'ouverture d'un fichier\n");
 		exit(EXIT_FAILURE);
 	}	
 	if( (fh=fopen(fileH,"r"))==NULL) {
	 	fprintf(stderr,"Erreur lors de l'ouverture d'un fichier\n");
 		exit(EXIT_FAILURE);
 	}	
 	
 	Fonc_num = 0;
	if(ordreFile(fileC,string))
	{
	  newBalise(fileHtml,0,string);
	  newBalise(fileHtml, -2, "Fonction(s)");
	  copieCom(fc, tmp, fileHtml);
	  copieCom(fh,tmp, fileHtml);
	}
	else if (ordreFile(fileH,string))
	{
	  newBalise(fileHtml,0,string);
	  newBalise(fileHtml, -2, "Fonction(s)");
	  copieCom(fh, tmp, fileHtml);
	  copieCom(fc,tmp, fileHtml);	  
	}
	else
	{
	  fprintf(stderr,"Balise d'en-tête introuvable pour un ensemble de fichier\n");
	  exit(EXIT_FAILURE);
	}
	fclose (fc);
	fclose(fh); 	
	fclose(tmp);
	if( (tmp=fopen("tmp","r"))==NULL) {
	 	fprintf(stderr,"Erreur lors de la création d'un fichier temporaire\n");
 		exit(EXIT_FAILURE);
 	}
 	newBalise(fileHtml,-3,NULL);
 	
 	return tmp;	
}

/**
 * \fn         void close_fusionFile(FILE* file)
 * \brief      Fonction qui ferme un fichier fusionner et le détruit 
 * \param      file	est le pointeur sur le fichier fusionner
 */
  void close_fusion(FILE* file)
  {
    fclose(file);
    unlink("tmp");
  }