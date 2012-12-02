#ifndef MAKERDOC_H
#define MAKERDOC_H

#include "Ensemble.h" 

/**
 * \file      MakerDoc.c
 * \author    Fuhs
 * \author    Moreau
 * \version   2.0
 * \date      2 Décembre 2012
 * \brief     Définit les fonctions permettant de construire la documentation.
 *
 * Les fonctions présentent ici permettent de créer à partir de
 * fichier un fichier html de la documentations de celui-ci.
 */
 
/**
 * \fn         int makeDoc(Ens* ens)
 * \brief      Fonction crée une documentation html
 * \param      ens	est la structure contenant plusieurs fichiers correspondant à une même documentation html.
 * \return     Un int représentant un code de sortie.
 */
 int makeDoc(Ens* ens);
 #endif