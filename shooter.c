#include <opencv/highgui.h>
#include <opencv/cv.h>
#include <stdio.h>

int main()
{
  int i;
  int cpt;
  int sumx;
  int sumy;
  int cols;
  int rows;
  char *edgesData;
  CvCapture *cap;
  IplImage *edges_HSV;
  IplImage *edges_threshed;
  IplImage *frame; 
  CvPoint centre;
  CvScalar color1, color2, color;
  color.val[0] = 0;
  color.val[1] = 255;
  color.val[2] = 0;
  color1.val[0] = 81;
  color1.val[1] = 119;
  color1.val[2] = 11;
  color2.val[0] = 129;
  color2.val[1] = 234;
  color2.val[2] = 203;
  cap=cvCreateCameraCapture(0);
  if(!cap)
    {
      printf("Erreur lors de l'ouverture de la caméra");
    }
  else
    {
      cvNamedWindow("Window", CV_WINDOW_AUTOSIZE);
      cvNamedWindow("Edges", CV_WINDOW_AUTOSIZE);
      cvNamedWindow("Edges_HSV", CV_WINDOW_AUTOSIZE);
      while(1)
	{
	  frame = cvQueryFrame(cap);
	  if(!frame)
	    {
	      printf("Erreur lors de l'acquisition de l'image");
	      break;
	    }
	  edges_HSV = cvCreateImage(cvGetSize(frame), 8, 3);
	  cvCvtColor(frame, edges_HSV, CV_BGR2HSV);
	  edges_threshed = cvCreateImage(cvGetSize(frame), 8, 1);
	  cvInRangeS(edges_HSV, color1, color2,edges_threshed);
	  /*cvCvtColor(frame, edges, CV_RGB2GRAY);
	    cvThreshold(edges, edges, 80, 255,0);*/
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
	  centre = cvPoint(sumx/cpt, sumy/cpt);
	  cvCircle(frame, centre, 15, color, -1, 8, 0);
	  cvShowImage("Window",frame);
	  cvShowImage("Edges",edges_threshed);
	  cvShowImage("Edges_HSV",edges_HSV);
	  cvReleaseImage(&edges_HSV);
	  cvReleaseImage(&edges_threshed);
	  cvWaitKey(27);
	}
      
      cvReleaseCapture(&cap);
      cvDestroyWindow("Window");
      cvDestroyWindow("Edges");
      cvDestroyWindow("Edges_HSV");
    }
  return 0;
}
