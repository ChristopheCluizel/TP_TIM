function I = imFenetre(img, a, b, background)
	n = size(img);
	I = zeros(n);
	for i=1:n(1)
		for j=1:n(2)
			if img(i,j) <= a
				I(i,j) = img(i,j) * background;
			elseif img(i,j) >= b
				I(i,j) = img(i,j) * background;
			else
				I(i,j) = 255;
			end
		end
	end
end