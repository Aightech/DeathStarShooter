#ifndef MBDLIB_H
#define MBDLIB_H

/**
 * \file mbdlib.h
 * \brief Ce fichier contient les prototypes des fonctions liées à la commande de la pantilt et de la archpro.
 * \author Alexis Devillard
 * \version 1.0
 * \date 30 mai 2017
 */



#include "struct.h"
#include <fcntl.h>

/*! \fn void movePantilt(Pantilt *pnt);
    \brief Initialize the pantilt to the new position.
    \param pnt The pantilt structure.
*/
void initPantilt(Pantilt *pnt);

/*! \fn void movePantilt(Pantilt *pnt);
    \brief Move the pantilt to the new position.
    \param pnt The pantilt structure.
*/
int movePantilt(Pantilt *pnt);

#endif
