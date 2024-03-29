#ifndef HTML_H
#define HTML_H

#include <stdio.h>
/**
 * \file      Html.c
 * \author    Fuhs
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
 * \brief      Fonction créant  un fichier html 
 * \details		Le fichier crée aura déja la balise en-tête "head" de completer et sa tête de lecture possitionner après la balise ouvrante <body>
 * \param      name	est le nom du fichier html a créer .
 * \return     Un FILE* qui est un pointeur sur le fichier html.
 */
 FILE* newHtml(char *name);
 
 /**
 * \fn         void newBalise(File* file, int code, char* String)
 * \brief      Fonction écrivant une chaine de caractère dans une balise 
 * \param      file	est un FILE* correspondant au fichier html dans lequel on doit mettre la balise .
 * \param      code	est un int correspondant à une balise .
 * \param		String est la chaine de caractère a mettre dans la balise
 */
 void newBalise(FILE* file,int code, char* String);
 
 /**
 * \fn			int closeHtml(FILE* file)
 * \brief		Fonction fermant un fichier crée par la fonction newHtml
 * \param		file est un pointeur sur un fichier crée par la fonction newHtml
 * \return		un int correspondant à un code de sortie
 */
 int closeHtml(FILE* file); 
#endif