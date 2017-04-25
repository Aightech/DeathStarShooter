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
  IplImage *edges;
  IplImage *edges_HSV;
  IplImage *edges_threshed;
  IplImage *frame; 
  CvPoint centre;
  CvScalar color;
  color.val[1] = 0;
  color.val[2] = 255;
  color.val[3] = 0;
  cap=cvCreateCameraCapture(0);
  if(!cap)
    {
      printf("Erreur lors de l'ouverture de la caméra");
    }
  else
    {
      cvNamedWindow("Window", CV_WINDOW_AUTOSIZE);
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
	  cvInRangeS(edges_HSV, cvScalar(20,100,100), cvScalar(30,255,255),edges_threshed);
	  cvReleaseImage(&edges_HSV);
	  /*cvCvtColor(frame, edges, CV_RGB2GRAY);
	    cvThreshold(edges, edges, 80, 255,0);
	    cpt = 0;
	    sumx= 0;
	    sumy= 0;
	  cols = edges->width;
	  rows = edges->height;
	  edgesData = edges->imageData;
	  for(i = 0 ; i < rows*cols ; i++)
	    {
	      if(edgesData[i] == 0)
		{
		  sumy += i/cols;
		  sumx += i%cols;
		  cpt++;
		}
	    }
	  centre = cvPoint(sumx/cpt, sumy/cpt);
	  cvCircle(frame, centre, 30, color, -1, 8, 0);*/
	  cvShowImage("Window",frame);
	  cvWaitKey(27);
	}
      
      cvReleaseCapture(&cap);
      cvDestroyWindow("Window");
    }
  return 0;
}
