#include <stdio.h>
#include "cgilib.h"
#include "mbdlib.h"


int main()
{
	//cJoystick js; joystick_position jp[2];

	Pantilt pantilt = {80,80,40,140,40,100,0.3};
	initPantilt();

  Camera cam;
  struct _CGI afterEffect;
  Patatoide patate;
  int h_resized, w_resized;
  CvRect ROI;
  int frameNumber = 0;

  init_mask(&afterEffect);
  patate.moy = 1500;
  if(!init_cam(&cam))
    {
      printf("Erreur lors de l'ouverture de la caméra\n");
      return 0;
    }
  else
    {
      afterEffect.DeathStar = cvLoadImage("death-star-v.jpg", CV_LOAD_IMAGE_COLOR );/*On charge l'image de l'étoile de la mort*/
      if(!afterEffect.DeathStar)
	{
	  printf("Erreur lors de l'ouverture de l'étoile de la mort !! Mais que fait Anakin ??\n");
	}
      afterEffect.Cockpit = init_cockpit();/* Initialisations liées à l'image du cockpit */

      /*Création du mask permettant d'enlever le fond du cockpit*/

      create_mask(&afterEffect, 0, 0, 0);

      while(1)
	{
	  frameNumber++;
	  if(frameNumber == 10)
	    frameNumber = 0;
	  cam.frame = cvQueryFrame(cam.cap);
	  if(!cam.frame)
	    {
	      printf("Erreur lors de l'acquisition de l'image\n");
	      break;
	    }

	  /*On créé nos images que l'on va utiliser*/

	  cam.HSV = cvCreateImage(cvGetSize(cam.frame), 8, 3);
	  cam.threshed = cvCreateImage(cvGetSize(cam.frame), 8, 1);

	  /*On passe de l'espace BGR à l'espace HSV. On stocke l'image dans edges_HSV*/

	  cvCvtColor(cam.frame, cam.HSV, CV_BGR2HSV);

	  /*On binarise l'image edges_HSV en la seuillant avec des bornes basses et hautes (pour garder uniquement le bleu)*/

	  cvInRangeS(cam.HSV, cam.lowerBound, cam.higherBound, cam.threshed);

	  /*EROSION*/

	  cvErode(cam.threshed, cam.threshed, cam.elem, 1);

	  /*Calcul du centre de l'image et du nombre moyen de pixels détectés faire focntion qui retourne struc centre*/

	  calcul_patate(&patate, &cam, 0.1);

	  /*Image ROI*/

	  h_resized = (int)( (afterEffect.DeathStar->height*patate.percentage)/100 );
	  w_resized = (int)( (afterEffect.DeathStar->width*patate.percentage)/100 );

	  afterEffect.DeathStar_resized = resize(afterEffect.DeathStar, patate.percentage);

	  /*Création du mask permettant d'enlever le fond de l'étoile de la mort*/

	  create_mask(&afterEffect, 1, w_resized, h_resized);

	  /* ROI ROI ROI */
	  ROI = cvRect(patate.centre.x - (int)(w_resized/2), patate.centre.y - (int)(h_resized/2), w_resized, h_resized);
	  cvSetImageROI(cam.frame, ROI);                                /*on set le ROI de l'image frame*/
	  if(cam.frame->roi->height == h_resized && cam.frame->roi->width == w_resized)
	    cvCopy(afterEffect.DeathStar_resized, cam.frame, afterEffect.mask_DeathStar);/*on copie l'étoile de la mort sur l'image (dans la ROI)*/

	  cvResetImageROI(cam.frame);

	  laser(cam.frame, frameNumber);

	  /* Copie du cockpit sur l'image principale*/
	  ROI = cvRect(0,0,afterEffect.Cockpit->width,afterEffect.Cockpit->height);
	  cvSetImageROI(cam.frame,ROI);
	  if(afterEffect.Cockpit->height == cam.frame->roi->height && afterEffect.Cockpit->width == cam.frame->roi->width)
	    cvCopy(afterEffect.Cockpit, cam.frame, afterEffect.mask_Cockpit);
	  else
	    printf("Erreur pas la même taille sur la copie du cockpit\n");

	  release_boucle(&afterEffect, &cam);
	  if(cvWaitKey(27) != -1)
	    break;
	}
      release_final(&cam, &afterEffect);
    }
  return 0;
}
