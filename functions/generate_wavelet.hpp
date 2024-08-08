#ifndef GENERATE_WAVELET_HPP
#define GENERATE_WAVELET_HPP

#include <iostream>
#include <vector>

std::vector<double> generateRickerWavelet(int Nt, double dt, int fmax);
std::vector<double> generateOrmsbyWavelet(int Nt, double dt, std::vector<double>& freqs);

#endif