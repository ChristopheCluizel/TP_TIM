function [ histogramme ] = imhistogramme(image,pasDeQuantification)
pasDeQuantification = pasDeQuantification - 1; % car un pas de quantification de 256 entraine des valeurs de pixels entre [0, 255]
histogramme = zeros(pasDeQuantification,1);

for i=0:pasDeQuantification
    histogramme(i+1)=nnz(image.*pasDeQuantification == i); %compte le nombre d'€™occurrence de la valeur 'i' dans la matrice. La multiplication permet de retrouver des valeurs de pixel entre [0, pasDeQuantification]
end

