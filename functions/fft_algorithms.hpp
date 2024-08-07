#ifndef FFT_ALGORITHMS_HPP
#define FFT_ALGORITHMS_HPP

#define REAL 0
#define IMAG 1

#include <vector>
#include "complex_type.hpp"

std::vector<complex> computeFFT(const std::vector<double>& wavelet);
std::vector<complex> computeIFFT(const std::vector<complex>& fft_vec);

#endif


