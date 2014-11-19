#include <iostream>

#include <highgui/highgui.hpp>
#include <imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

/* fonctionne pas
float calculNormeGradient(int x, int y, Mat G_x, Mat G_y)
{
	return sqrt(pow(G_x.at<uchar>(x, y), 2) + pow(G_y.at<uchar>(x, y), 2));
}

double calculGradientDirection(int x, int y, Mat G_x, Mat G_y)
{
	return fastAtan2(G_y.at<uchar>(x,y), G_x.at<uchar>(x,y));
} */

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
	addWeighted(imgFiltreHorizontal, 0.5, imgFiltreVertical, 0.5, 0, imgDest, -1);

	imshow("image avec filtre horizontal", imgFiltreHorizontal);
	imshow("image avec filtre vertical", imgFiltreVertical);

	// float norme = calculNormeGradient(150, 100, imgFiltreHorizontal, imgFiltreVertical);
	// float direction = calculGradientDirection(150,100, imgFiltreHorizontal, imgFiltreVertical);
	// cout<<"norme avec 2 filtres : "<<norme<<endl;
	// // cout<<"norme finalltre final : "<<(int)imgDest.at<uchar>(150,100)<<endl;
	// cout<<"direction : "<<direction<<endl;
	

	return imgDest;
}

Mat MarrHildreth(Mat imgSrc, int N1, float sigma1, int N2, float sigma2)
{
	Mat gausienne1, gaussienne2, dest;
	Size ksize1(N1, N1);
	Size ksize2(N2, N2);

	GaussianBlur(imgSrc, gausienne1, ksize1, sigma1, 0, BORDER_DEFAULT);
	GaussianBlur(imgSrc, gaussienne2, ksize2, sigma2, 0, BORDER_DEFAULT);

	subtract(gausienne1, gaussienne2, dest, noArray(), -1);

	return dest;
}

int main(int argc, char* argv[])
{
	Mat imageCameramanOriginale = imread("image/cameraman.tif", IMREAD_GRAYSCALE);
	Mat imagePapillonOriginale = imread("image/papillon.jpg", IMREAD_GRAYSCALE);
	Mat imageRouteOriginale = imread("image/road1.jpg", IMREAD_GRAYSCALE);
	resize(imageRouteOriginale, imageRouteOriginale, Size(800, 600), 0, 0, INTER_LINEAR);

	Mat imageCameramanSobel;
	Mat imagePapillonSobel;

	Mat imageCameramanPrewitt;
	Mat imagePapillonPrewitt;

	Mat imageCameramanHildreth;

	Mat imageRoutePrewittPuisOtsu;
	Mat imageRouteMarrHildrethPuisOtsu;
	Mat imageRouteCanny;

	/* Application du filtre de Sobel */
	imageCameramanSobel =  appliquerSobel(imageCameramanOriginale);
	imagePapillonSobel = appliquerSobel(imagePapillonOriginale);

	imshow("Cameraman filtre avec Sobel", imageCameramanSobel);
	imshow("Papillon filtre avec Sobel", imagePapillonSobel);
	
	/* Application du filtre de Prewitt */
	imageCameramanPrewitt = appliquerPrewitt(imageCameramanOriginale);
	imagePapillonPrewitt = appliquerPrewitt(imagePapillonOriginale);

	imshow("Cameraman filtre avec Prewitt", imageCameramanPrewitt);
	imshow("Papillon filtre avec Prewitt", imagePapillonPrewitt);
	
	/* Application de l'operateur de Marr et Hildreth */
	imageCameramanHildreth = MarrHildreth(imageCameramanOriginale, 3, 0.6, 3, 0.9);
	imshow("Cameraman filtre MarrHildreth", imageCameramanHildreth);
	
	/* Application du filtre de Prewitt puis seuillage avec Otsu */
	imageRoutePrewittPuisOtsu = appliquerPrewitt(imageRouteOriginale);
	threshold(imageRoutePrewittPuisOtsu, imageRoutePrewittPuisOtsu, 0, 255, THRESH_BINARY | THRESH_OTSU);
	imshow("Extraction de contours avec Prewitt puis Otsu", imageRoutePrewittPuisOtsu);

	/* Application de l'operateur de Marr et Hildreth puis seuillage avec Ostu */
	imageRouteMarrHildrethPuisOtsu = MarrHildreth(imageRouteOriginale, 3, 0.6, 3, 0.8);
	threshold(imageRouteMarrHildrethPuisOtsu, imageRouteMarrHildrethPuisOtsu, 0, 255, THRESH_BINARY | THRESH_OTSU);
	imshow("Extraction de contours avec Marr et Hildreth puis Otsu", imageRouteMarrHildrethPuisOtsu);
	
	/* Application du filtre de Canny */
	 Canny(imageRouteOriginale, imageRouteCanny, 250, 255, 3, false);
	 imshow("Filtre de Canny sur l'image Route", imageRouteCanny);

	waitKey(0);

	return 0;
}
