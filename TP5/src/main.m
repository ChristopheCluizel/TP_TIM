clear; close all;

% ============ 1.2 Application des operateurs de premier ordre =======
T = 0.01;
t1 = -200:T:200;

vecEchelon = atan(t1);

figure;
plot(t1, vecEchelon);
title("image echelon")

t2 = -pi:T:pi;
vecGaussienne = cos(t2);

figure;
plot(t2, vecGaussienne);
title("image gaussienne")

figure;
plot(t1, gradient(vecEchelon))
title("gradient de la fonction echelon")

figure;
plot(t2, gradient(vecGaussienne))
title("gradient de la fonction gaussienne")