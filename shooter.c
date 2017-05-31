#include <stdio.h>
#include "cgilib.h"
#include "mbdlib.h"

int main()
{
  /*cJoystick js; joystick_position jp[2];

    Pantilt pantilt = {80,80,40,140,40,100,0.3};
    initPantilt();*/

  Camera cam;
  struct _CGI afterEffect;
  Patatoide patate;
  cam.frameNumber = 0;

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
      afterEffect.Explosion = cvLoadImage("explosion.jpg", CV_LOAD_IMAGE_COLOR); /* On charge l'image de l'étoile de la mort */

      /*Création du mask permettant d'enlever le fond du cockpit*/

      create_mask(&afterEffect, 0, 0, 0);

      while(1)
	{
	  cam.frameNumber++;
	  if(cam.frameNumber == 10)
	    cam.frameNumber = 0;
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

	  insert_image(&afterEffect, &cam, &patate, 1);/* On insère l'étoile de la mort */
	  insert_image(&afterEffect, &cam, &patate, 2);/* On insère l'explosion */
	  insert_image(&afterEffect, &cam, &patate, 0);/* On insère le cockpit */

	  laser(cam.frame, cam.frameNumber);

	  release_boucle(&afterEffect, &cam);
	  if(cvWaitKey(27) != -1)
	    break;
	}
      release_final(&cam, &afterEffect);
    }
  return 0;
}
