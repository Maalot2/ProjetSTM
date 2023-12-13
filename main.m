%  'y' est le signal discret filtré.
%y = filtreRIF(80);
[x, F1] = audioread('frelon3.WAV');
Fe = 8192; % Fréquence d'échantillonnage
x_resampled = resample(x, Fe, F1);  % conversion en 8kHz
segment_length = 2048;
y=x_resampled(:, 1);    % on garde que 1 canal
overlap = segment_length / 2;
window = triang(segment_length);

% Calcule le nombre total de segments
num_segments = floor((length(y) - overlap) / (segment_length - overlap));

% Initialisation des tableaux pour stocker les résultats
average_magnitude = zeros(1, segment_length);
average_phase = zeros(1, segment_length);

% Diviser le signal en segments, appliquer la fenêtre et calculer la FFT
for i = 1:num_segments
    start_index = (i - 1) * (segment_length - overlap) + 1;
    end_index = start_index + segment_length - 1;
    segment = y(start_index:end_index);
    windowed_segment = segment .* window;
    segment_fft = fft(windowed_segment);
    average_magnitude = average_magnitude + abs(segment_fft);
    average_phase = average_phase + angle(segment_fft);
end
% Moyenner les FFT
average_magnitude = average_magnitude / num_segments;
average_phase = average_phase / num_segments;
% Calculer les fréquences correspondantes à la DFT
frequencies = (0:segment_length - 1) * (Fe / segment_length);
% Définisser les limites pour les fréquences que vous souhaitez afficher
lower_freq_limit = 1; % Hz
upper_freq_limit = 1000; % Hz
% Identifier les indices des fréquences à afficher
indices_to_display = (frequencies >= lower_freq_limit) & (frequencies <= upper_freq_limit);
% Tracer le module de la moyenne de la DFT en limitant les fréquences
figure;
plot(frequencies(indices_to_display), average_magnitude(indices_to_display),'b');
xlabel('Fréquence (Hz)');
ylabel('Module de la DFT');
title('Moyenne de la Transformée de Fourier Discrète (DFT)');
xlim([lower_freq_limit, upper_freq_limit]); % Limitez l'axe x

% Tracer la phase de la moyenne de la DFT en limitant les fréquences
% figure;
% plot(frequencies(indices_to_display), average_phase(indices_to_display));
% xlabel('Fréquence (Hz)');
% ylabel('Phase de la DFT');
% title('Phase de la Moyenne de la Transformée de Fourier Discrète (DFT)');
% xlim([lower_freq_limit, upper_freq_limit]); % Limitez l'axe x

hold on;

%fenêtre décalé de 2000 echantillons
% Diviser le signal en segments, appliquer la fenêtre et calculer la FFT
for i = 1:num_segments
    start_index = (i - 1) * (segment_length - overlap) + 1;
    end_index = start_index + segment_length - 1;
    segment = y(start_index:end_index);
    windowed_segment = segment .* window;
    segment_fft = fft(windowed_segment);
    average_magnitude = average_magnitude + abs(segment_fft);
    average_phase = average_phase + angle(segment_fft);
end
% Moyenner les FFT
average_magnitude = average_magnitude / num_segments;
average_phase = average_phase / num_segments;
% Calculer les fréquences correspondantes à la DFT
frequencies = (0:segment_length - 1) * (Fe / segment_length);
% Limites pour les fréquences que nous souhaitons afficher
lower_freq_limit = 1; % Hz
upper_freq_limit = 1000; % Hz
% Identifier les indices des fréquences à afficher
indices_to_display = (frequencies >= lower_freq_limit) & (frequencies <= upper_freq_limit);
% Tracer le module de la moyenne de la DFT en limitant les fréquences
plot(frequencies(indices_to_display), average_magnitude(indices_to_display),'r');
xlim([lower_freq_limit, upper_freq_limit]); % Limitez l'axe x



% Récupération amplitude max
magnitude_max = max(average_magnitude(:));
seuil = 0.05;

% Utiliser la fonction findpeaks pour détecter les pics basés sur la hauteur
[peaks, peak_indices] = findpeaks(average_magnitude(indices_to_display), 'MinPeakProminence', seuil * magnitude_max);

% Sélectionner les pics dont la fréquence est supérieure à 200 Hz
selected_peaks = peaks(frequencies(peak_indices+1) > 200);
selected_peak_indices = peak_indices(frequencies(peak_indices+1) > 200);

% Afficher les résultats finaux
disp('Fréquences des pics :');
disp(frequencies(selected_peak_indices+1));
disp('Amplitudes des pics :');
disp(selected_peaks);

% Tracer les pics détectés
hold on;
scatter(frequencies(selected_peak_indices+1), selected_peaks, 'r', 'filled');
xlabel('Fréquence (Hz)');
ylabel('Module de la DFT');
title('Spectre avec détection automatique des pics');


