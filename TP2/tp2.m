clear all;
close all;
img = double(imread('lena_gray.tif')); %chargement de l'image et conversion en double pour traitement ulterieur
figure(1)
imshow(img/255) % division pour avoir des valeurs dans l'intervalle [0,1] pour le bon affichage avec 'imshow'

%================== 1 Histogramme d'une image =============
histo = imhistogramme(img/255,256); % creation de l'histogramme

figure(2)
stem(histo)
title('Histogramme de Lena avec 256 niveaux de gris');

%================== 2 Quantification d'une image ==========
% quantification avec successivement 2, 4, 8, 16, 32, 64, 128 niveaux de gris
% puis affichage des histogrammes correspondant 

figure(3)
for i=1:8
    quantif=2^i;
    subplot(4,4,i)
    imgQuantif=imquantify(img,quantif);
    imshow(imgQuantif);
    title(2^i)
    
    subplot(4,4,i+8)
    histo = imhistogramme(imgQuantif,2^i);
    stem(histo);
    title(2^i)
end



%================= Cameleon =================
[cameleon,map] = imread('cameleon.tif','TIFF'); %recuperation des 3 couleurs r, g, b dans le map
cameleon = ind2rgb(cameleon,map); %fusion des 3 couleurs pour obtenir l'image en couleur
figure(4)
imshow(cameleon)
info = imfinfo('cameleon.tif'); %recupere les metadonnees de l'image
info.Format % renvoi le format de l'image, dans notre cas 'TIF'
cameleongris = rgb2gris(cameleon);  % conversion de l'image en niveaux de gris
imshow(cameleongris);


histo = imhistogramme(cameleongris,256);
figure(5)
stem(histo)
title('Histogramme de l image avec 256 niveaux de gris');

cameleongris = cameleongris.*255; % valeur des pixels entre [0, 255]

%================== quantification et affichage ==========
% quantification avec successivement 2, 4, 8, 16, 32, 64, 128 niveaux de gris
% puis affichage des histogrammes correspondant 

figure(6)
for i=1:8
    quantif=2^i;
    subplot(4,4,i)
    imgQuantif=imquantify(cameleongris,quantif);
    imshow(imgQuantif);
    title(2^i)
    
    subplot(4,4,i+8)
    histo = imhistogramme(imgQuantif,2^i);
    stem(histo);
    title(2^i)
end

% ======== Q3 ========
% Nous pouvons observer qu'a partir du pas de quantification de 8 certains faux contours apparaissent.


% ==== 5. Conclusion ========
% La quantification n'influe pas sur la repartition/demographie des niveaux de gris dans l'image. A partir d'un certain pas de quantification, des faux contours apparaissent creant ainsi de l'information erronees. Cependant, une reduction du nombre de niveaux de gris est un pre-traitement permettant de facilite la detection de contour. De plus, cette reduction permet aussi d'ameliorer l'efficacite de compression, notamment avec l'algorithme de RLE (run-length encoding).



%================== 3 Re-echantillonnage d'une image ======
mire = imread('mire.png'); % chargement de l'image

figure(7)
imshow(imDownSample(mire,2)) %affichage de l'image sous-echantillonnee avec un facteur 2
title('Sous Échantillonnage avec un facteur 2');

%========== Q5 ==============
% Le re-echantillonnage par un facteur 2 fait perdre de l'information et dans le cas present cree de l'informations erronees. Nous obtenons une image dont la forme s'eloigne de celle d'origine


figure(8)
imshow(imDownSample(mire,4)) %affichage de l'image sous-echantillonnee avec un facteur 4
title('Sous Échantillonnage avec un facteur 4');

%========= Q8 ===============
% Le facteur 4 fait perdre encore plus d'information et cree enormement d'informations erronees a tel point que nous perdons totalement la forme d'origine

























