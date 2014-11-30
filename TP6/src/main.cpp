#include <iostream>

#include <highgui/highgui.hpp>
#include <imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

enum ElementStructurant{RECT, ELLIPSE, CROSS};

int lowerH=0;
int lowerS=0;
int lowerV=0;

int upperH=180;
int upperS=256;
int upperV=256;


void repondreQuestion1()
{
	Mat I1 = Mat(7, 7, CV_32F, Scalar(1));
	I1.at<uchar>(1,1) = 0;
	I1.at<uchar>(1,2) = 0;
	I1.at<uchar>(1,4) = 0;
	I1.at<uchar>(1,5) = 0;
	I1.at<uchar>(3,1) = 0;
	I1.at<uchar>(3,2) = 0;
	I1.at<uchar>(3,4) = 0;
	I1.at<uchar>(3,5) = 0;
	I1.at<uchar>(6,2) = 0;
	I1.at<uchar>(6,3) = 0;
	uchar tabI1[3][3] = {{0, 1, 0}, {1, 1, 1}, {0, 1, 0}};
	Mat S1 = Mat(3, 3, CV_32F, tabI1);
	Mat I1Dilate;

	dilate(I1, I1Dilate, MORPH_RECT);

    namedWindow("I1", WINDOW_NORMAL);
    imshow("I1", I1);
    namedWindow("I1 dilate", WINDOW_NORMAL);
    imshow("I1 dilate", I1Dilate);

}

Mat creerImageNoireAvecCarreBlanc()
{
	Mat squares(301, 301, CV_8U, Scalar::all(0));
	for(int i = 119; i < 182; i++)
	{
		for(int j = 119; j < 182; j++)
		{
			squares.at<uchar>(i,j) = 255;
		}
	}
	return squares;
}

int getWhitePixels(Mat image)
{
	int compteurPixelBlanc = 0;

	for(int i =0; i < image.rows; i++)
	{
		for(int j = 0; j < image.cols; j++)
		{
			if(image.at<uchar>(i, j) == 255)
				compteurPixelBlanc++;
		}
	}

	return compteurPixelBlanc;
}

Mat eroderImage(Mat image, int taille, ElementStructurant elementStructurant)
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
	
	erode(image, dest, kernel);
	return dest;
}

Mat dilaterImage(Mat image, int taille, ElementStructurant elementStructurant)
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
	
	dilate(image, dest, kernel);
	return dest;
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

Mat topHatImage(Mat image, int taille, ElementStructurant elementStructurant)
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
	
	morphologyEx(image, dest, MORPH_TOPHAT, kernel);
	return dest;
}

Mat bottomHatImage(Mat image, int taille, ElementStructurant elementStructurant)
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
	
	morphologyEx(image, dest, MORPH_BLACKHAT, kernel);
	return dest;
}

void setwindowSettings()
{
	cvNamedWindow("Image originale", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Image binarisee", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Trackbars", CV_WINDOW_AUTOSIZE);

	cvCreateTrackbar("LowerH", "Trackbars", &lowerH, 180, NULL);
	cvCreateTrackbar("UpperH", "Trackbars", &upperH, 180, NULL);

	cvCreateTrackbar("LowerS", "Trackbars", &lowerS, 256, NULL);
	cvCreateTrackbar("UpperS", "Trackbars", &upperS, 256, NULL);

	cvCreateTrackbar("LowerV", "Trackbars", &lowerV, 256, NULL);
	cvCreateTrackbar("UpperV", "Trackbars", &upperV, 256, NULL);
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
	Mat squares;
	Mat squaresErosion3time3;
	Mat squaresErosion15by15;
	int nbPixelsBlanc = 0;

	Mat hawk = imread("image/hawk1.tif", 0);
	//imshow("Hawk original", hawk);
	Mat logoInsa = imread("image/INSA2014.jpg", 0);

	squares = creerImageNoireAvecCarreBlanc();
	// imshow("Squares original", squares);
	// cout<<"Nb pixels blancs squares original : " <<getWhitePixels(squares)<<endl;

	/* ============== Erosion sur carre blanc ============== */
	// squaresErosion3time3 = eroderImage(squares, 3, RECT);
	// imshow("Squares erode 3X3", squaresErosion3time3);
	// cout<<"Nb pixels blancs squares erode 3X3 :" <<getWhitePixels(squaresErosion3time3)<<endl;

	// squaresErosion15by15 = eroderImage(squares, 15, ELLIPSE);
	// imshow("Squares erode 15X15", squaresErosion15by15);
	// cout<<"Nb pixels blancs squares erode 15X15 :" <<getWhitePixels(squaresErosion15by15)<<endl;

	/* ============== Erosion sur hawk ============== */
	// imshow("Hawk erode rect", eroderImage(hawk, 3, RECT));
	// imshow("Hawk erode ellipse", eroderImage(hawk, 3, ELLIPSE));
	// imshow("Hawk erode cross", eroderImage(hawk, 3, CROSS));

	/* ============== dilatation sur hawk ============== */
	// imshow("Hawk dilate rect", dilaterImage(hawk, 3, RECT));
	// imshow("Hawk dilate ellipse", dilaterImage(hawk, 3, ELLIPSE));
	// imshow("Hawk dilate cross", dilaterImage(hawk, 3, CROSS));

	/* ============== Gradient par erosion ============== */
	// Mat hawkGradientErosion;
	// subtract(hawk, eroderImage(hawk,3,RECT), hawkGradientErosion);
	// imshow("Gradient par erosion hawk", hawkGradientErosion);
	
	/* ============== Gradient par dilatation ============== */
	// Mat hawkGradientDilatation;
	// subtract(dilaterImage(hawk,3,RECT), hawk, hawkGradientDilatation);
	// imshow("Gradient par dilatation hawk", hawkGradientDilatation);

	/* ============== Gradient symetrise ============== */
	// Mat hawkGradientSymetrise;
	// subtract(dilaterImage(hawk, 3, RECT), eroderImage(hawk, 3, RECT), hawkGradientSymetrise);
	// imshow("Gradient symetrise hawk", hawkGradientSymetrise);
	// Mat logoInsaGradientSymetrise;
	// subtract(dilaterImage(logoInsa, 3, RECT), eroderImage(logoInsa, 3, RECT), logoInsaGradientSymetrise);
	// imshow("Gradient symetrise logoInsa", logoInsaGradientSymetrise);
	
	/* ============== Ouverture ============== */
	//imshow("logoInsa ouverture", ouvertureImage(logoInsa, 3, RECT));

	/* ============== Fermeture ============== */
	//imshow("logoInsa fermeture", fermetureImage(logoInsa, 3, RECT));
	
	/* ============== Application ============== */
	Mat timber = imread("image/timber1.jpg", 1);
	Mat imgHSV;
	Mat imgThresh;

	setwindowSettings();

	imshow("Image originale", timber);
  	cvtColor(timber, imgHSV, CV_BGR2HSV); //Change the color format from BGR to HSV

  	while(true)
  	{
	  	imgThresh = getThresholdedImage(imgHSV);
	  	imgThresh = fermetureImage(imgThresh, 3, CROSS);
	  	imgThresh = ouvertureImage(imgThresh, 3, CROSS);

	  	subtract(dilaterImage(imgThresh, 3, RECT), eroderImage(imgThresh, 3, RECT), imgThresh);
	  	imshow("Image binarisee", imgThresh);

		int c = cvWaitKey(80);
  		if((char)c==27 ) break;	//If 'ESC' is pressed, break the loop
	}

	return 0;
}