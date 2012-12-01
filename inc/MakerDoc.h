#ifndef MAKERDOC_H
#define MAKERDOC_H

/**
 * \file      MakerDoc.c
 * \author    Fuhs
 * \author    Moreau
 * \version   1.0
 * \date      10 Novembre 2012
 * \brief     Implement the functions needed to build the documentation.
 *
 * Functions which create a documentation of an html file.
 */
 
  /**
 * \fn         int makeDoc(char* file)
 * \brief      Create an html documentation.
 * \param      file	is the name of the file which the program has to create the documentation.
 * \return     An integer which is a special exit code.
 */
 int makeDoc(char* file);
 #endif
