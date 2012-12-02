#ifndef ENSEMBLE_H
#define ENSEMBLE_H

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
 * \version   2.0
 * \date      2 Décembre 2012
 * \brief     Rassemble les fichiers correspondant à une même entité.
 *
 * Bibliothèque permettant de récupéré une structure contenant l'ensemble des fichiers
 * correspondant à une même entité.
 */

int AddEnsemble(ListEns* list, char *name);
int RemoveEnsemble(ListEns* list);

#endif