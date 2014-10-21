clear; close all;

%%======================= Partie 1 visualisation de l'histogramme en niveaux de gris =====
rice = double(imread('images/rice.tif'));
cameraman = double(imread('images/cameraman.tif'));
spine = double(imread('images/spine.tif'));

%%======================= Q2 =============================
histoRice = imhistogramme(rice ./ 255, 256);
histoCameraman = imhistogramme(cameraman ./255, 256);
histoSpine = imhistogramme(spine ./255, 256);

%%==== affichage ======
figure;
subplot(2,3,1)
imshow(rice ./ 255)
title('Rice')

subplot(2,3,2)
imshow(cameraman ./ 255)
title('Cameraman')

subplot(2,3,3)
imshow(spine ./ 255)
title('Spine')

subplot(2,3,4)
stem(histoRice);
title('Histogramme de l image rice');

subplot(2,3,5)
stem(histoCameraman);
title('Histogramme de l image cameraman');

subplot(2,3,6)
stem(histoSpine);
title('Histogramme de l image spine');
% fin affichage


%%======================= Q3 ===========================
% Ces histogrammes ne sont pas egalises. Pour l'image Spine, nous pouvons remarquer qu'il y a une quasi totalite de noir, contrairement a l'image cameraman ou les niveaux de gris sont plus repartis.



%%======================= Partie 2 renforcement de contraste ==============
%%======================= Q1 ===========================
%%==== affichage ======
figure;
subplot(2,3,1)
imshow(rice ./ 255)
title('Rice')

subplot(2,3,2)
imshow(cameraman ./ 255)
title('Cameraman')

subplot(2,3,3)
imshow(spine ./ 255)
title('Spine')

subplot(2,3,4)
image(imBinariser(rice, 110) .* 255);
title('Image rice binarisee');

subplot(2,3,5)
image(imBinariser(cameraman, 80) .* 255);
title('Image cameraman binarisee');

subplot(2,3,6)
image(imBinariser(spine, 25) .* 255);
title('Image spine binarisee');
% fin affichage

%%========= d) ========
% Selon la valeur du seuil, nous pouvons mettre en valeur des elements de l'image. Par exemple sur l'image Rice, nous avons fait ressortir les grains de riz. Cependant, nous devons trouver experimentalement le seuil pour chaque image en fonction des elements que l'on souhaite faire ressortir.


%%======================= Q2 ======================
%%==== affichage ======
figure;
subplot(2,3,1)
imshow(rice ./ 255)
title('Rice')

subplot(2,3,2)
imshow(cameraman ./ 255)
title('Cameraman')

subplot(2,3,3)
imshow(spine ./ 255)
title('Spine')

subplot(2,3,4)
image(imRecDyn(rice, 0, 100));
title('Image rice recadree');

subplot(2,3,5)
image(imRecDyn(cameraman, 0, 100));
title('Image cameraman recadree');

subplot(2,3,6)
image(imRecDyn(spine, 0, 100));
title('Image spine recadree');
% fin affichage

%============ d) ===============
% Pour l'image Rice, nous ne voyons pas l'image. Ceci est du a des valeurs seuil a et b mals adaptees.
% Pour l'image Cameraman, les valeurs sont bien adaptees pour le manteau du cameraman. En effet nous pouvons voir tous les details de son manteau.
% Pour l'image Spine, les valeurs sont globalement adpatees pour faire ressortir la forme de l'element voulu.

%%==== affichage ======
figure;
subplot(2,3,1)
imshow(rice ./ 255)
title('Rice')

subplot(2,3,2)
imshow(cameraman ./ 255)
title('Cameraman')

subplot(2,3,3)
imshow(spine ./ 255)
title('Spine')

subplot(2,3,4)
image(imRecDyn(rice));
title('Image rice recadree');

subplot(2,3,5)
image(imRecDyn(cameraman));
title('Image cameraman recadree');

subplot(2,3,6)
image(imRecDyn(spine));
title('Image spine recadree');
% fin affichage

% ================== g) ========================
% La methode est mal adapte pour l'image Rice, car n'extrayons pas les elements voulus. En revanche, l'extraction par defaut est acceptable, tout depend de ce que l'on souhaite extraire.

%%======================= Q3 ========================
%==== affichage ======
figure;
subplot(3,3,1)
imshow(rice ./ 255)
title('Rice')

subplot(3,3,2)
imshow(cameraman ./ 255)
title('Cameraman')

subplot(3,3,3)
imshow(spine ./ 255)
title('Spine')

subplot(3,3,4)
imagesc(imFenetre(rice, 100, 150, true));
title('Image rice extraction d intensite avec backgound');

subplot(3,3,5)
imagesc(imFenetre(cameraman, 100, 150, true));
title('Image cameraman extraction d intensite avec backgound');

subplot(3,3,6)
imagesc(imFenetre(spine, 100, 150, true));
title('Image spine extraction d intensite avec backgound');

subplot(3,3,7)
imagesc(imFenetre(rice, 100, 150, false));
title('Image rice extraction d intensite sans backgound');

subplot(3,3,8)
imagesc(imFenetre(cameraman, 100, 150, false));
title('Image cameraman extraction d intensite sans backgound');

subplot(3,3,9)
imagesc(imFenetre(spine, 100, 150, false));
title('Image spine extraction d intensite sans backgound');
% fin affichage

%======================= Q4 =========================
%%==== affichage ======
figure;
subplot(1,3,1)
imshow(imNegative(rice) ./ 255)
title('Negatif de Rice')

