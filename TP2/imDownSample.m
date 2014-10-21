function [ res ] = imDownSample( image,factor )
    taille = size(image); % recupere la taille de l'image

    res=zeros(taille./factor);
    res = image(1:factor:taille(1),1:factor:taille(2)); % re-echantillonnage en ne prenant que 1 pixel sur 'factor'

end

