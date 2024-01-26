#ifndef AGC_H
#define AGC_H

#include <stdio.h>

#define TARGET 10000

// Structure pour stocker les paramètres de l'AGC
typedef struct {
    float gain;  // Gain actuel
    float target;  // Niveau cible
    float alpha;  // Coefficient de régulation
} AGC_s;
// Initialiser l'AGC avec les paramètres par défaut
void initAGC(AGC_s *agc, float target, float alpha);
// Mettre à jour le gain en fonction du signal actuel
void updateAGC(AGC_s *agc, float input);
// Appliquer le gain à un signal
float applyGain(AGC_s *agc, float input);

void AGC(float *x, float *y, int size);


#endif // AGC_H
