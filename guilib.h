#ifndef GUILIB_H
#define GUILIB_H

/**
 * \file guilib.h
 * \brief Ce fichier contient les prototypes des fonctions liées à l'interface grapphique.
 * \author Alexis Devillard
 * \version 1.0
 * \date 30 mai 2017
 */



#include "struct.h"

/*! \fn void initGUI(GUI *gui);
    \brief initialize the gui.
    \param GUI The gui structure.
*/
void initGUI(GUI *gui);

/*! \fn void createMenu(GUI *gui);
    \brief initialize the gui.
    \param GUI The gui structure.
*/
void createMenu(GUI *gui);

/*! \fn void updateGUI(GUI *gui);;
    \brief initialize the gui.
    \param GUI The gui structure.
*/
void updateGUI(GUI *gui);




#endif
