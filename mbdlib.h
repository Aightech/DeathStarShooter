#ifndef MBDLIB
#define MBDLIB

void initPantilt(Pantilt *pnt);


/*! \fn void movePantilt(Pantilt *pnt);
    \brief Move the pantilt to the new position.
    \param L The pantilt structure.
*/
int movePantilt(Pantilt *pnt);

#endif
