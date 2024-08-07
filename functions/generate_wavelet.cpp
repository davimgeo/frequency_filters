#include <iostream>
#include <vector>
#include <cmath>
#include "generate_wavelet.hpp"

std::vector<double> generateRickerWavelet(int Nt, double dt, int fmax) 
{
    std::vector<double> wavelet(Nt);
    double t0 = 2 * M_PI / fmax;

    for (int i = 0; i < Nt; ++i) 
    {
        double t = i * dt - t0;
        double arg = M_PI * fmax * t;
        double expression = (1.0 - 2.0 * arg * arg) * exp(-arg * arg);
        wavelet[i] = expression;
    }

    return wavelet;
}
