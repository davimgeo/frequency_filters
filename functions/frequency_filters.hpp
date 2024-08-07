#ifndef FREQUENCY_FILTERS_HPP
#define FREQUENCY_FILTERS_HPP

#include <vector>
#include "complex_type.hpp"

std::vector<double> lowPassFilter(int cutoff_freq, int fft_size, double sampling_rate);
std::vector<double> highPassFilter(int cutoff_freq, int fft_size, double sampling_rate);
void applyLowPassFilter(std::vector<complex>& fft_vec, const std::vector<double>& filter);

#endif