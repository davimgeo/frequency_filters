#include <iostream>
#include <vector>
#include <cmath>
#include "generate_wavelet.hpp"

std::vector<double> generateRickerWavelet(int Nt, double dt, int fmax) 
{
    std::vector<double> wavelet(Nt);
    double t0 = 2 * M_PI / fmax;

    for (int i = 0; i < Nt; i++) {
        double t = i * dt - t0;
        double arg = M_PI * fmax * t;
        double expression = (1.0 - 2.0 * arg * arg) * exp(-arg * arg);
        wavelet[i] = expression;
    }

    return wavelet;
}

double sinc(double x)
{
    return sin(x) / x; 
}

std::vector<double> generateOrmsbyWavelet(int Nt, double dt, std::vector<double>& freqs)
{
    double t0 = (Nt * dt) / 2.0;
    std::vector<double> wavelet(Nt);
    for (int i = 0; i < Nt; i++) {
        double t = i * dt - t0;
        double arg1 = pow(sinc(M_PI * freqs[3] * t), 2) * pow(M_PI * freqs[3], 2) / (M_PI * freqs[3] - M_PI * freqs[2]);
        double arg2 = pow(sinc(M_PI * freqs[2] * t), 2) * pow(M_PI * freqs[2], 2) / (M_PI * freqs[3] - M_PI * freqs[2]);
        double arg3 = pow(sinc(M_PI * freqs[1] * t), 2) * pow(M_PI * freqs[1], 2) / (M_PI * freqs[1] - M_PI * freqs[0]);
        double arg4 = pow(sinc(M_PI * freqs[0] * t), 2) * pow(M_PI * freqs[0], 2) / (M_PI * freqs[1] - M_PI * freqs[0]);
        wavelet[i] = (arg1 - arg2) - (arg3 - arg4);
    }
    return wavelet;
}
