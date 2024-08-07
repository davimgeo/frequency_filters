#ifndef FREQUENCY_FILTERS_H
#define FREQUENCY_FILTERS_H

#include <vector>
#include "complex_type.h"

std::vector<double> lowPassFilter(int cutoff_freq, int fft_size, double sampling_rate);
void applyLowPassFilter(std::vector<complex>& fft_vec, const std::vector<double>& filter);

#endif