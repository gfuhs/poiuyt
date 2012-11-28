#ifndef HTML_H
#define HTML_H

#include <stdio.h>
/**
 * \file      Html.c
 * \author    Fuhs
 * \author    Moreau
 * \version   1.0
 * \date      10 Novembre 2012
 * \brief     Ecrit un fichier html .
 *
 * On a ici les fonctions permettant d'écrire un fichier  
 * html utilisant un fichier CSS construit avec les fonctions
 * contenu dans Css.h.
*/
 
/**
 * \fn         FILE* newHtml(char* name)
 * \brief      Fonction créant un fichier html 
 * \details    Le fichier créé aura déja la balise en-tête "head" de complété et sa tête de lecture possitionnée après la balise ouvrante <body>
 * \param      name	est le nom du fichier html à créer .
 * \return     Un FILE* qui est un pointeur sur le fichier html.
*/
 FILE* newHtml(char *name);
 
/**
 * \fn         void newBalise(File* file, int code, char* String)
 * \brief      Fonction écrivant une chaine de caractères dans une balise 
 * \param      file	est un FILE* correspondant au fichier html dans lequel on doit mettre la balise .
 * \param      code	est un int correspondant à une balise .
 * \param		String est la chaine de caractère a mettre dans la balise
*/
 void newBalise(FILE* file, int code, char* String);
 
/**
 * \fn		int closeHtml(FILE* file)
 * \brief	Fonction fermant un fichier créé par la fonction newHtml
 * \param	file est un pointeur sur un fichier créé par la fonction newHtml
 * \return	un int correspondant à un code de sortie
*/
 int closeHtml(FILE* file); 

/**
 * \fn		void putTab (FILE * file, int nb)
 * \brief 	Fonction mettant un nombre de tabulations pour indenter le fichier html
 * \param	file est un pointeur sur un fichier créé par la fonction newHtml
 * \param	nb est le nombre de tabulations à insérer dans le fichier pour indenter proprement le code html
*/
 void putTab (FILE * file, int nb);
 
/**
 * \fn 		void putSpace (FILE * file, int nb)
 * \brief	Fonction mettant un nombre d'espaces contribuant au css
 * \param	file est un pointeur sur un fichier créé par la fonction newHtml
 * \param	nb est le nombre d'espaces à insérer dans le fichier pour clarifier la page html
*/

#endif
