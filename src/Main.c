#include "Main.h"
#include "MakerDoc.h"
#include "Css.h"
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "TreeChar.h"
#include "Ensemble.h"
#include <getopt.h>
#include <stdlib.h>
#include <string.h>

extern int optind;

void method_fich_pass_argument(int argc,char* argv[])
{
	int i;
	ListEns list = NULL;
	TreeChar* arborescence = NULL;
	
	mkdir("doc",S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
	makeCss(0,"doc/");
	arborescence = CreateTree(".");
	for(i=optind;i<argc;i++)
	{
		if(AddEnsemble(&list, argv[i],arborescence,"./")==0)
		{
		  fprintf(stderr,"Fichier %s non trouver dans l'arborescence du projet\n",argv[i]);
		  exit(1);
		}
		if(makeDoc(list) == 0)
		{
		 	fprintf(stderr,"Erreur lors de la création de la documentation de %s\n",argv[i]);
		 	exit(1);	
		}
		RemoveEnsemble(&list);	
	}		
}

void method_chemin_projet(char* path)
{
	ListEns list = NULL;
	ListEns index = NULL;
	TreeChar* arborescence = NULL;
	char buff[1024];
	buff[0]='\0';
	strcat(buff,path);
	strcat(buff,"doc/");
	mkdir(buff,S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
	makeCss(0,buff);
	arborescence = CreateTree(path);
	GenerateEnsemble(&list,arborescence,arborescence,path);
	index=list;
	while(index!=NULL) 
	{
		if(makeDoc(index) == 0)
		{
		 	fprintf(stderr,"Erreur lors de la création de la documentation \n");
		 	exit(1);	
		}
		RemoveEnsemble(&index);
	}	
}

int main (int argc, char* argv[])
{
	static char optstring[]="vh";
	int cmdx = 0;
	int optch;
	static struct option long_opts[] = {
	    {"version",0,0,'v'},
	    {"help",0,0,'h'},
	    {0,0,0,0}
	};	
	
	while( (optch = getopt_long(argc, argv, optstring,long_opts,&cmdx)) != -1 )
	{
		switch(optch)
		{
			case 'v' :
				printf("Version 1.3 de MackerDoc\n");
				return 0;
			case 'h' :
				printf("En attente de création");
				return 0;
			default:
				printf("Option non reconnue\n Veuillez utiliser l'option -h ou --help\n");
				return 1;
		}
	}
	
	if((argc-optind)>1)
		method_fich_pass_argument(argc,argv);
	else if((argc-optind)==1)
	{
		if(strstr(argv[optind],".c")==NULL)
			method_chemin_projet(argv[optind]);
		else 
			method_fich_pass_argument(argc,argv);	
	}
	else 
		method_chemin_projet("./");

	return 0;
}
