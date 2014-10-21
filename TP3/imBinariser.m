function I = imBinariser(image, seuil)

n = size(image);
I = zeros(n);

I(:,:) = image(:,:) >= seuil; % on fixe la valeur des pixels selon s'ils se trouvent au dessus ou en dessous de la valeur seuil.

end