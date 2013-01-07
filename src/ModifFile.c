#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "ModifFile.h"
#include "Html.h"

/**
 * \fn		int fileOrder(char* file, char* name)
 * \brief	Function which determinates if the file contains the head tag	
 * \param		file	is the name of the file to scan
 * \param		name 	is the name of the module if the head tag is found 
 * \return		Retourne 1 si oui sinon 0
 */
int fileOrder(char* file, char* name)
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

typedef struct cel{
	char* element;
	struct cel* next;	
}CelG,*ListG;

/** 
 * \fn		void initTab(void* tab[])
 *\bief		Function init the tab at null
 *\param		tab is the tab at init
 */
 void initTab(void* tab[])
 {
 	int i;
 	for(i=0;i<9;i++)
 		tab[i] = NULL;	
 }

/**
 * \fn 		void orderingBalise(void* tab[],char* buff)
 * \brief		Function stocke in tab the buff 
 * \param		tab is tab of stockage of element
 * \param		buff is the buffer of readinfg of the file reading
 */
 void orderingBalise(void* tab[], char* buff)
 {
 	char* tmp;
 	ListG list_tmp;
	ListG index;

	if(strstr(buff,"/**")!=NULL || strstr(buff,"*/")!=NULL) 
		return ; 	
 	
 	if( (tmp = (char*) malloc(sizeof(char)*(strlen(buff)+1))) == NULL)
	{
		fprintf(stderr,"Mémoire insuffisante");
		exit(1);
	}
	strcpy(tmp,buff);
	
 	if(strstr(buff,"\\file")!=NULL) 
 	{
		 tab[0] = tmp;
		 return ;
 	}	
 	if(strstr(buff,"\\fn")!=NULL) 
 	{
 		tab[0] = tmp;
 		return;
 	}	
  	if(strstr(buff,"\\author")!=NULL) 
 	{
		if( (list_tmp = (ListG)malloc(sizeof(CelG)) ) == NULL)
		{
			fprintf(stderr,"Mémoire insuffisante");
			exit(1);
		}
		list_tmp->element = tmp;
		list_tmp->next=tab[1];
 		tab[1] = list_tmp;
 		return;
 	}	
 	if(strstr(buff,"\\version")!=NULL) 
 	{
 		tab[2] = tmp;
 		return;
 	}	
 	if(strstr(buff,"\\date")!=NULL) 
 	{
 		tab[3] = tmp;
 		return;
 	}	
 	 if(strstr(buff,"\\brief")!=NULL) 
 	{
 		tab[4] = tmp;
 		return;
 	}	
 	if(strstr(buff,"\\param")!=NULL) 
 	{
		if( (list_tmp = (ListG)malloc(sizeof(CelG)) ) == NULL)
		{
			fprintf(stderr,"Mémoire insuffisante");
			exit(1);
		}
		list_tmp->element = tmp;
		list_tmp->next=tab[6]; 		
 		tab[6] = list_tmp;
 		return ;
 	}	
 	if(strstr(buff,"\\return")!=NULL) 
 	{
 		tab[7] = tmp;
 		return;
 	}	
 	if(strstr(buff,"\\bug")!=NULL) 
 	{
		if( (list_tmp = (ListG)malloc(sizeof(CelG)) ) == NULL)
		{
			fprintf(stderr,"Mémoire insuffisante");
			exit(1);
		}
		list_tmp->element = tmp;
		list_tmp->next=tab[8]; 		
 		tab[8] = list_tmp;
 		return ;
 	}	
 	
	if( (list_tmp = (ListG)malloc(sizeof(CelG)) ) == NULL)
	{
		fprintf(stderr,"Mémoire insuffisante");
		exit(1);
	}
	list_tmp->element = tmp;
	list_tmp->next = NULL;
	for(index=tab[5];index!=NULL && index->next!=NULL;index= index->next)
	  ;
	if(index == NULL)
	  tab[5] = list_tmp;
	else
	  index->next = list_tmp;
 }  

/**
 *\fn		void printTab(void* tab[] , FILE* out)
 *\brief		Function print the tab in flux out
 *\param		tab is the tab at printing
 *\param		out is the flux where print the tab
 */
void printTab(void* tab[], FILE* out)
{
	int i;
	ListG tmp;
	fprintf(out,"/**\n");
	for(i=0;i<9;i++)
	{
		if(tab[i]==NULL) 
			continue;
		if(i==1 || i==5 || i==6 || i==8)
		{
			while(tab[i]!=NULL)
			{
				fprintf(out,"%s",((ListG)tab[i])->element);
				tmp = tab[i];
				tab[i]=((ListG)tab[i])->next;
				free(tmp);
			}
		}	
		else
		{
			fprintf(out,"%s",(char*)tab[i]);
			free(tab[i]);
			tab[i]= NULL;	
		}			
	}	
	fprintf(out,"*/\n\n\n");
} 
 
/**
 * \fn         void copyCom(FILE* fin, FILE* fout, FILE* html)
 * \brief	   Function which copy the comments of a file in another and do the list of the functions from the source file. 
 * \param      fin	is a pointer on the input file.
 * \param      fout	is a pointer on the output file.
 * \param      html	is a pointer on the html file which contains the documentation of the input file.  
 */
void copyCom(FILE* fin, FILE* fout, FILE* html)
{
	int fnfound = 0;
	char buffer[1024];
	char code_read = 0;
	char* s;
	void* tab[9] ;
	
	initTab(tab); 
	while(feof(fin) == 0)
 	{
		fgets(buffer, 1024, fin);

		if(strstr(buffer,"/**") != NULL && buffer[0] == '/')
		{
			code_read = 1;
		}
		
		else if(strstr(buffer, "///") != NULL && buffer[0] == '/') 
		{
			code_read = 2;
		}
		
		else if(code_read == 2)
		{
			code_read = 0;
			printTab(tab, fout);
		}

		if(code_read != 0)
		{
			orderingBalise(tab, buffer);
		  
			if( (s = strstr(buffer, "\\fn")) != NULL) 
			{
				s += 3;
				newBalise(html, 12, s);
				fnfound = 1;
			} 		
			
			else if ((s = strstr(buffer, "\\brief")) != NULL && fnfound == 1)
			{
				s += 6;
				newBalise(html, -1, s);
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
	
 	if( (tmp = fopen(".tmp", "w")) == NULL) 
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
 	
	if(fileOrder(fileC, string))
	{
		newBalise(fileHtml, 0, string);
		newBalise(fileHtml, -2, "Fonction(s)");
	  
		copyCom(fc, tmp, fileHtml);
		copyCom(fh, tmp, fileHtml);
	}
	
	else if (fileOrder(fileH, string))
	{
		newBalise(fileHtml, 0, string);
		newBalise(fileHtml, -2, "Fonction(s)");
		copyCom(fh, tmp, fileHtml);
		copyCom(fc, tmp, fileHtml);	  
	}
	
	else
	{
		fprintf(stderr, "Balise d'en-tête introuvable pour le fichier %s ou le fichier %s\n", fileC, fileH);
		newBalise(fileHtml, 0, string);
		newBalise(fileHtml, -2, "Fonction(s)");
	  	copyCom(fc, tmp, fileHtml);
		copyCom(fh, tmp, fileHtml);
	}
	
	fclose(fc);
	fclose(fh); 	
	fclose(tmp);
	
	if( (tmp = fopen(".tmp", "r")) == NULL) 
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
    unlink(".tmp");
  }
