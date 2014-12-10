#include <iostream>

#include <highgui/highgui.hpp>
#include <imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int lowerThresholdCanny=0;
int upperThresholdCanny=1000;
int thresholdHough=256;
int rhodHough=0;
int thetaHough=360;
int minDistEntreCentreCerle=256;

void setwindowSettings()
{
	cvNamedWindow("Image originale", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Contour", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Trackbars", CV_WINDOW_AUTOSIZE);

	cvCreateTrackbar("lowerThresholdCanny", "Trackbars", &lowerThresholdCanny, 1000, NULL);
	cvCreateTrackbar("upperThresholdCanny", "Trackbars", &upperThresholdCanny, 1000, NULL);
	cvCreateTrackbar("thresholdHough", "Trackbars", &thresholdHough, 256, NULL);
	cvCreateTrackbar("rhodHough", "Trackbars", &rhodHough, 256, NULL);
	cvCreateTrackbar("thetaHough", "Trackbars", &thetaHough, 360, NULL);
	cvCreateTrackbar("minDistEntreCentreCerle", "Trackbars", &minDistEntreCentreCerle, 256, NULL);
}

int main(int argc, char* argv[])
{
	Mat route = imread("image/washingtonRoad.png", 0);
	Mat contour;
	Mat ligne, cdst;
	vector<Vec4i> lines;
	vector<Vec3f> circles;

	setwindowSettings();

	while(true)
  	{
		Canny(route, contour, lowerThresholdCanny, upperThresholdCanny);

		imshow("Image originale", route);

		cvtColor(contour, cdst, CV_GRAY2BGR);

	    HoughLinesP(contour, lines, rhodHough+1, CV_PI/(thetaHough+1), thresholdHough+1, 30, 10 );
	    // HoughCircles(contour, circles, CV_HOUGH_GRADIENT, 1, minDistEntreCentreCerle+1);

	    for( size_t i = 0; i < lines.size(); i++ )
	    {
	        line(cdst, Point(lines[i][0], lines[i][1]),
	            Point(lines[i][2], lines[i][3]), Scalar(0,0,255), 3, 8 );
	    }

	    // for( size_t i = 0; i < circles.size(); i++ )
	    // {
	    //      Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
	    //      int radius = cvRound(circles[i][2]);
	    //      // draw the circle center
	    //      circle(cdst, center, 3, Scalar(0,255,0), -1, 8, 0 );
	    //      // draw the circle outline
	    //      circle(cdst, center, radius, Scalar(0,0,255), 3, 8, 0 );
	    // }

		imshow("Contour", cdst);

		int c = cvWaitKey(80);
  			if((char)c==27 ) break;	//If 'ESC' is pressed, break the loop
	}

	return 0;
}
