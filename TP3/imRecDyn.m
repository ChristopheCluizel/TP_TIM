function I = imRecDyn(img, a, b)
n = size(img);
I = zeros(n);

if nargin < 1	% pour verifier q'une image est bien passee en parametre
	error ('image missing');
end
if nargin < 2 	% pour verifier que a est bien passe en parametre
	a = min(min(img));
end
if nargin < 3 % pour verifier que b est bien passe en parametre
	b = max(max(img));
end

for i=1:n(1)	% parcours de l'image
	for j=1:n(2)
		if img(i,j) <= a
			I(i,j) = 0;
		elseif img(i,j) >= b
			I(i,j) = 255;
		else
			I(i,j) = 255 * (img(i,j) - a) / (b - a); % linearisation entre a et b
		end
	end
end

end