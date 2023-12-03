#ifndef FINDPEAKS_H
#define FINDPEAKS_H

#include <stdio.h>
#include <stdlib.h>

#define LENGTHYIN 1024
//#define ALPHA 0.0001  // Constante d'ajustement pour la moyenne mobile exponentielle

void findpeaks(float *Yin, int *iPk);
void getAllPeaks(float *Yin, int *iPk);
void removePeaksBelowMinPeakHeight(float *Yin, int *iPk, float MinPeakHeight);
void removePeaksBelowThreshold(float *Yin, int *iPk, float Threshold);
void findLocalMaxima(float *Yin, int *iPk);
//float calculateInitialThreshold(float *Yin);
//float updateExpMovingAverage(float newValue, float dynamicThreshold);

#endif // FINDPEAKS_H