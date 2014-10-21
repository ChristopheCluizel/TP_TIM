#include <highgui/highgui.hpp>
#include <imgproc/imgproc.hpp>
#include <iostream>

#include "tp4.h"

using namespace cv;
using namespace std;

enum TypeBruit {GAUSSIEN, POIVRE_SEL, UNIFORME};
enum TypeFiltre {FMOYEN, FMEDIAN, FGAUSSIEN};

float moyenneDuFiltre(Mat imageSource, int ordonnee, int abscisse, int tailleFiltre);
Mat generateurDeBruit(Mat imageSource, TypeBruit typeBruit, float quantiteBruit);
Mat filtrage(Mat imageSource, TypeFiltre typeFiltre, int tailleFiltre);

Mat generateurDeBruit(Mat imageSource, TypeBruit typeBruit, float quantiteBruit)
{   
    /* retourne une image bruitee a partir des parametres en entree */

    Mat imgDest = imageSource.clone(); // Mat imgDest(imageSource.rows, imageSource.cols, CV_8U);
    float pixel = 0;
    float bruit = 0;

    switch(typeBruit)
    {
        case GAUSSIEN:
            for(int i = 0; i < imgDest.rows; i++)
            {
                for(int j = 0; j < imgDest.cols; j++)
                {
                    bruit = AWGN_generator(quantiteBruit); // genere un nombre suivant une loi normale de moyenne 0 et d'ecart type 'quantiteBruit'
                    pixel = imageSource.at<uchar>(i, j); // recupere la valeur du pixel de l'image a la position (i,j)

                    if(bruit + pixel > 255) // pour eviter de depasser la valeur max en niveaux de gris d'un pixel
                    {
                        imgDest.at<uchar>(i, j) = 255;
                    }
                    else if(bruit + pixel < 0)
                    {
                        imgDest.at<uchar>(i, j) = 0;
                    }
                    else
                        imgDest.at<uchar>(i, j) = pixel + bruit;    // ajout du bruit gaussien a la valeur du pixel
                }
            }
        break;

        case POIVRE_SEL:
            for(int i = 0; i < imgDest.rows; i++)
            {
                for(int j = 0; j < imgDest.cols; j++)
                {
                    pixel = imgDest.at<uchar>(i, j);
                    bruit = (rand() % 2) * 255; // prend la valeur 0 ou 255 avec une proba de 0.5

                    if(rand() % 101 <= quantiteBruit)
                    {
                            imgDest.at<uchar>(i, j) = bruit;
                    }
                }
            }
        break;

        case UNIFORME:
            for(int i = 0; i < imgDest.rows; i++)
            {
                for(int j = 0; j < imgDest.cols; j++)
                {
                    bruit = rand() % 256;   // genere un nb aleatoire entre 0 et 255
                    pixel = imgDest.at<uchar>(i, j);

                    if(pixel + bruit < 255)
                        imgDest.at<uchar>(i, j) = pixel + bruit;
                }
            }
        break;
    }

    return imgDest;
}

Mat filtrage(Mat imageSource, TypeFiltre typeFiltre, int tailleFiltre)
{
    /* retourne une image filtree a partir du type de filtre et de la taille du filtre en entree */

    Mat imgDest = imageSource.clone();;
    Mat kernel;
    int sigmaFiltreGaussien = 10;

    switch(typeFiltre)
    {
        case FMOYEN :
            kernel = Mat::ones(tailleFiltre, tailleFiltre, CV_32F) / (float)(tailleFiltre * tailleFiltre); // creation du kernel. Matrice avec 1 partout et coeff devant
            filter2D(imageSource, imgDest, -1, kernel, Point(-1,-1), 0, BORDER_DEFAULT); // application du kernel
        break;

        case FMEDIAN :
            medianBlur(imageSource, imgDest, tailleFiltre); // application du filtre directement
        break;

        case FGAUSSIEN :
           GaussianBlur(imageSource, imgDest, Size(tailleFiltre, tailleFiltre), sigmaFiltreGaussien, 0, BORDER_DEFAULT); // application du filtre directement
        break;
    }
    
    return imgDest;
}

float calculerErreurQuadratique(Mat imgSource, Mat imgBruitee)
{
    double norme = 0;

    norme = norm(imgSource, imgBruitee, NORM_L2, noArray());

    return norme / (imgSource.rows * imgSource.cols);
}

