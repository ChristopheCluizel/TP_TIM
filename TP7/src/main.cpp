#include <iostream>

#include <highgui/highgui.hpp>
#include <imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

enum ElementStructurant{RECT, ELLIPSE, CROSS};

int lowerThresholdCanny=0;
int upperThresholdCanny=1000;
int thresholdHough=256;
int rhodHough=0;
int thetaHough=360;
int minDistEntreCentreCerle=256;
int houghCirclesAccumulatorThreshold=0;
int dp=0;
int thresholdHoughCircle=0;

int lowerH=0;
int lowerS=0;
int lowerV=0;

int upperH=180;
int upperS=256;
int upperV=256;

void setwindowSettings()
{
	cvNamedWindow("TrackbarsLine", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("TrackbarsCircle", CV_WINDOW_AUTOSIZE);

	cvCreateTrackbar("lowerThresholdCanny", "TrackbarsLine", &lowerThresholdCanny, 1000, NULL);
	cvCreateTrackbar("upperThresholdCanny", "TrackbarsLine", &upperThresholdCanny, 1000, NULL);
	cvCreateTrackbar("thresholdHough", "TrackbarsLine", &thresholdHough, 256, NULL);
	cvCreateTrackbar("rhodHough", "TrackbarsLine", &rhodHough, 256, NULL);
	cvCreateTrackbar("thetaHough", "TrackbarsLine", &thetaHough, 360, NULL);

	cvCreateTrackbar("minDistEntreCentreCerle", "TrackbarsCircle", &minDistEntreCentreCerle, 256, NULL);
	cvCreateTrackbar("accumulatorThreshold", "TrackbarsCircle", &houghCirclesAccumulatorThreshold, 256, NULL);
	cvCreateTrackbar("dp", "TrackbarsCircle", &dp, 256, NULL);
	cvCreateTrackbar("thresholdHoughCircle", "TrackbarsCircle", &thresholdHoughCircle, 256, NULL);
}

void setwindowColorFilterSettings()
{
	cvNamedWindow("TrackbarsColor", CV_WINDOW_AUTOSIZE);

	cvCreateTrackbar("LowerH", "TrackbarsColor", &lowerH, 180, NULL);
	cvCreateTrackbar("UpperH", "TrackbarsColor", &upperH, 180, NULL);

	cvCreateTrackbar("LowerS", "TrackbarsColor", &lowerS, 256, NULL);
	cvCreateTrackbar("UpperS", "TrackbarsColor", &upperS, 256, NULL);

	cvCreateTrackbar("LowerV", "TrackbarsColor", &lowerV, 256, NULL);
	cvCreateTrackbar("UpperV", "TrackbarsColor", &upperV, 256, NULL);
}

Mat ouvertureImage(Mat image, int taille, ElementStructurant elementStructurant)
{
	Mat dest;
	Mat kernel;

	switch(elementStructurant)
	{
		case RECT:
			kernel = getStructuringElement(MORPH_RECT, Size(taille, taille));
		break;
		case ELLIPSE:
			kernel = getStructuringElement(MORPH_ELLIPSE, Size(taille, taille));
		break;
		case CROSS:
			kernel = getStructuringElement(MORPH_CROSS, Size(taille, taille));
		break;
	}

	morphologyEx(image, dest, MORPH_OPEN, kernel);
	return dest;
}

Mat fermetureImage(Mat image, int taille, ElementStructurant elementStructurant)
{
	Mat dest;
	Mat kernel;

	switch(elementStructurant)
	{
		case RECT:
			kernel = getStructuringElement(MORPH_RECT, Size(taille, taille));
		break;
		case ELLIPSE:
			kernel = getStructuringElement(MORPH_ELLIPSE, Size(taille, taille));
		break;
		case CROSS:
			kernel = getStructuringElement(MORPH_CROSS, Size(taille, taille));
		break;
	}

	morphologyEx(image, dest, MORPH_CLOSE, kernel, Point(-1,-1), 1);
	return dest;
}

//This function threshold the HSV image and create a binary image
Mat getThresholdedImage(Mat imgHSV)
{
	Mat imgThresh;
	inRange(imgHSV, Scalar(lowerH,lowerS,lowerV), Scalar(upperH,upperS,upperV), imgThresh);

	return imgThresh;
}

int main(int argc, char* argv[])
{
	Mat routeOriginale = imread("image/washingtonRoad.png", 1);
	Mat luneOriginale = imread("image/moon.tif", 1);
	Mat luneNetB  = imread("image/moon.tif", 0);
	Mat luneEtCercle;
	Mat luneHSV;
	Mat cercle;
	Mat routeHSV;
	Mat routeColorFiltered;
	Mat routeEtLigne;
	Mat contour;
	Mat ligne, contourEtLignes;
	vector<Vec4i> lines;
	vector<Vec3f> circles;

	setwindowSettings();
	setwindowColorFilterSettings();

	cvtColor(routeOriginale, routeHSV, CV_BGR2HSV); //Change the color format from BGR to HSV

	while(true)
  	{
		routeEtLigne = routeOriginale.clone();
		luneEtCercle = luneOriginale.clone();
		routeColorFiltered = getThresholdedImage(routeHSV);

		Canny(routeColorFiltered, contour, lowerThresholdCanny, upperThresholdCanny);

		cvtColor(contour, contourEtLignes, CV_GRAY2BGR);

	    HoughLinesP(contour, lines, rhodHough+1, CV_PI/(thetaHough+1), thresholdHough+1, 30, 10 );
	    HoughCircles(luneNetB, circles, CV_HOUGH_GRADIENT, dp+1, minDistEntreCentreCerle+1, thresholdHoughCircle+1, houghCirclesAccumulatorThreshold+1);	//86, 17, 0, 49

	    for( size_t i = 0; i < lines.size(); i++ )
	    {
	        line(contourEtLignes, Point(lines[i][0], lines[i][1]),
	            Point(lines[i][2], lines[i][3]), Scalar(0,0,255), 3, 8 );	// dessin des lignes sur l'image des contours
	        line(routeEtLigne, Point(lines[i][0], lines[i][1]),
	            Point(lines[i][2], lines[i][3]), Scalar(0,0,255), 3, 8 );	// dessin des lignes sur l'image originale
	    }

	    for( size_t i = 0; i < circles.size(); i++ )
	    {
	         Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
	         int radius = cvRound(circles[i][2]);
	         // draw the circle center
	         circle(luneEtCercle, center, 3, Scalar(0,255,0), -1, 8, 0 );
	         // draw the circle outline
	         circle(luneEtCercle, center, radius, Scalar(0,0,255), 3, 8, 0 );
	    }

	    imshow("Image filtered by color", routeColorFiltered);
		imshow("Image avec lignes", routeEtLigne);
		imshow("Contours et lignes", contourEtLignes);
		imshow("Lune et cercles", luneEtCercle);

		int c = cvWaitKey(80);
  			if((char)c==27 ) break;	//If 'ESC' is pressed, break the loop
	}

	return 0;
}
