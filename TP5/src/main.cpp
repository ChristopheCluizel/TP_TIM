#include <iostream>

#include <highgui/highgui.hpp>
#include <imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

float calculNormeGradient(Mat G_x, Mat G_y)
{
	
}

Mat appliquerSobel(Mat imgSource)
{
	Mat imgDest;

	Sobel(imgSource, imgDest, imgSource.depth(), 1, 1, 3, 4, 0, BORDER_DEFAULT);

	return imgDest;
}

Mat appliquerPrewitt(Mat imgSource)
{
	Mat imgDest;
	Mat imgFiltreHorizontal;
	Mat imgFiltreVertical;

	float tabG_x[3][3] = {{-1, 0, 1}, {-1, 0, 1}, {-1, 0, 1}};
	float tabG_y[3][3] = {{1, 1, 1}, {0, 0, 0}, {-1, -1, -1}};
	Mat G_x = Mat(3, 3, CV_32F, tabG_x);
	Mat G_y = Mat(3, 3, CV_32F, tabG_y);

	filter2D(imgSource, imgFiltreHorizontal, -1, G_x, Point(-1,-1), 0, BORDER_CONSTANT);
	filter2D(imgSource, imgFiltreVertical, -1, G_y, Point(-1,-1), 0, BORDER_CONSTANT);

	convertScaleAbs(imgFiltreHorizontal, imgFiltreHorizontal, 1, 0);
	convertScaleAbs(imgFiltreVertical, imgFiltreVertical, 1, 0);
	addWeighted(imgFiltreHorizontal, 1, imgFiltreVertical, 1, 0, imgDest, -1);

	return imgDest;
}

int main(int argc, char* argv[])
{
	Mat imageCameramanOriginale = imread("image/cameraman.tif", IMREAD_GRAYSCALE);
	Mat imagePapillonOriginale = imread("image/papillon.jpg", IMREAD_GRAYSCALE);
	Mat imageCameramanSobel;
	Mat imagePapillonSobel;
	Mat imageCameramanPrewitt;
	Mat imagePapillonPrewitt;

	/* Application du filtre de Sobel */
	// imageCameramanSobel =  appliquerSobel(imageCameramanOriginale);
	// imagePapillonSobel = appliquerSobel(imagePapillonOriginale);

	// imshow("Cameraman filtre avec Sobel", imageCameramanSobel);
	// imshow("Papillon filtre avec Sobel", imagePapillonSobel);
	
	/* Application du filtre de Prewitt */
	// imageCameramanPrewitt = appliquerPrewitt(imageCameramanOriginale);
	// imagePapillonPrewitt = appliquerPrewitt(imagePapillonOriginale);

	// imshow("Cameraman filtre avec Prewitt", imageCameramanPrewitt);
	// imshow("Papillon filtre avec Prewitt", imagePapillonPrewitt);

	waitKey(0);

	return 0;
}
