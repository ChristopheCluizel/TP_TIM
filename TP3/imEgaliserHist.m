function I = imEgaliserHist(Im)
	[m, n] = size(Im);
	I = zeros(m,n);

	nbOccurence = zeros(1 ,256);
	for i=0:255
		nbOccurence(1, i+1) = nnz(Im == i);
	end
	
	for i=1:m
		for j=1:n
			I(i,j) = ((256 - 1) / (m*n)) * sum(nbOccurence(1:Im(i,j)));
		end
	end
end
