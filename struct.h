/**
 * \file struct.h
 * \brief Ce fichier regroupe les structures nécessaires à notre jeu.
 * \author Elias H.
 * \version 1.0
 * \date 30 mai 2017
 */
#ifndef STRUCT
#define STRUCT

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <opencv/highgui.h>
#include <opencv/cv.h>

#define winW 700
#define winH 650

#define W 640
#define H 420
using namespace sf;
using namespace std;

/**
 * \struct _GUI
 * \brief Gui est une structure composé de toutes les variable nécéssaire à linterface graphique.
 */
typedef struct _GUI{
       RenderWindow window;/**< The window */
       Texture textureButton,textureStarShip[3],textureImages;/**<  texture of the differents gui objects*/
       Sprite buttons[3];/**< The buttons of the GUI */
       Sprite spritesStarship[3];/**< The buttons of the GUI */
       Sprite cam;
       Font font;/**<  The font used in the gui */
       Text labels[3],labTitle;/**<  The */
       float selected;/**<  */
       int display;/**<  */
       int starship;/**<  */
       unsigned char pixels[W*H*4];/**<  */
       

}GUI;

/**
 * \struct _Pantilt
 * \brief Regroupe les variables liées à la pantilt
 */
typedef struct _Pantilt{
	
  float posM1,posM2; /**< Current positions of the motors. */
  int minM1,maxM1; /**< Maximums positions of the motor 1. */
  int minM2,maxM2; /**< Maximums positions of the motor 1. */
  float ease; /**< Coeficient to filter the position command of the motors. */
       
  int archPro; /**< File descriptor of the embed microcontroller */
  char buffer[64];
  char str[8];
	
	
} Pantilt;
/**
 * \struct Camera
 * \brief Structure contenant les variables liées à la caméra et au traitement des images reçues
 *
 */
typedef struct _Camera{

  IplImage *HSV;/*!< Image reçue passée dans l'espace HSV. */
  IplImage *threshed;/*!< Image reçue binarisée depuis l'espace HSV. */
  IplImage *frame;/*!< Image reçue. */
  CvScalar lowerBound, higherBound;/*!< Bornes de binarisation de l'image HSV. */
  CvCapture *cap;/*!< La caméra d'où on récupère nos images. */
  IplConvKernel *elem;/*!< Element pour l'érosion. */
  int cols, rows;/*!< Nombres de colonnes et de lignes de l'image. */
  int frameNumber;/*!< Donne la frame actuelle pour le déplacement des lasers. */

} Camera;
/**
 * \struct CGI
 * \brief Structure contenant les images et effets à incorporer à l'image reçue.
 *
 */
typedef struct _CGI{
  IplImage *DeathStar; /*!< Image de l'étoile de la mort à sa taille initiale. */
  IplImage *mask_DeathStar;/*!< Mask à appliquer à l'étoile de la mort pour avoir une image sans fond. */
  IplImage *DeathStar_resized;/*!< Image de l'étoile de la mort redimensionnée. */
  IplImage *Cockpit;/*!< Image du cockpit choisi. */
  IplImage *mask_Cockpit;/*!< Mask à appliquer au cockpit pour avoir une image sans fond. */
  CvScalar maskLowerBound, maskHigherBound;/*!< Bornes permettant l'application du mask. */
  IplImage *Explosion;/*!< Image contenant l'explosion à taille initiale. */
  IplImage *Explosion_resized;/*!< Image contenant l'explosion redimensionnée. */
  IplImage *mask_Explosion;/*!< Mask à appliquer à l'explosion pour avoir une image sans fond. */
} CGI;
/**
 * \struct Patatoide
 * \brief Contient les informations relatives au patatoïde détecté
 */
typedef struct _Patatoide{

  CvPoint centre;/*!< Centre du patatoïde. */
  int moy;/*!< "taille" du patatoïde en nombre de pixels, avec une évolution pondérée par un coefficient. */
  int percentage;/*!< Taille du patatoide en pourcentage par rapport à l'image initiale. */

} Patatoide;



#endif
