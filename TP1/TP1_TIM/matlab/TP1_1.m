clear all
close all

%==== 1.1 Lecture et visualisation ======
% ========== Q1 ==========
img = imread('../ressources/lena_gray.tif'); %ouverture et stockage de l'image dans une variable

% ========== Q2 ==========
figure(1)
imshow(img);

% ========== Q3 ===========
niveau_gris = img(50,100); % img est une matrice de dimension 2 donc on y accède par couple de valeurs

% ========== Q4 ==========
taille = size(img);
imgQuart = img(1: taille /2, taille /2 : taille);

% ========== Q5 ==========
imwrite(imgQuart,'imgQuart.tif','TIFF'); %stockage de l'image au format .tiff


%===== 1.2 La palette de couleurs ===

%======= Q1 =====
% création de la matrice N*N
N = 256;
I = zeros(N,N);
for i=1:N
    for j=1:N
        I(i,j) = j;
    end
end
%========= Q2 & Q3 =========

figure(2)
image(I)

figure(3)
imagesc(I) % commentaire dans le rapport

%========= Q5 & Q6 =========
figure(4);
palette_grey = colormap('gray');
colormap(palette_grey);
imagesc(I);
figure(5);
imshow(palette_grey);	%affiche la palette de niveau de gris

%========= Q7 =============
%creation de la palette de 256 niveaux de gris
N = 256;
palette256_gray = zeros(N, 3);
for i=1:3
    for j=1:N
        palette256_gray(j,i) = j/N;
    end
end

%========= Q8 =========
figure(6)
colormap(palette256_gray)
image(I)

%====== Q9 ==========
% commentaire dans le rapport

%====== Q10 ========
%création de la palette de gris inversée
N = 256;
paletteInversee = zeros(N, 3);
for i=1:3
    for j=1:N
        paletteInversee(j,i) = (N-j)/N;
    end
end

%======= Q11 =======
figure(7)
colormap(paletteInversee)
image(I)

%======= Q12 =====
palette = rand(256,3);
figure(8)
colormap(palette)
image(I)

%======= Q13 =====
% commentaire dans le rapport
