function y= filtreRIF(N)
Fe=44100 ; % Fréquence d'échantillonnage
Te=1/Fe ; % Période d'échantillonnage
Fc=5000; % Fréquence de coupure
Fa=6600 ; % Fréquence atténuée
Amax=0.7079; % Amax=3dB
Amin=0.01; % Amin=40dB
%----------- Définition du gabarit du filtre (filtre désiré)------------
BT=Fa-Fc ; % Largeur de la bande transition
a=(Amin-Amax)/BT ; % Pente dans la bande de transition
F=[0 (1-Amax)/a+Fc Fc Fa Fc-Amax/a Fe/2]/(Fe/2) ;
M=[1 1 Amax Amin 0 0];
fd=(Fe/2)*[-F(length(F):-1:2) F] ; % Réponse fréquentielle
% du filtre désiré
Hd=[M(length(M):-1:2) M]; % sur –Fe/2 à Fe/2
%------------------------ Synthèse du filtre ---------------------------
Fenetre=ones(1,N) ; % Fenêtre de pondération (rectangulaire)
% entre –Fe/2 à Fe/2.
h=fir2(N-1,F,M,Fenetre); % Synthèse du filtre : génération des
% coefficients de la réponse impulsionnelle
f = -Fe/2:Fe/2 ; % Définition de la variable fréquence
% entre –Fe/2 à Fe/2.
H = freqz(h,[1],f,Fe) ; % Fonction de transfert du filtre synthétisé
P = unwrap(angle(H)) ; % Déroulement de la phase du filtre
%--------------- Calcul du temps de propagation de groupe --------------
 [a n1]=min(abs(f+Fc/2)) ; % Détermination du retard de la réponse :
[a n2]=min(abs(f-Fc/2)) ; % en supposant une phase linéaire dans
DP = P(n2)-P(n1) ; % la bande passante, ce retard est donnée
Df = f(n2)-f(n1) ; % par la relation (V.49)
Retard=DP/Df/(-2*pi)
%%subplot(211),plot(fd,Hd,'k-.',f,abs(H),'k')
%%axis([min(f) max(f) -0.1 1.1])
%%subplot(212),plot(f,P) 
%%figure
%%subplot(211),plot(h,'ko'), hold on, stem(h,'k.')
%%axis([0 N+1 min(h)-0.1 max(h)+0.1])
%---------------------- Synthèse du signal test ------------------------
%%figure
[x, F1] = audioread('frelon_court.wav');
t= 0:Te:(length(x)-1)*Te ; % définition de la variable temps : période
% d'échantillonnage Te
%F1=10 ; % Fréquence F1
%F2=800; % Fréquence F2
%xF1=sin(2*pi*F1*t) ; % Génération d'une sinusoïde de fréquence F1
%x=xF1+0.5*sin(2*pi*F2*t) ; % Génération du signal test qui est la
% somme de deux sinusoïdes de fréquences
% F1 et F2


%-------------------------------Filtrage--------------------------------
y=filter(h,[1],x(:, 1)) ; % Filtrage
%%subplot(211),plot(t,x(:, 1),'b'), % Tracé du signal test
%%axis([min(t) max(t) -2 2])
%%subplot(212),plot(t,y,'k'), % Tracé de la réponse du filtre
% superposée à la sinusoïde de
% fréquence F1.
%%axis([min(t) max(t) -2 2]) 
