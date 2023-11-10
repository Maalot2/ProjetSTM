%  'y' est le signal discret filtré.
y = filtreRIF(80);
Fe = 44100; % Fréquence d'échantillonnage
segment_length = 8192;
overlap = segment_length / 2;
window = triang(segment_length);

% Calcule le nombre total de segments
num_segments = floor((length(y) - overlap) / (segment_length - overlap));

% Initialisez les tableaux pour stocker les résultats
average_magnitude = zeros(1, segment_length);
average_phase = zeros(1, segment_length);

% Divisez le signal en segments, appliquez la fenêtre et calculez la FFT
for i = 1:num_segments
    start_index = (i - 1) * (segment_length - overlap) + 1;
    end_index = start_index + segment_length - 1;
    segment = y(start_index:end_index);
    windowed_segment = segment .* window;
    segment_fft = fft(windowed_segment);
    average_magnitude = average_magnitude + abs(segment_fft);
    average_phase = average_phase + angle(segment_fft);
end
% Moyennez les FFT
average_magnitude = average_magnitude / num_segments;
average_phase = average_phase / num_segments;
% Calculez les fréquences correspondantes à la DFT
frequencies = (0:segment_length - 1) * (Fe / segment_length);
% Définissez les limites pour les fréquences que vous souhaitez afficher
lower_freq_limit = 1; % Hz
upper_freq_limit = 1000; % Hz
% Identifiez les indices des fréquences à afficher
indices_to_display = (frequencies >= lower_freq_limit) & (frequencies <= upper_freq_limit);
% Tracez le module de la moyenne de la DFT en limitant les fréquences
figure;
plot(frequencies(indices_to_display), average_magnitude(indices_to_display),'b');
xlabel('Fréquence (Hz)');
ylabel('Module de la DFT');
title('Moyenne de la Transformée de Fourier Discrète (DFT)');
xlim([lower_freq_limit, upper_freq_limit]); % Limitez l'axe x

% Tracez la phase de la moyenne de la DFT en limitant les fréquences
% figure;
% plot(frequencies(indices_to_display), average_phase(indices_to_display));
% xlabel('Fréquence (Hz)');
% ylabel('Phase de la DFT');
% title('Phase de la Moyenne de la Transformée de Fourier Discrète (DFT)');
% xlim([lower_freq_limit, upper_freq_limit]); % Limitez l'axe x

hold on;

%fenêtre décalé de 2000 echantillons
% Divisez le signal en segments, appliquez la fenêtre et calculez la FFT
for i = 1:num_segments
    start_index = (i - 1) * (segment_length - overlap) + 2001;
    end_index = start_index + segment_length - 1;
    segment = y(start_index:end_index);
    windowed_segment = segment .* window;
    segment_fft = fft(windowed_segment);
    average_magnitude = average_magnitude + abs(segment_fft);
    average_phase = average_phase + angle(segment_fft);
end
% Moyennez les FFT
average_magnitude = average_magnitude / num_segments;
average_phase = average_phase / num_segments;
% Calculez les fréquences correspondantes à la DFT
frequencies = (0:segment_length - 1) * (Fe / segment_length);
% Définissez les limites pour les fréquences que vous souhaitez afficher
lower_freq_limit = 1; % Hz
upper_freq_limit = 1000; % Hz
% Identifiez les indices des fréquences à afficher
indices_to_display = (frequencies >= lower_freq_limit) & (frequencies <= upper_freq_limit);
% Tracez le module de la moyenne de la DFT en limitant les fréquences
plot(frequencies(indices_to_display), average_magnitude(indices_to_display),'r');
xlim([lower_freq_limit, upper_freq_limit]); % Limitez l'axe x
