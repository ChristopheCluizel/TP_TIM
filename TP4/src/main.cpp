#include <highgui/highgui.hpp>
#include <imgproc/imgproc.hpp>
#include <iostream>

#include "tp4.h"

using namespace cv;
using namespace std;

enum TypeBruit {GAUSSIEN, POIVRE_SEL, UNIFORME};
enum TypeFiltre {FMOYEN, FMEDIAN, FGAUSSIEN};

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

    return (norme / (imgSource.rows * imgSource.cols)) * 100;
}

void repondreQuestion12345(Mat imageSource)
{
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
}

void repondreQuestion6()
{
    Mat imageBase = Mat::ones(6, 6, CV_32F);
    float matTemp1[3][3] = {{0, 1, 0}, {1, 1, 1}, {0, 1, 0}};
    float matTemp2[3][4] = {{0, 1, 1, 0}, {1, 1, 1, 1}, {0, 1, 1, 0}};
    float matTemp3[4][4] = {{0, 1, 1, 0}, {1, 1, 1, 1}, {1, 1, 1, 1}, {0, 1, 1, 0}};
    Mat H1 = Mat(3, 3, CV_32F, matTemp1) / 9;
    Mat H2 = Mat(3, 4, CV_32F, matTemp2) / 12;
    Mat H3 = Mat(4, 4, CV_32F, matTemp3) / 16;

    Mat resultatH1;
    Mat resultatH2;
    Mat resultatH3;

    filter2D(imageBase, resultatH1, -1, H1, Point(-1,-1), 0, BORDER_CONSTANT);
    filter2D(imageBase, resultatH2, -1, H2, Point(-1,-1), 0, BORDER_CONSTANT);
    filter2D(imageBase, resultatH3, -1, H3, Point(-1,-1), 0, BORDER_CONSTANT);

    namedWindow("Image originale", WINDOW_NORMAL);
    imshow("Image originale", imageBase);

    namedWindow("H1 originale", WINDOW_NORMAL);
    imshow("H1 originale", H1);
    namedWindow("H2 originale", WINDOW_NORMAL);
    imshow("H2 originale", H2);
    namedWindow("H3 originale", WINDOW_NORMAL);
    imshow("H3 originale", H3);

    namedWindow("Image filtre H1", WINDOW_NORMAL);
    imshow("Image filtre H1", resultatH1);
    namedWindow("Image filtre H2", WINDOW_NORMAL);
    imshow("Image filtre H2", resultatH2);
    namedWindow("Image filtre H3", WINDOW_NORMAL);
    imshow("Image filtre H3", resultatH3);

}

int separationHisto3_1(Mat imgSource)
{
    Mat hist(1, 256, CV_32F);
    int vbin = 256; // car 256 classes
    int histSize[] = {vbin};
    float vranges[] = {0, 255}; // intervalle que peuvent prendre les valeurs
    const float * ranges[] = {vranges};
    int channels[] = {0};

    calcHist(&imgSource, 1, channels, Mat(), hist, 1, histSize, ranges, true, false);
    int compteurPixel = 0;
    int nbPixelImage = imgSource.cols * imgSource.rows;
    int seuil = 0;
    // cout<<hist<<endl;
    // cout<<"taille tabHist : "<<hist.size()<<endl;
    while(compteurPixel < nbPixelImage / 2) // seuil atteint lorsque le diagramme cumule atteint la moitie du nb de pixel total
    {
        compteurPixel += hist.at<float>(seuil);
        seuil++;
    }
    cout<<"Nombre de pixel lorsque le seuil est atteint : "<<compteurPixel<<endl;

    // pour verifier que l'histogramme est bon en retrouvant le nombre total de pixel
    // int temp = 0;
    // for(int j = 0; j < 256; j++)
    // {
    //     temp += hist.at<float>(j);
    //     // cout<<temp<<endl;
    // }

    cout<<"nombre pixel total de l'image : "<<nbPixelImage<<endl;

    return seuil;
}

float calculProportionRelative(Mat histNormalise, int seuil)
{
    float proportion = 0;

    for(int i = 0; i < seuil; i++)
    {
        proportion += histNormalise.at<float>(i);
    }

    return proportion;
}

float calculMu(Mat histNormalise, int borneInf, int borneSup, float q)
{
    float somme = 0;

    for(int i = borneInf; i <= borneSup; i++)
    {
        somme += i * histNormalise.at<float>(i);
    }
    if(q == 0)
        return 10^10;
    else
        return somme / q;
}

