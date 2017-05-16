#include <opencv/highgui.h>
#include <opencv/cv.h>
#include <stdio.h>

IplImage *resize(IplImage *src, int percentage)
{
  IplImage *dst;
  dst = cvCreateImage(cvSize( (int)( (src->height*percentage)/100 ), (int)( (src->width*percentage)/100 ) ),src->depth,src->nChannels);
  cvResize(src, dst, CV_INTER_AREA);
  return dst;
}
int main()
{
  int i, cpt, sumx, sumy, cols, rows, h_resized, w_resized, moy;
  char *edgesData;
  CvCapture *cap;
  IplImage *edges_HSV, *edges_threshed, *frame, *DeathStar, *mask, *DeathStar_resized;
  IplConvKernel *elem;
  CvPoint centre;
  CvScalar color1, color2, colorm1,colorm2;
  CvRect ROI;
  int  percentage;
  float coeff;
  colorm1.val[0] = 0;
  colorm1.val[1] = 125;
  colorm1.val[2] = 0;
  colorm2.val[0] = 130;
  colorm2.val[1] = 255+1;
  colorm2.val[2] = 130;
  color1.val[0] = 109;
  color1.val[1] = 141;
  color1.val[2] = 84;
  color2.val[0] = 121;
  color2.val[1] = 216;
  color2.val[2] = 255;
  /*color1.val[0] = 114;
  color1.val[1] = 196;
  color1.val[2] = 84;
  color2.val[0] = 123;
  color2.val[1] = 242;
  color2.val[2] = 252;*/
  moy = 1500;
  coeff = 0.1;
  cap=cvCreateCameraCapture(0);
  if(!cap)
    {
      printf("Erreur lors de l'ouverture de la caméra");
    }
  else
    {
      cvNamedWindow("Window", CV_WINDOW_AUTOSIZE);
      cvNamedWindow("Edges", CV_WINDOW_AUTOSIZE);
      DeathStar = cvLoadImage("death-star-v.jpg", CV_LOAD_IMAGE_COLOR );/*On charge l'image de l'étoile de la mort*/
      if(!DeathStar)
	{
	  printf("Erreur lors de l'ouverture de l'étoile de la mort !! Mais que fait Anakin ??\n");
	}
      while(1)
	{
	  frame = cvQueryFrame(cap);
	  if(!frame)
	    {
	      printf("Erreur lors de l'acquisition de l'image\n");
	      break;
	    }

	  /*On créé nos images que l'on va utiliser*/

	  edges_HSV = cvCreateImage(cvGetSize(frame), 8, 3);
	  edges_threshed = cvCreateImage(cvGetSize(frame), 8, 1);

	  /*On passe de l'espace BGR à l'espace HSV. On stocke l'image dans edges_HSV*/

	  cvCvtColor(frame, edges_HSV, CV_BGR2HSV);

	  /*On binarise l'image edges_HSV en la seuillant avec des bornes basses et hautes (pour garder uniquement le bleu)*/

	  cvInRangeS(edges_HSV, color1, color2,edges_threshed);

	  /*EROSION*/
	  elem = cvCreateStructuringElementEx(5, 5, 2, 2.5, 2.5, NULL );
	  cvErode(edges_threshed, edges_threshed, elem, 1);
	  cpt = 1;
	  sumx= 0;
	  sumy= 0;
	  cols = edges_threshed->width;
	  rows = edges_threshed->height;
	  edgesData = edges_threshed->imageData;
	  for(i = 0 ; i < rows*cols ; i++)
	    {
	      if(edgesData[i] !=0)
		{
		  sumy += i/cols;
		  sumx += i%cols;
		  cpt++;
		}
	    }
	  moy += (cpt-moy)* coeff;  
	  /*Image ROI*/
	  printf("cpt = %d\n",cpt);
	  percentage = (int)( ((float)moy/(640.0*480.0))*1200.0 + 5.0);
	  printf("pourcentage = %d \n",percentage);
	  printf("différence =%d \n", moy);
	  h_resized = (int)( (DeathStar->height*percentage)/100 );
	  w_resized = (int)( (DeathStar->width*percentage)/100 );
	  DeathStar_resized = resize(DeathStar, percentage);

	  /*Création du mask permettant d'enlever le fond de l'étoile de la mort*/
	  mask = cvCreateImage(cvSize(w_resized,h_resized), DeathStar->depth, 1);
	  cvInRangeS(DeathStar_resized, colorm1, colorm2, mask);
	  cvNot(mask,mask);

	  ROI = cvRect((sumx/cpt) - (int)(w_resized/2), (sumy/cpt) - (int)(h_resized/2), w_resized, h_resized);
	  centre = cvPoint(sumx/cpt, sumy/cpt);                     /*Centre du patatoïde*/
	  cvSetImageROI(frame, ROI);                                /*on set le ROI de l'image frame*/
	  /*cvCircle(frame, centre, 15, color, -1, 8, 0);*/
	  if(frame->roi->height == h_resized && frame->roi->width == w_resized)
	    cvCopy(DeathStar_resized, frame, mask);                           /*on copie l'étoile de la mort sur l'image (dans la ROI)*/
	  cvResetImageROI(frame);
	  cvShowImage("Window",frame);
	  cvShowImage("Edges",edges_threshed);
	  cvReleaseImage(&edges_HSV);
	  cvReleaseImage(&edges_threshed);
	  cvReleaseImage(&mask);
	  cvWaitKey(27);
	}
      
      cvReleaseCapture(&cap);
      cvReleaseImage(&DeathStar);
      cvDestroyWindow("Window");
      cvDestroyWindow("Edges");
    }
  return 0;
}
