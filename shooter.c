#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <stdio.h>

int main()
{
  CvCapture *cap;
  cap=cvCreateCameraCapture(0);
  if(!cap)
    {
    printf("Erreur lors de l'ouverture de la caméra");
  }
  else
    {
      cvNamedWindow("Window", CV_WINDOW_AUTOSIZE);
      for(;;)
	{
	  IplImage *frame = cvQueryFrame(cap);
	  if(!frame)
	    {
	      printf("Erreur lors de l'acquisition de l'image");
	      break;
	    }
	  cvShowImage("Window",frame);
	  cvWaitKey(27);
	}
      cvCamShift(,"Window",);
      cvReleaseCapture(&cap);
      cvDestroyWindow("Window");
    }
  return 0;
}
