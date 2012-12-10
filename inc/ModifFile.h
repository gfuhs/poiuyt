#ifndef MODIFFILE_H
#define MODIFFILE_H

#include <stdio.h>

/**
 * \file      MofifFile.c
 * \author    Fuhs
 * \author    Moreau
 * \version   2.0
 * \date      2 Décembre 2012
 * \brief     Functions which manipulate files.
 *
 * Library which contains functions of manipulation of several files.
 */

/**
 * \fn         FILE* fusionFile (char *fileC, char* fileH, FILE* fileHtml)
 * \brief	   Function which merge the comments of files .c and files .h and create the list of the functions in the html file
 * \param      file C	is the name of the file .c to merge
 * \param      fileH	is the name of the file .h to merge
 * \param      fileHtml	is a pointer on the html file which will contain the documentation of both files
 * \return     A pointer on the temporary file which contains the documentation.
 */
 FILE* fusionFile(char *fileC, char* fileH, FILE* fileHtml);
 
 int ordreFile(char* file,char* name);
 
 void copieCom(FILE* fin, FILE* fout, FILE* html);
 
void close_fusion(FILE* file);
 
 #endif
 
