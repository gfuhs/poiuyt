#include "Main.h"
#include "MakerDoc.h"
#include "Css.h"
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "TreeChar.h"
#include "Ensemble.h"

int main (int argc, char* argv[])
{
	int i;
	ListEns list = NULL;
	TreeChar* arborescence = NULL;
	
	mkdir("doc",S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
	makeCss(0,"doc/");
	arborescence = CreateTree(".");
	for(i=1;i<argc;i++)
	{
		if(AddEnsemble(&list, argv[i],arborescence)==0)
		{
		  fprintf(stderr,"Fichier %s non trouver dans l'arborescence du projet\n",argv[i]);
		  return 1;
		}
		if(makeDoc(list) == 0)
		{
		 	fprintf(stderr,"Erreur lors de la création de la documentation de %s\n",argv[i]);
		 	return 1;	
		}
		RemoveEnsemble(&list);	
	}	
	return 0;
}