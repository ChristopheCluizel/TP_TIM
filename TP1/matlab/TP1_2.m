clear all;
close all;

%============== 1.3.1 Matlab ====================
%====== Q1 conversion de l'image en double ==========

img=double(imread('lena_color.tif'));	% chargement de l'image avec un cast en "double"


%====== Q2 creation des differentes composantes de l'image =======

palette_gray = zeros(256,3);
for i=1:3
    for j=1:256
    	palette_gray(j,i)=j/256;
    end
end

%creation des palettes de couleur
paletter = zeros(256,3);
paletteg = zeros(256,3);
paletteb = zeros(256,3);
for j=1:256
   paletter(j,1)=j/256;
end
for j=1:256
   paletteg(j,2)=j/256;
end
for j=1:256
   paletteb(j,3)=j/256;
end

% affichage des trois composantes de l'image selon la palette correspondante
figure(1)
imagesc(img(:,:,1))
colormap(paletter)
title('Composante rouge')

figure(2)
imagesc(img(:,:,2))
colormap(paletteg)
title('Composante verte')

figure(3)
imagesc(img(:,:,3))
colormap(paletteb)
title('Composante bleue')


% ========= Q3 conversion de l'image en niveaux de gris ==========

img_gray=zeros(512,512);
img_gray=(img(:,:,1)*0.21+img(:,:,2)*0.72+img(:,:,3)*0.07)/255; % on ajoute les 3 composantes précédentes avec des coefficients multiplicateurs correspondant à des propriétés optique

% affichage de l'image en niveaux de gris
figure(4)
imagesc(img_gray)
colormap(palette_gray)
title('Conversion de l image en niveau de gris')


%========== 1.4.1 Matlab ====================

figure(5)
histogramme=zeros(255,1);
for i=1:256
    histogramme(i,1)=nnz(img_gray==i/255); % la commande "nnz" permet de compter tous les pixels de l'image ayant la valeur demandees (i/255)
end
colormap(palette_gray)
bar(histogramme)
title('Histogramme de l image en niveaux de gris')


