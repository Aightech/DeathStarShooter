/**
 * \file cgilib.h
 * \brief Ce fichier contient les prototypes des fonctions du fichier cgilib.c.
 * \author Elias H.
 * \version 1.0
 * \date 30 mai 2017
 */
#ifndef CGI
#define CGI

#include "struct.h"

/**
 * \fn void laser(IplImage *img, int frameNumber)
 * \brief Fonction d'animation des lasers sur l'image.
 *
 * \param img Image sur laquelle on souhaite ajouter les lasers.
 * \param frameNumber Indique à quelle frame de l'image nous sommes pour déterminer à quelle position afficher les lasers.
 * \return void.
 */
void laser(IplImage *img, int frameNumber);
/**
 * \fn void release_final(Camera *cam, struct _CGI *afterEffect)
 * \brief Fonction de libération de la mémoire que l'on a allouée au début du programme (et pas dans la boucle infinie)
 *
 * \param cam Structure contenant des pointeurs sur les mémoires à libérer
 * \param afterEffect idem que cam
 * \return void.
 */
void release_final(Camera *cam, struct _CGI *afterEffect);
/**
 * \fn void release_boucle(struct _CGI *afterEffect, Camera *cam)
 * \brief Fonction de libération de la mémoire que l'on a allouée dans la boucle infinie du programme
 *
 * \param cam Structure contenant des pointeurs sur les mémoires à libérer
 * \param afterEffect idem que cam
 * \return void.
 */
void release_boucle(struct _CGI *afterEffect, Camera *cam);
/**
 * \fn IplImage *resize(IplImage *src, int percentage)
 * \brief Fonction qui redimensionne une image en pourcentage de sa taille initiale.
 *
 * \param src Image que à redimensionner.
 * \param percentage Pourcentage qui donne la taille de l'image finale par rapport à l'image initiale
 * \return IplImage Image redimensionnée en fonction du pourcentage.
 */
IplImage *resize(IplImage *src, int percentage);
/**
 * \fn IplImage *init_cockpit()
 * \brief Fonction qui permet de choisir un cockpit et de lui associée une image allouée en mémoire.
 *
 * \return IplImage pointeur sur l'image du cockpit.
 */
IplImage *init_cockpit();
/**
 * \fn void calcul_patate(Patatoide *patate, Camera *cam, float coeff)
 * \brief Fonction effectuant des calculs amenant à connaître le centre et la taille du patatoïde observé.
 *
 * \param patate Structure contenant les informations sur le patatoïde.
 * \param cam Structure contenant des pointeurs sur les images utilisées dans le programme.
 * \param coeff Valeur choisie à 0.1 ajustant la variation de la taille du patatoïde pour empêcher une évolution trop brusque. 
 * \return void.
 */
void calcul_patate(Patatoide *patate, Camera *cam, float coeff);
/**
 * \fn void init_mask(struct _CGI *afterEffect);
 * \brief Fonction initialisant les valeurs des bornes haute et basse utilisées dans la création du mask.
 *
 * \param afterEffect Structure contenant les variables de bornes haute et basse à modifier.
 * \return void.
 */
void init_mask(struct _CGI *afterEffect);
/**
 * \fn void create_mask(struct _CGI *afterEffect, int mode, int w_resized, int h_resized)
 * \brief Fonction de création du mask.
 *
 * \param afterEffect Structure contenant le mask à créer.
 * \param mode permet de choisir quel mask créer (mode = 0 pour le mask du cockpit et mode = 1 pour le mask de l'étoile de la mort).
 * \param w_resized Seulement pour le mode 1, largeur de l'image à masquer.
 * \param h_resized eulement pour le mode 1, hauteur de l'image à masquer.
 * \return void.
 */
void create_mask(struct _CGI *afterEffect, int mode, int w_resized, int h_resized);
/**
 * \fn int init_cam(Camera *cam)
 * \brief Fonction d'initialisation des différents paramètres liées à la caméra.
 *
 * \param cam Structure contenant les variables et images à initialiser.
 * \return void.
 */
int init_cam(Camera *cam);

#endif
