#ifndef MAKERDOC_H
#define MAKERDOC_H

/**
 * \file      MakerDoc.c
 * \author    Fuhs
 * \version   1.0
 * \date      10 Novembre 2012
 * \brief     Définit les fonctions permettant de construire la documentation.
 *
 * Les fonctions présentent ici permettent de créer à partir de
 * fichier un fichier html de la documentations de celui-ci.
 */
 
  /**
 * \fn         int makeDoc(char* file)
 * \brief      Fonction crée une documentation html
 * \param      file	est le nom ou l'adresse du fichier dont on veut faire la documentation html.
 * \return     Un int représentant un code de sortie.
 */
 int makeDoc(char* file);
 #endif