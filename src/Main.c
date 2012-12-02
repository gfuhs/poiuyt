#include "Main.h"
#include "MakerDoc.h"
#include "Css.h"
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "Ensemble.h"

int main (int argc, char* argv[])
{
	int i;
	ListEns list = NULL;
	
	mkdir("doc",S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH - S_IXOTH);
	makeCss(0,"doc/");
	for(i=1;i<argc;i++)
	{
		AddEnsemble(&list, argv[i]);
		if(makeDoc(list) == 0)
		{
		 	fprintf(stderr,"Erreur lors de la création de la documentation de %s\n",argv[i]);
		 	return 1;	
		}
		RemoveEnsemble(&list);	
	}	
	return 0;
}