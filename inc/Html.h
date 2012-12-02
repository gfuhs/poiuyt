#ifndef HTML_H
#define HTML_H

#include <stdio.h>

extern int Fonc_num;

/**
 * \file      Html.c
 * \author    Fuhs
 * \author    Moreau
 * \version   2.0
 * \date      2 Décembre 2012
 * \brief     Create an html file.
 *
 * Functions with which the program can create an html file using a css file built with the functions wrote in Css.c
*/
 
/**
 * \fn         FILE* newHtml(char* name)
 * \brief      Function which create an html file 
 * \details	   The created file will already have the "head" completed and his CUR will be after the opening tag <body>
 * \param      name 	is the html filename.
 * \return     A FILE* which is a pointer on the created file.
*/
 FILE* newHtml(char *name);
 
/**
 * \fn         void newBalise(File* file, int code, char* String)
 * \brief      Function which write a String in a tag
 * \param      file 	is a FILE * on the html file in which the program has to write the tag.
 * \param      code is an integer which correspond to a tag.
 * \param		String is the string to put in the tag
*/
 void newBalise(FILE* file, int code, char* String);
 
/**
 * \fn		int closeHtml(FILE* file)
 * \brief	Close a file created by the newHtml function
 * \param	file	is a pointer on a file created by the newHtml function
 * \return	an integer which corresponds to a special exit code
*/
 int closeHtml(FILE* file); 

/**
 * \fn		void putTab (FILE * file, int nb)
 * \brief 	Put a special number of tabulations to indent the html file
 * \param	file	is a pointer on an html file created by the newHtml function
 * \param	nb	is the number of tabluations to insert
*/
 void putTab (FILE * file, int nb);
 
/**
 * \fn 		void putSpace (FILE * file, int nb)
 * \brief	Insert some spaces in the html file to improve the look of the html page
 * \param	file	is a pointer on an html file created by the newHtml function
 * \param	nb	is the number of spaces to insert
*/
 void putSpace (FILE * file, int nb);

#endif
