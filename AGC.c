#include "agc.h"

// Initialiser l'AGC avec les paramètres par défaut
void initAGC(AGC_s *agc, float target, float alpha) {
    agc->gain = 1.0f;
    agc->target = target;
    agc->alpha = alpha;
}

// Mettre à jour le gain en fonction du signal actuel
void updateAGC(AGC_s *agc, float input) {
    // Calculer l'erreur
    float error = agc->target - input;

    // Mettre à jour le gain en fonction de l'erreur
    agc->gain += agc->alpha * error;

    // Limiter le gain pour éviter des valeurs excessives
    if (agc->gain < 0.1f) {
        agc->gain = 0.1f;
    } else if (agc->gain > 10.0f) {
        agc->gain = 10.0f;
    }
}

// Appliquer le gain à un signal
float applyGain(AGC_s *agc, float input) {
    return agc->gain * input;
}

void AGC(float *x, float *y, int size)
{
    int i=0;
    AGC_s agc;

    // Initialiser l'AGC avec une valeur cible de 1.0 et un coefficient alpha de 0.01
    initAGC(&agc, target, 0.01f);

    for(i=0; i < size; i++)
    {
        // Mettre à jour l'AGC avec un signal factice (peut être remplacé par une entrée réelle)
        updateAGC(&agc, x[i]);

        // Appliquer le gain au signal d'entrée
        y[i] = applyGain(&agc, x[i]);
    }
}