float calculSigmaCarre(Mat histNormalise, int borneInf, int borneSup, float q, float mu)
{
    float somme = 0;

    for(int i = borneInf; i <= borneSup; i++)
    {
        somme += ((i - mu)*(i-mu)) * histNormalise.at<float>(i);
    }
    if(q == 0)
        return 10^10;
    else
        return somme / q;
}

int minimumTab(float tab[])
{
    int indexMini = 0;

    for(int i = 0; i < 256; i++)
    {
        if(tab[i] < tab[indexMini])
            indexMini = i;
    }
 
    return indexMini;
}

int separationHisto3_3(Mat imgSource)
{

    Mat hist(1, 256, CV_32F);
    Mat histNormalise(1, 256, CV_32F);

    int vbin = 256;
    int histSize[] = {vbin};
    float vranges[] = {0, 255};
    const float * ranges[] = {vranges};
    int channels[] = {0};
    int nbPixelTotal = imgSource.rows * imgSource.cols;
    int seuil = 0;
    float tabVarianceIntraClasse[256];
    float q1 = 0, q2 = 0, mu1 = 0, mu2 = 0, sigma1carre = 0, sigma2carre = 0;

    calcHist(&imgSource, 1, channels, Mat(), hist, 1, histSize, ranges, true, false);
    histNormalise = hist / nbPixelTotal;
    // cout<<histNormalise<<endl;
    for(int i = 0; i < 256; i++)
    {
        q1 = calculProportionRelative(histNormalise, i);
        q2 = 1 - q1;
        mu1 = calculMu(histNormalise, 0, i, q1);
        mu2 = calculMu(histNormalise, i + 1, 255, q2);
        sigma1carre = calculSigmaCarre(histNormalise, 0, i, q1, mu1);
        sigma2carre = calculSigmaCarre(histNormalise, i + 1, 255, q2, mu2);
        tabVarianceIntraClasse[i] = q1 * sigma1carre + q2 * sigma2carre;

        cout<<"i : "<<i<<" | q1 : "<<q1<<" | q2 : "<<q2<<" | mu1 : "<<mu1<<" | mu2 : "<<mu2<<" | sigma1Carre : "<<sigma1carre<<" | sigma2Carre : "<<sigma2carre<<" | varianceIntraClasse : "<<tabVarianceIntraClasse[i]<<endl;
    }

    seuil = minimumTab(tabVarianceIntraClasse);

    return seuil;
}

int main(int argc, char** argv)
{   
    Mat imageSource;
    Mat imageBinariseeSeuilPremiereApproche;
    Mat imageBinariseeSeuilOtsu;
    Mat imageBinariseeSeuilOtsuReel;
    int seuilPremiereApproche = 0;
    int seuilOtsu = 0;


    srand (time(NULL));

    // imageSource = imread("images/lena_gray.tif", IMREAD_GRAYSCALE);
    imageSource = imread("images/pomme.jpg", IMREAD_GRAYSCALE);
    if( imageSource.empty())
    {
        cout<<"Impossible d'ouvrir l'image"<<endl ;
        return -1;
    }

    // repondreQuestion12345(imageSource);
    // repondreQuestion6();
    
    /* ------------------- Binarisation -------------------- */

    // seuilPremiereApproche = separationHisto3_1(imageSource);
    // cout<<"Seuil premiere approche : "<<seuilPremiereApproche<<endl;

    // threshold(imageSource, imageBinariseeSeuilPremiereApproche, seuilPremiereApproche, 255, THRESH_BINARY);
    // imshow("Image binarisee seuil premiere approche", imageBinariseeSeuilPremiereApproche);

    seuilOtsu = separationHisto3_3(imageSource);
    cout<<"Seuil avec methode Otsu : "<<seuilOtsu<<endl;

    threshold(imageSource, imageBinariseeSeuilOtsu, seuilOtsu, 255, THRESH_BINARY);
    imshow("Image binarisee seuil methode Otsu a la main", imageBinariseeSeuilOtsu);

    threshold(imageSource, imageBinariseeSeuilOtsuReel, 0, 255, THRESH_BINARY | THRESH_OTSU);
    imshow("Image binarisee seuil methode Otsu d'OpenCv", imageBinariseeSeuilOtsuReel);
    
    waitKey(0); // appui d'une touche pour quitter

    return 0;
}