subplot(1,3,2)
imshow(imNegative(cameraman) ./ 255)
title('Negatif de Cameraman')

subplot(1,3,3)
imshow(imNegative(spine) ./ 255)
title('Negatif de Spine')


%======================= Q5 =========================

figure;
subplot(2,3,1)
imshow(rice./255)
subplot(2,3,2)
histoRiceOriginal = imhistogramme(rice ./ 255, 256);
stem(histoRice);
subplot(2,3,3)
stem(cumsum(histoRiceOriginal));

subplot(2,3,4)
riceDilate = round(imDilCont(rice, 120, 0, 10));
imshow(riceDilate./255)
subplot(2,3,5)
histoRiceDilate = imhistogramme(riceDilate ./ 255, 256);
stem(histoRiceDilate);
subplot(2,3,6)
stem(cumsum(histoRiceDilate));

% %----------------
figure;
subplot(2,3,1)
imshow(cameraman./255)
subplot(2,3,2)
histoCameramanOriginal = imhistogramme(cameraman ./ 255, 256);
stem(histoCameramanOriginal);
subplot(2,3,3)
stem(cumsum(histoCameramanOriginal));

subplot(2,3,4)
cameramanDilate = round(imDilCont(cameraman, 127, 0, 50));
imshow(cameramanDilate./255)
subplot(2,3,5)
histoCameramanDilate = imhistogramme(cameramanDilate ./ 255, 256);
stem(histoCameramanDilate);
subplot(2,3,6)
stem(cumsum(histoCameramanDilate));
%-----------------------
figure;
subplot(2,3,1)
imshow(spine./255)
subplot(2,3,2)
histoSpineOriginal = imhistogramme(spine ./ 255, 256);
stem(histoSpineOriginal);
subplot(2,3,3)
stem(cumsum(histoSpineOriginal));

subplot(2,3,4)
spineDilate = round(imDilCont(spine, 127, 0, 50));
imshow(spineDilate./255)
subplot(2,3,5)
histoSpineDilate = imhistogramme(spineDilate ./ 255, 256);
stem(histoSpineDilate);
subplot(2,3,6)
stem(cumsum(histoSpineDilate));

% La dilatation des zones claires decale les diagrammes cumules vers la gauche. C'est-a-dire augmente le nombre de pixel fonce au detriment des pixels clairs. On augmente egalement les contrastes.

% si 'pd' est superieur a 'a' on dilate les zones sombres et si 'pd' inferieur à 'a', comme ici, on dilate des zones claires.


%======================= Partie 3 egalisation d'histogramme ============
%======== Q2 =============
figure;
subplot(2,3,1)
imshow(rice./255)
title('Rice original');
subplot(2,3,2)
histoRiceOriginal = imhistogramme(rice ./ 255, 256);
stem(histoRiceOriginal);
title('Histogramme du rice original');
subplot(2,3,3)
stem(cumsum(histoRiceOriginal));
title('Histogramme cumule du rice original');

subplot(2,3,4)
riceEgalise = round(imEgaliserHist(rice));
imshow(riceEgalise ./255)
title('Rice egalise');
subplot(2,3,5)
histoRiceEgalise = imhistogramme(riceEgalise ./ 255, 256);
stem(histoRiceEgalise)
title('Histogramme du rice egalise');
subplot(2,3,6)
stem(cumsum(histoRiceEgalise));
title('Histogramme cumule du rice egalise');

%----------------------------------------------------------------------------------------

figure;
subplot(2,3,1)
imshow(cameraman./255)
title('Cameraman original');
subplot(2,3,2)
histoCameramanOriginal = imhistogramme(cameraman ./ 255, 256);
stem(histoCameramanOriginal);
title('Histogramme du cameraman original');
subplot(2,3,3)
stem(cumsum(histoCameramanOriginal));
title('Histogramme cumule du cameraman original');

subplot(2,3,4)
cameramanEgalise = round(imEgaliserHist(cameraman));
imshow(cameramanEgalise ./255)
title('Cameraman egalise');
subplot(2,3,5)
histoCameramanEgalise = imhistogramme(cameramanEgalise ./ 255, 256);
stem(histoCameramanEgalise)
title('Histogramme du cameraman egalise');
subplot(2,3,6)
stem(cumsum(histoCameramanEgalise));
title('Histogramme cumule du cameraman egalise');

%-----------------------------------------------------------------------------------------

figure;
subplot(2,3,1)
imshow(spine./255)
title('Spine original');
subplot(2,3,2)
histoSpineOriginal = imhistogramme(spine ./ 255, 256);
stem(histoSpineOriginal);
title('Histogramme du spine original');
subplot(2,3,3)
stem(cumsum(histoSpineOriginal));
title('Histogramme cumule du spine original');

subplot(2,3,4)
spineEgalise = round(imEgaliserHist(spine));
imshow(spineEgalise ./255)
title('Spine egalise');
subplot(2,3,5)
histoSpineEgalise = imhistogramme(spineEgalise ./ 255, 256);
stem(histoSpineEgalise)
title('Histogramme du spine egalise');
subplot(2,3,6)
stem(cumsum(histoSpineEgalise));
title('Histogramme cumule du spine egalise');

% Les diagrammes cumules sont lineaires, cela atteste du bon fonctionnement de l'egalisation.
% Nous pouvons remarquer sur les diagrammes que les niveaux de gris sont
% mieux repartis. Pour Rice et cameraman, nous perdons en information,
% tandis que nous l'optimisons pour spine.