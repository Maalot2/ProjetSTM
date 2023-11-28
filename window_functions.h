/*
// Created by jackb on 28/11/2023.
*/

#ifndef PROJETSTM_WINDOW_FUNCTIONS_H
#define PROJETSTM_WINDOW_FUNCTIONS_H

#ifndef M_PI
#define M_PI 3.14159265358979323846264338327
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

void cosine_window(double * w, unsigned int n, const double * coeff, unsigned int ncoeff, bool sflag);
void triangular (double *w, unsigned int n);
void triangular_applyWindow(double *input);
}

#endif //PROJETSTM_WINDOW_FUNCTIONS_H*/
