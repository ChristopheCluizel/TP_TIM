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

Mat getColorChannel(Mat* image, int noChannel)//recupère le canal couleur d'une image
{
    vector<Mat> rgb;
    vector<Mat> channels;
    Mat output;
    Mat g = Mat::zeros(Size(image->rows, image->cols), CV_8UC1);
    split(*image,rgb);
    for(int i=0;i<3;i++)
    {
        if(i==noChannel)
            channels.push_back(rgb.at(i));
        else
            channels.push_back(g);
    }

    merge(channels, output);
    return output;
}

void valueSet(Mat img,int x,int y,int value)
{

    img.at<uchar>(x,y)=value;
}

int valueAt(Mat img,int x,int y)
{

    return ((Scalar)(img.at<uchar>(img.cols-x,img.rows-y))).val[0];
}

//La méthode n'étant pas sur moodle, nous avons tenté de la réaliser nous meme. 
/*Mat createHistogramme(Mat *img) //Fortement inspiré de la documentation officiel d'OpenCv
{
    Mat hsv=*img;
    //cvtColor(*img, hsv, CV_BGR2HSV);

    // Quantize the hue to 30 levels
    // and the saturation to 32 levels
    int hbins = 30, sbins = 32;
    int histSize[] = {hbins, sbins};
    // hue varies from 0 to 179, see cvtColor
    float hranges[] = { 0, 180 };
    // saturation varies from 0 (black-gray-white) to
    // 255 (pure spectrum color)
    float sranges[] = { 0, 256 };
    const float* ranges[] = { hranges, sranges };
    MatND hist;
    // we compute the histogram from the 0-th and 1-st channels
    int channels[] = {0};

    calcHist( &hsv, 1, channels, Mat(), // do not use mask
             hist, 2, histSize, ranges,
             true, // the histogram is uniform
             false );
    double maxVal=0;
    minMaxLoc(hist, 0, &maxVal, 0, 0);

    int scale = 10;
    Mat histImg = Mat::zeros(sbins*scale, hbins*10, CV_8UC3);

    for( int h = 0; h < hbins; h++ )
        for( int s = 0; s < sbins; s++ )
        {
            float binVal = hist.at<float>(h, s);
            int intensity = cvRound(binVal*255/maxVal);
            rectangle( histImg, Point(h*scale, s*scale),
                        Point( (h+1)*scale - 1, (s+1)*scale - 1),
                        Scalar::all(intensity),
                        CV_FILLED );
        }
        return histImg;
}*/

int main(int argc, char** argv)
{
    
    Mat img, g, fin_img;
    img = imread("../../ressources/lena_color.tif",CV_LOAD_IMAGE_COLOR);
    
    //=============================1.3.2=============================
    //Découpage des cannaux de l'image
    vector<Mat> rgb;
    split(img,rgb);
    Mat blue = rgb.at(0);
    Mat green = rgb.at(1);
    Mat red = rgb.at(2);
    vector<Mat> channels;
    //Création d'une matrice vide
    g = Mat::zeros(Size(red.rows, red.cols), CV_8UC1);
    //Assemblage d'une image avec seulement une couche bleue
    channels.push_back(blue);
    channels.push_back(g);
    channels.push_back(g);
    merge(channels, blue);

    //Assemblage d'une image avec seulement une couche verte
    channels.clear();
    channels.push_back(g);
    channels.push_back(green);
    channels.push_back(g);
    merge(channels, green);

    //Assemblage d'une image avec seulement une couche rouge
    channels.clear();
    channels.push_back(g);
    channels.push_back(g);
    channels.push_back(red);
    merge(channels, red);

    //Affichage des couleurs
    imshow("blue", blue);
    imshow("green", green);
    imshow("red", red);

    //Utilisation de la méthode getColorChannel()
    imshow("getColorChannel",getColorChannel(&img,1));

    //================================1.4.2============================
    Mat imggray = imread("../../ressources/lena_gray.tif",CV_LOAD_IMAGE_GRAYSCALE);
    imshow("lena gray",imggray);
    int histogramme[256][1];// = Mat::zeros(Size(256, 1), CV_32FC1);
    for(int i=0;i<256;i++)
    {
        histogramme[i][0]=0;
    }
    //Comptage du nombre d'occurence de chaques couleurs
    for(int i=0;i<imggray.rows;i++)
    {
        for(int j=0;j<imggray.cols;j++)
        {
            int tmp = valueAt(imggray,i,j);
            histogramme[tmp][0]++;
        }
    }
    int max=0;
    //determination de la valeur maximal. nous la divisons par 10 pour l'affichage
    for(int i=0;i<256;i++)
    {

        if (histogramme[i][0]/10>max)
            max=histogramme[i][0]/10;
    }
    cout <<"Valeur 200:" << histogramme[200][0] << endl;
    
    Mat histo = Mat::zeros(Size(256, max), CV_8UC1);
    //Création de l'image de l'histogramme
    for(int i=0;i<256;i++)
    {
        for(int j=0;j<histogramme[i][0]/10;j++)
        {
            valueSet(histo,max-j,i,255);       
        }
    }

    imshow("histo",histo);
    //La méthode évoquée dans le sujet n'étant pas sur moodle, cette partie n'a pu aboutir.
    //imshow("OpenCVHisto",createHistogramme(&imggray));



    waitKey(0);
    return 0;
}