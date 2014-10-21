#include <highgui.h>
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

    Mat imgDest(imageSource.rows, imageSource.cols, CV_8U);

    switch(typeFiltre)
    {
        case FMOYEN :
            for(int i = 0; i < imageSource.rows; i++)
            {
                for(int j = 0; j < imageSource.cols; j++)
                {
                    imgDest.at<uchar>(i,j) = moyenneDuFiltre(imageSource, i, j, tailleFiltre);
                }
            }
        break;
    }
    
    return imgDest;
}

float moyenneDuFiltre(Mat imageSource, int ordonnee, int abscisse, int tailleFiltre)
{
    /* retourne la moyenne des pixels appartenant a la fenetre du filtre centre sur le pixel (ordonnee, abscisse) */

    int somme = 0;
    int compteurPixel = 0;

    int ordonneeDepart = ordonnee - (tailleFiltre-1) / 2;
    int ordonneeArrivee = ordonnee + (tailleFiltre-1) / 2;
    int abscisseDepart = abscisse - (tailleFiltre-1) / 2;
    int abscisseArrivee = abscisse + (tailleFiltre-1) / 2;

    for(int i = ordonneeDepart; i < ordonneeArrivee; i++)
    {
        if(0 <= i && i < imageSource.rows)
        {
            for(int j = abscisseDepart; j < abscisseArrivee; j++)
            {
                if( 0 <= j && j < imageSource.cols)
                {
                    somme += imageSource.at<uchar>(i, j);
                    compteurPixel++;
                }
            }
        }
    }

    return somme / compteurPixel;
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

    int tailleFiltreGaussien = 3;

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
    imageBruitGaussienFiltreMoyen = filtrage(imageBruitGaussien, FMOYEN, tailleFiltreGaussien);
    imageBruitPoivreSelFiltreMoyen = filtrage(imageBruitPoivreSel, FMOYEN, tailleFiltreGaussien);
    imageBruitUniformeFiltreMoyen = filtrage(imageBruitUniforme, FMOYEN, tailleFiltreGaussien);

    imshow("Image originale", imageSource);

    // affichage des images bruitees
    imshow("Image avec bruit gaussien", imageBruitGaussien);
    imshow("Image avec bruit poivre & sel", imageBruitPoivreSel);
    imshow("Image avec bruit uniforme", imageBruitUniforme);

    // affichage des images filtrees avec un filtre moyenneur
    imshow("Image bruit gaussien filtre moyen", imageBruitGaussienFiltreMoyen);
    imshow("Image bruit poivre et sel filtre moyen", imageBruitPoivreSelFiltreMoyen);
    imshow("Image bruit uniforme filtre moyen", imageBruitUniformeFiltreMoyen);
   
    waitKey(0); // appui d'une touche pour quitter

    return 0;
}