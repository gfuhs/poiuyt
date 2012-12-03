#ifndef CSS_H
#define CSS_H

#include <stdio.h>

/**
 * \file      Css.c
 * \author    Fuhs
 * \author    Moreau
 * \version   2.0
 * \date      2 Décembre 2012
 * \brief     Create a default css file.
 *
 * Functions with which we can create a css file with a css style defined.
 */
 
/**
 * \fn			void themeCreationD(FILE * fin)
 * \brief		Create a css file which will contain the css of the html pages
 * \param		fin		is the file in which we have to write the css style which will be applied to html pages.
 */
 void themeCreationD(FILE * fin);
 
/**
 * \fn			void printReset(FILE * reset)
 * \brief		Function which reset the css style of an html page
 * \details		Function which reset the css style of an html page to improve the number of browsers which can take the css style of the program.
 * \param		reset	est le fichier dans lequel on doit écrire le code de reset css
 */
 void printReset(FILE * reset);
 
/**
 * \fn         int makeCss(int theme, char* path)
 * \brief      Function which create a css style already chosen
 * \param      theme	is a code to choose which style css the program have to applied
 * \param      path		is the path to the directory where the program has to write the css files	
 * \return     Un int représentant un code de sortie.
 */
 int makeCss(int theme, char* path);
 
#endif
