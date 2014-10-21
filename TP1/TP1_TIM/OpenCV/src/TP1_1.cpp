//
//  main.cpp
//  TIMTD1
//
//  Created by Alexandre Brehmer on 11/09/2014.
//  Copyright (c) 2014 Alexandre Brehmer. All rights reserved.
//

// Example showing how to read and write images
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int valueAt(Mat img,int x,int y) //récupère la valeur du pixel de coordonnées x,y
{

    return ((Scalar)(img.at<uchar>(img.cols-x,img.rows-y))).val[0];
}
void valueSet(Mat img,int x,int y,int value) //assigne la valeur du pixel de coordonnées x,y
{

    img.at<uchar>(img.cols-x,img.rows-y)=value;
}
Mat invertIntensities(Mat inputimage) //inverse les couleurs de l'image
{
    Mat image = inputimage;
    for(int i=0;i<image.cols;i++)
    {
        for(int j=0;j<image.rows;j++)
        {
            valueSet(image,i,j,255-valueAt(image,i,j));
        }
    }
    return image;
}

int main(int argc, char** argv)
{
    
    // Ouverture de l'image
    cv::Mat image;
    image = imread("../ressources/lena_gray.tif", IMREAD_GRAYSCALE);
 if( image.empty())
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }
    //------------------Affichage de l'image
    imshow("Image",image);
    //------------------Valeur du pixel 50,100
    cout << "Pixel(50,100)=" << valueAt(image,100,50) << endl;
    //------------------Quart haut droit de l'image
    Mat imQuart = image(Range(0,image.cols/2),Range(image.rows/2,image.rows)); //extraction du quart haut droit
    imshow("Image quart",imQuart);
    imwrite("lena_gray_quart.tif",imQuart);

    //------------------Dégradé Noir et blanc
    int N=256;
    Mat degrade = Mat::eye(N,N,0);
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            valueSet(degrade,j,i,N-i);
        }
    }

    imshow("Dégradé",degrade);

    Mat imgInvert=invertIntensities(image);
    imshow("Invert",imgInvert);
   
    waitKey(0); // Wait for a keystroke in the window
    return 0;
}