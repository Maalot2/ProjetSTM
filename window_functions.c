/*
// Created by jackb on 28/11/2023.
*/


#include "window_functions.h"
#include <complex.h>
#include <math.h>

/*!
 * Defining cosinus window function useful for many other windows.
 * \param[in] w Pointer to the array where the cosine window will be stored
 * \param[in] n Length of the window
 * \param[in] coeff Pointer to the array of coefficients
 * \param[in] ncoeff Number of coefficients in the coeff array
 * \param[in] sflag Boolean flag; if true, the length of the window is n - 1, otherwise, it is n
 *
 * \return nothing
 */
void cosine_window(float * w, unsigned int n, const float * coeff, unsigned int ncoeff, bool sflag){
    if (n == 1){
        // Special case for n == 1.
        w[0] = 1.0;
    }
    else{
        const unsigned wlength = sflag ? (n - 1) : n; //If sflag is true, then the value of wlength is set to (n - 1).If sflag is false, then the value of wlength is set to n

        for (unsigned i = 0; i < n; ++i){
            double wi = 0.0;
            for (unsigned j = 0; j < ncoeff; ++j){
                wi += coeff[j] * cos(i * j * 2.0 * M_PI / wlength);
            }
            w[i] = wi;
        }
    }
}
/*!
 * Defining triangular window function.
 * \param[in] w  This is a pointer to a double array where the calculated triangular window will be stored
 * \param[in] n the length of the triangular window
 *
 * \return nothing
 */

void triangular (float *w, unsigned int n){
    const unsigned denominator =  (n % 2 != 0) ? (n + 1) : n;// The n parameter is used to calculate the denominator based on whether n is odd or even.
    for (unsigned i = 0; i < n; ++i)
    {
        w[i] = 1.0 - fabs(2.0 * i - (n - 1)) / denominator; //fabs absolute value
    }
}
