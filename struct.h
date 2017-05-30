/* Ce fichier regroupe les structures nécéssaires à notre jeu */
#ifndef STRUCT
#define STRUCT

#include <opencv/highgui.h>
#include <opencv/cv.h>

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

typedef struct _Camera{

	IplImage *HSV;
	IplImage *threshed;
	IplImage *frame;
	CvScalar lowerBound, higherBound;
	CvCapture *cap;
	IplConvKernel *elem;
	int cols, rows;

} Camera;

typedef struct _CGI{
	
	IplImage *DeathStar; 
	IplImage *mask_DeathStar;
	IplImage *DeathStar_resized;
	IplImage *Cockpit;
	IplImage *mask_Cockpit;
	CvScalar maskLowerBound, maskHigherBound;

} CGI;

typedef struct _Patatoide{

	CvPoint centre;
	int moy;
	int percentage;

} Patatoide;

#endif
