#include "opencv2/opencv.hpp"

using namespace cv;

int main(int, char**)
{
  VideoCapture cap(0); // open the default camera
  if(!cap.isOpened())  // check if we succeeded
    return -1;

  Mat edges;
  namedWindow("edges",1);
  for(;;)
    {
      Mat frame;
      cap >> frame; // get a new frame from camera
      cvtColor(frame, edges, CV_BGR2GRAY);
      threshold(edges, edges, 80, 255,THRESH_BINARY);
      int sumx=0;
      int sumy=0;
      int cpt =0;
      int cols = edges.cols, rows = edges.rows;
      if(edges.isContinuous())
	{
	  cols *= rows;
	  rows = 1;
	}
      for(int i = 0; i < rows; i++)
	{
	  const uchar* Mi = edges.ptr<uchar>(i);
	  for(int j = 0; j < cols; j++)
	    if(Mi[j] == 0)
	      {
		sumx += i;
		sumy += j;
		cpt++;
	      }
	}
      Point2i centre(sumx/cpt, sumy/cpt);
      circle(edges, centre, 30, Scalar(0,255,0), -1, 8, 0);
      imshow("edges", edges);
      if(waitKey(30) >= 0) break;
    }
  // the camera will be deinitialized automatically in VideoCapture destructor
  return 0;
}
