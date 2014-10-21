function I = imDilCont(Im, a, pc, pd)
	[m, n] = size(Im);
	for i =1:m
		for j=1:n
			if(Im(i, j) < a)
				I(i, j) = pd / a * Im(i, j);
			else
				I(i, j) = ((255-pd)*Im(i,j) + 255*(pd-a)) / (255-a);
			end
		end
	end
end