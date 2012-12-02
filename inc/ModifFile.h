#ifndef MODIFFILE_H
#define MODIFFILE_H

#include <stdio.h>

/**
 * \file      MofifFile.c
 * \author    Fuhs
 * \author    Moreau
 * \version   2.0
 * \date      2 Décembre 2012
 * \brief     Bibliothèque permettant la manipulation de fichier.
 *
 * Bibliothèque contenant les fonctions permettant de manipuler un ensemble de fichier.
 */

/**
 * \fn         FILE* fusionFile (char *fileC, char* fileH, FILE* fileHtml)
 * \brief      Fonction fusionnant les commentaires des fichiers c et h et qui fait la liste des fonctions dans le fichier html 
 * \param      fileC	est le nom du fichier c a fusionner 
 * \param      fileH	est le nom du fichier h a fusionner 
 * \param      fileHtml	est un pointeur sur le fichier HTML qui correspond a la documentation du fichier c et h  
 * \return     Un FILE* qui est un pointeur sur le fichier temporaire résultant de la fusion des deux fichiers c et h.
 */
 FILE* fusionFile(char *fileC, char* fileH, FILE* fileHtml);
 
 #endif
 