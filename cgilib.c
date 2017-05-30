#include <stdio.h>
#include "struct.h"

void laser(IplImage *img, int frameNumber)
{
  int x1, y1, x2, y2;
  CvPoint pt1, pt2;
  CvScalar color = cvScalar(0,0,255,0);

  x1 = frameNumber*32;
  y1 = 480 - (0.4625 * x1 + 120);
  pt1 = cvPoint(x1, y1);
  x2 = x1 + 30;
  y2 = 480 - (0.4625 * x2 + 120);
  pt2 = cvPoint(x2, y2);

  cvLine(img, pt1, pt2, color, 5, 8, 0);

  x1 = 640 - frameNumber*32;
  pt1 = cvPoint(x1, y1);
  x2 = x1 - 30;
  pt2 = cvPoint(x2, y2);

  cvLine(img, pt1, pt2, color, 5, 8 , 0);
}
void release_final(Camera *cam, CGI *afterEffect)
{       
  cvReleaseCapture(&cam->cap);
  cvReleaseImage(&afterEffect->DeathStar);
  cvReleaseImage(&afterEffect->Cockpit);
  cvReleaseImage(&afterEffect->mask_Cockpit);
  cvDestroyWindow("Window");
}
void release_boucle(CGI *afterEffect, Camera *cam)
{
  cvResetImageROI(cam->frame);
  cvShowImage("Window",cam->frame);
  cvReleaseImage(&cam->HSV);
  cvReleaseImage(&cam->threshed);
  cvReleaseImage(&afterEffect->mask_DeathStar);
}
IplImage *resize(IplImage *src, int percentage)
{
  IplImage *dst;
  dst = cvCreateImage(cvSize( (int)( (src->width*percentage)/100 ), (int)( (src->height*percentage)/100 ) ),src->depth,src->nChannels);
  cvResize(src, dst, CV_INTER_AREA);
  return dst;
}
IplImage *init_cockpit()
{
  int i;
  IplImage *Cockpit;
  printf("Quel cockpit voulez vous utiliser ?\n-Le cockpit 1 ? (plutôt stylé)\n-Le cockpit 2 ? (en mode cabriolet)\n-Le cockpit 3 ? (avec aide à la visée pour les noobs)\n...\n...\n...\nAlors... quel cockpit ?\n");
  scanf("%d",&i);
  printf("Cockpit choisi = %d\n\n\n\n", i);
  switch(i)
    {
    case 1:
      Cockpit = cvLoadImage("cockpit1.jpg", CV_LOAD_IMAGE_COLOR);
      break;
    case 2:
      Cockpit = cvLoadImage("cockpit2.jpg", CV_LOAD_IMAGE_COLOR);
      break;
    case 3:
      Cockpit = cvLoadImage("cockpit3.jpg", CV_LOAD_IMAGE_COLOR);
      break;
    }
  if(!Cockpit)
    {
      printf("Erreur lors de l'ouverture du cockpit !! Satané mécano rebelle !\n");
    }
  return Cockpit;
}
void calcul_patate(Patatoide *patate, Camera *cam, float coeff)
{
  int i;
  int cpt = 1;
  int sumx = 0;
  int sumy = 0;
  cam->cols = cam->threshed->width;
  cam->rows = cam->threshed->height;
  for(i = 0 ; i < cam->rows*cam->cols ; i++)
    {
      if(cam->threshed->imageData[i] !=0)
	{
	  sumy += i/cam->cols;
	  sumx += i%cam->cols;
	  cpt++;
	}
    }
  patate->centre = cvPoint(sumx/cpt, sumy/cpt);
  patate->moy += (cpt-patate->moy) * coeff;
  patate->percentage = (int)( ((float)patate->moy/(640.0*480.0))*1200.0 + 2.0);
}  
void init_mask(CGI *afterEffect)
{
  afterEffect->maskLowerBound = cvScalar(0, 125, 0, 0);
  afterEffect->maskHigherBound = cvScalar(130, 255 + 1, 130, 0);
}
void create_mask(CGI *afterEffect, int mode, int w_resized, int h_resized)
{
  if(!mode)
    {
      afterEffect->mask_Cockpit = cvCreateImage(cvSize(afterEffect->Cockpit->width, afterEffect->Cockpit->height), afterEffect->Cockpit->depth, 1);
      cvInRangeS(afterEffect->Cockpit, afterEffect->maskLowerBound, afterEffect->maskHigherBound, afterEffect->mask_Cockpit);
      cvNot(afterEffect->mask_Cockpit, afterEffect->mask_Cockpit);
    }
  if(mode)
    {
      afterEffect->mask_DeathStar = cvCreateImage(cvSize(w_resized,h_resized), afterEffect->DeathStar->depth, 1);
      cvInRangeS(afterEffect->DeathStar_resized, afterEffect->maskLowerBound, afterEffect->maskHigherBound, afterEffect->mask_DeathStar);/* a commenter */
      cvNot(afterEffect->mask_DeathStar,afterEffect->mask_DeathStar);
    }
}
int init_cam(Camera *cam)
{
  cam->lowerBound = cvScalar(109,141,84, 0);
  cam->higherBound = cvScalar(121, 216, 255, 0);
  cam->cap = cvCreateCameraCapture(0);
  if(!cam->cap)
    {
      return 0;
    }
  cam->elem = cvCreateStructuringElementEx(5, 5, 2, 2.5, 2.5, NULL );
  cvNamedWindow("Window", CV_WINDOW_AUTOSIZE);
  return 1;
}
