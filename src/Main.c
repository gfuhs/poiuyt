#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <getopt.h>
#include "TreeChar.h"
#include "Ensemble.h"
#include "Main.h"
#include "MakerDoc.h"
#include "Css.h"
#include "Html.h"

extern int optind;
int cssind = 0;
 
/**
 * \fn		void method_file_pass_argument(int argc, char * argv[])
 * \details		The program assume that the current directory is the root of the project.
 * \param		\i argc \i  number of arguments on the command line.
 * \brief		Create the documentation with the files on the command line from the current directory.
 * \param	 	\i argv \i Table of the arguments of the command line.
 */
void method_file_pass_argument(int argc, char * argv[])
{
	int i;
	ListEns list = NULL;
	TreeChar* arborescence = NULL;
	FILE* index;
	
	mkdir("./doc/", S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
	makeCss(cssind, "./doc/");
	
	arborescence = CreateTree(".");
	
	index = newHtml("./doc/index.html");
	print_TreeChar(index, arborescence, 0);
	
	closeHtml(index);
	
	for(i = optind; i < argc; i++)
	{
		if(AddEnsemble(&list, argv[i],arborescence, "./") == 0)
		{
			fprintf(stderr,"Fichier %s non trouver dans l'arborescence du projet\n", argv[i]);
			exit(1);
		}
		
		if(makeDoc(list) == 0)
		{
		 	fprintf(stderr,"Erreur lors de la création de la documentation de %s\n", argv[i]);
		 	exit(1);	
		}
		
		RemoveEnsemble(&list);	
	}		
	
	free_TreeChar(arborescence);
}


/**
 * \fn         void method_path_project(char * path)
 * \param      \i path	\i is the name of the \g path of the root of the project \g .
 * \brief      Run the program with the path to the root of the project.
 */
void method_path_project(char * path)
{
	char buff[1024];
	ListEns list = NULL;
	ListEns index = NULL;
	TreeChar* arborescence = NULL;
	FILE * indexf;
	
	buff[0] = '\0';
	strcat(buff, path);
	strcat(buff, "doc/");
	mkdir(buff, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
	
	makeCss(cssind, buff);
	arborescence = CreateTree(path);
	strcat(buff, "index.html");	
	indexf = newHtml(buff);
	
	newBalise(indexf, 0, "Arborescence du projet\n");
	putSpace(indexf, 3);
	print_TreeChar(indexf, arborescence, 0);
	closeHtml(indexf);
	
	GenerateEnsemble(&list, arborescence, arborescence, path);
	index = list;
	
	while(index != NULL) 
	{
		if(makeDoc(index) == 0)
		{
		 	fprintf(stderr, "Erreur lors de la création de la documentation \n");
		 	exit(1);	
		}
		
		RemoveEnsemble(&index);
	}	
	
	free_TreeChar(arborescence);
}


int main (int argc, char * argv[])
{
	static char optstring[] = "vhc:";
	int cmdx = 0;
	int optch;
	
	static struct option long_opts[] = {
	    {"version", 0, 0, 'v'},
	    {"help", 0, 0, 'h'},
	    {"css",1,0,'c'},
	    {0, 0, 0, 0}
	};	
	
	while( (optch = getopt_long(argc, argv, optstring, long_opts, &cmdx)) != -1 )
	{
		switch(optch)
		{
			case 'v' :
				fprintf(stderr, "Version 1.4.3 de MakerDoc\n");
				return 0;
				
			case 'h' :
				printf("Option(s) possible(s) :\n");
				printf("\t -v ou --version affiche la version du programme\n");
				printf("\t -h ou --help affiche l'aide\n");
				printf("\t -c ou --css prend un argument du type int correpondant à un thème particulier (0 pour thème par default et 1 pour thème light)\n\n");				
				printf("Utilisation possible :\n");
				printf("- user@pc:~$ docmycode fichier1.c fichier2.c main.c (L'ensemble des fichiers sources à documenter passés en arguments)\n");
				printf("- user@pc:~$ docmycode /chemin/vers/mon/projet/ (Un chemin vers la racine du projet est passé en argument)\n");
				printf("- user@pc:/chemin/vers/mon/projet/$ docmycode (Le programme est appelé depuis la racine du projet)\n\n");
				return 0;
			
			case 'c' :
			      sscanf(optarg,"%d",&cssind);
			      break;
			      
			default:
				fprintf(stderr, "Option non reconnue\n Veuillez utiliser l'option -h ou --help\n");
				return 1;
		}
	}
	
	if((argc-optind) > 1)
	{
		method_file_pass_argument(argc, argv);
	}
	
	else if( (argc-optind) == 1)
	{
		if(strstr(argv[optind], ".c") == NULL)
		{
			method_path_project(argv[optind]);
		}
		
		else
		{
			method_file_pass_argument(argc, argv);
		}
	}
	
	else
	{ 
		method_path_project("./");
	}

	return 0;
}
