#ifndef MAKERDOC_H
#define MAKERDOC_H

#include "Ensemble.h" 

/**
 * \file      MakerDoc.c
 * \author    Fuhs
 * \author    Moreau
 * \version   3.0
 * \date      11 Décembre 2012
 * \brief     Define the functions which create the documentation.
 *
 * Functions which create an html file by the documentation of a file.
 */
 
/**
 * \fn         int makeDoc(Ens* ens)
 * \brief      Function which create an html documentation.
 * \param      ens	is the structure which contains several files which correspond to the same html documentation.
 * \return     An integer which is a special exit code.
 */
 int makeDoc(Ens* ens);
 #endif
