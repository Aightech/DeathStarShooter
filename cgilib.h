/* Ce fichier regroupe les fonctions d'effets spéciaux nécéssaires à notre jeu */
#ifndef CGI
#define CGI

#include "struct.h"

void laser(IplImage *img, int frameNumber);
void release_final(Camera *cam, struct _CGI *afterEffect);
void release_boucle(struct _CGI *afterEffect, Camera *cam);
IplImage *resize(IplImage *src, int percentage);
IplImage *init_cockpit();
void calcul_patate(Patatoide *patate, Camera *cam, float coeff);
void init_mask(struct _CGI *afterEffect);
void create_mask(struct _CGI *afterEffect, int mode, int w_resized, int h_resized);
int init_cam(Camera *cam);

#endif
