function [ imagegray ] = rgb2gris( imagergb )
    imagegray=zeros(size(imagergb));

    imagegray=(imagergb(:,:,1)*0.21+imagergb(:,:,2)*0.72+imagergb(:,:,3)*0.07); % superposition des 3 couleurs avec les coefficients optique correspondant pour former l'image en niveau de gris
end

