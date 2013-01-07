#ifndef ENSEMBLE_H
#define ENSEMBLE_H

#include "TreeChar.h"

typedef struct cel {
	char file[100];	
	char path_file_c[100];
	char path_file_h[100];
	struct cel *next;	
}Ens, *ListEns;

/**
 * \file      Ensemble.c
 * \author    Fuhs
 * \author    Moreau
 * \version   3.0
 * \date      11 Décembre 2012
 * \brief     Put together the file belonging to the same module.
 *
 * Library which get a structure containing the files of the same module.
 */

int AddEnsemble(ListEns* list, char *name, const TreeChar* tree, char* path);

int RemoveEnsemble(ListEns* list);

void GenerateEnsemble(ListEns* list,const TreeChar* tree,const TreeChar* node,char* path);

#endif
