#ifndef MBDLIB_H
#define MBDLIB_H

#include "struct.h"
#include <fcntl.h>

void initPantilt(Pantilt *pnt);

/*! \fn void movePantilt(Pantilt *pnt);
    \brief Move the pantilt to the new position.
    \param L The pantilt structure.
*/
int movePantilt(Pantilt *pnt);

#endif
