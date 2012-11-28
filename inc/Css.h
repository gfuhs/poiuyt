#ifndef CSS_H
#define CSS_H

#include <stdio.h>

/**
 * \file      Css.c
 * \author    Fuhs
 * \author    Moreau
 * \version   1.0
 * \date      10 Novembre 2012
 * \brief     Ecrit un fichier CSS par défaut.
 *
 * On a ici les fonctions permettant d'écrire un fichier de 
 * style CSS prédéfini pour une page html.
 */
 
/**
 * \fn			void themeCreationD(FILE * fin)
 * \brief		Fonction  créant un fichier.css qui contiendra le thème des pages html
 * \param		fin		est le fichier dans lequel on doit écrire le code css qui sera appliqué aux pages html
 */
 void themeCreationD(FILE * fin);
 
/**
 * \fn			void printReset(FILE * reset)
 * \brief		Fonction créant un fichier de reset pour le css
 * \details		Fonction créant un fichier de reset pour le css afin d'optimiser le nombre de navigateurs prenant en compte notre theme css
 * \param		reset	est le fichier dans lequel on doit écrire le code de reset css
 */
 void printReset(FILE * reset);
 
/**
 * \fn         int makeCss(int theme, char* path)
 * \brief      Fonction créant un fichier CSS prédéfini
 * \param      theme	est le code d'un style prédéfini .
 * \param      path	est le chemin au répertoire où on veut placer les fichiers css	
 * \return     Un int représentant un code de sortie.
 */
 int makeCss(int theme, char* path);
 
#endif