int main(int argc, char** argv)
{
    
    Mat imageSource;

    Mat imageBruitGaussien;
    Mat imageBruitPoivreSel;
    Mat imageBruitUniforme;

    Mat imageBruitGaussienFiltreMoyen;
    Mat imageBruitGaussienFiltreMedian;
    Mat imageBruitGaussienFiltreGaussien;

    Mat imageBruitPoivreSelFiltreMoyen;
    Mat imageBruitPoivreSelFiltreMedian;
    Mat imageBruitPoivreSelFiltreGaussien;

    Mat imageBruitUniformeFiltreMoyen;
    Mat imageBruitUniformeFiltreMedian;
    Mat imageBruitUniformeFiltreGaussien;

    int tailleFiltre = 3; // nombre impair obligatoire

    srand (time(NULL));

    imageSource = imread("images/lena_gray.tif", IMREAD_GRAYSCALE);
    if( imageSource.empty())
    {
        cout<<"Impossible d'ouvrir l'image"<<endl ;
        return -1;
    }

    // on genere les images bruitees
    imageBruitGaussien = generateurDeBruit(imageSource, GAUSSIEN, 20);
    imageBruitPoivreSel = generateurDeBruit(imageSource, POIVRE_SEL, 10);
    imageBruitUniforme = generateurDeBruit(imageSource, UNIFORME, 0);

    // filtrage a l'aide d'un filtre moyenneur
    imageBruitGaussienFiltreMoyen = filtrage(imageBruitGaussien, FMOYEN, tailleFiltre);
    imageBruitPoivreSelFiltreMoyen = filtrage(imageBruitPoivreSel, FMOYEN, tailleFiltre);
    imageBruitUniformeFiltreMoyen = filtrage(imageBruitUniforme, FMOYEN, tailleFiltre);

    // filtrage a l'aide d'un filtre median
    imageBruitGaussienFiltreMedian = filtrage(imageBruitGaussien, FMEDIAN, tailleFiltre);
    imageBruitPoivreSelFiltreMedian = filtrage(imageBruitPoivreSel, FMEDIAN, tailleFiltre);
    imageBruitUniformeFiltreMedian = filtrage(imageBruitUniforme, FMEDIAN, tailleFiltre);

    //filtrage a l'aide d'un filtre gaussien
    imageBruitGaussienFiltreGaussien = filtrage(imageBruitGaussien, FGAUSSIEN, tailleFiltre);
    imageBruitPoivreSelFiltreGaussien = filtrage(imageBruitPoivreSel, FGAUSSIEN, tailleFiltre);
    imageBruitUniformeFiltreGaussien = filtrage(imageBruitUniforme, FGAUSSIEN, tailleFiltre);

    // imshow("Image originale", imageSource);

    // ------------- affichage des images bruitees ------------------
    // imshow("Image avec bruit gaussien", imageBruitGaussien);
    // imshow("Image avec bruit poivre & sel", imageBruitPoivreSel);
    // imshow("Image avec bruit uniforme", imageBruitUniforme);

    // ------------- affichage des images filtrees avec un filtre moyenneur -----------------
    // imshow("Image bruit gaussien filtre moyen", imageBruitGaussienFiltreMoyen);
    // imshow("Image bruit poivre et sel filtre moyen", imageBruitPoivreSelFiltreMoyen);
    // imshow("Image bruit uniforme filtre moyen", imageBruitUniformeFiltreMoyen);
    
    // ------------- affichage des images filtrees avec une filtre median ----------------------
    // imshow("Image bruit gaussien filtre median", imageBruitGaussienFiltreMedian);
    // imshow("Image bruit poivre & sel filtre median", imageBruitPoivreSelFiltreMedian);
    // imshow("Image bruit uniforme filtre median", imageBruitUniformeFiltreMedian);
    
    // ------------- affichage des images filtrees avec un filtre gaussien ---------------------------
    // imshow("Image bruit gaussien filtre gaussien", imageBruitGaussienFiltreGaussien);
    // imshow("Image bruit poivre & sel filtre gaussien", imageBruitPoivreSelFiltreGaussien);
    // imshow("Image bruit uniforme filtre gaussien", imageBruitUniformeFiltreGaussien);
    

    float erreurBruitGaussien = calculerErreurQuadratique(imageSource, imageBruitGaussien);
    float erreurBruitGaussienFiltreMoyen = calculerErreurQuadratique(imageSource, imageBruitGaussienFiltreMoyen);
    float erreurBruitGaussienFiltreMedian = calculerErreurQuadratique(imageSource, imageBruitGaussienFiltreMedian);
    float erreurBruitGaussienFiltreGaussien = calculerErreurQuadratique(imageSource, imageBruitGaussienFiltreGaussien);

    float erreurBruitPoivreSel = calculerErreurQuadratique(imageSource, imageBruitPoivreSel);
    float erreurBruitPoivreSelFiltreMoyen = calculerErreurQuadratique(imageSource, imageBruitPoivreSelFiltreMoyen);
    float erreurBruitPoivreSelFiltreMedian = calculerErreurQuadratique(imageSource, imageBruitPoivreSelFiltreMedian);
    float erreurBruitPoivreSelFiltreGaussien = calculerErreurQuadratique(imageSource, imageBruitPoivreSelFiltreGaussien);

    cout<<"Erreur bruit gaussien sans filtre : " << erreurBruitGaussien<<endl;
    cout<<"Erreur bruit gaussien filtre moyen : " << erreurBruitGaussienFiltreMoyen<<endl;
    cout<<"Erreur bruit gaussien filtre median : " << erreurBruitGaussienFiltreMedian<<endl;
    cout<<"Erreur bruit gaussien filtre gaussien : " << erreurBruitGaussienFiltreGaussien<<endl<<endl;

    cout<<"Erreur bruit poivre & sel sans filtre : " << erreurBruitPoivreSel<<endl;
    cout<<"Erreur bruit poivre & sel filtre moyen : " << erreurBruitPoivreSelFiltreMoyen<<endl;
    cout<<"Erreur bruit poivre & sel filtre median : " << erreurBruitPoivreSelFiltreMedian<<endl;
    cout<<"Erreur bruit poivre & sel filtre gaussien : " << erreurBruitPoivreSelFiltreGaussien<<endl<<endl;

   
    waitKey(0); // appui d'une touche pour quitter

    return 0;
}