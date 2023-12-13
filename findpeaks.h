#ifndef FINDPEAKS_H
#define FINDPEAKS_H

#include <stdio.h>
#include <stdlib.h>

#define AUDIO_SIZE 2048
#define LENGTHYIN AUDIO_SIZE/2
#define ALPHA 0.0001  // Constante d'ajustement pour la moyenne mobile exponentielle

int findpeaks(float *Yin, int **iPk);
int getAllPeaks(float *Yin, int *iPk);
int removePeaksBelowMinPeakHeight(float *Yin, int *iPk, float MinPeakHeight);
int removePeaksBelowThreshold(float *Yin, int *iPk);
int findLocalMaxima(float *Yin, int *iPk);
float calculateInitialThreshold(float *Yin);
float updateExpMovingAverage(float newValue, float dynamicThreshold);

#endif // FINDPEAKS_H