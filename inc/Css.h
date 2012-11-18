#ifndef CSS_H
#define CSS_H

/**
 * \file      Css.c
 * \author    Fuhs
 * \version   1.0
 * \date      10 Novembre 2012
 * \brief     Ecrit un fichier CSS par défault.
 *
 * On a ici les fonctions permettant d'écrire un fichier de 
 * style CSS prédéfinis pour une page html.
 */
 
   /**
 * \fn         int makeCss(int theme, char* path)
 * \brief      Fonction crée une fichier CSS prédéfinis
 * \param      theme	est le code d'un style prédéfinis .
 * \param      path	est le chemin au répertoire où on veut placer le fichier css	
 * \return     Un int représentant un code de sortie.
 */
 int makeCss(int theme, char* path);
#endif