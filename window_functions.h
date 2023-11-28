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

void cosine_window(double * w, unsigned n, const double * coeff, unsigned ncoeff, bool sflag);

}

#endif //PROJETSTM_WINDOW_FUNCTIONS_H*/
