#include "fft_algorithms.hpp"
#include "complex_type.hpp"
#include <cmath>
#include <fftw3.h>
#include <vector>

std::vector<double> lowPassFilter(int cutoff_freq, int fft_size, double sampling_rate) 
{
    std::vector<double> filter(fft_size);
    for(int i = 0; i < fft_size; i++) {
        double freq = (i * sampling_rate) / fft_size;
        filter[i] = (std::abs(freq) <= cutoff_freq) ? 1 : 0;
    }
    return filter;
}

std::vector<double> highPassFilter(int cutoff_freq, int fft_size, double sampling_rate) 
{
    std::vector<double> filter(fft_size);
    for(int i = 0; i < fft_size; i++) {
        double freq = (i * sampling_rate) / fft_size;
        filter[i] = (std::abs(freq) >= cutoff_freq) ? 1 : 0;
    }
    return filter;
}

std::vector<double> bandPassFilter(double lowcutoff_freq, double highcutoff_freq, int fft_size, double sampling_rate) 
{
    std::vector<double> filter(fft_size);
    for(int i = 0; i < fft_size; i++) {
        double freq = (i * sampling_rate) / fft_size;
        filter[i] = (std::abs(freq) >= lowcutoff_freq && std::abs(freq) <= highcutoff_freq) ? 1 : 0;
    }
    return filter;
}

std::vector<double> bandStopFilter(double lowcutoff_freq, double highcutoff_freq, int fft_size, double sampling_rate) 
{
    std::vector<double> filter(fft_size);
    for(int i = 0; i < fft_size; i++) {
        double freq = (i * sampling_rate) / fft_size;
        filter[i] = (std::abs(freq) >= lowcutoff_freq && std::abs(freq) <= highcutoff_freq) ? 0 : 1;
    }
    return filter;
}

void applyFilter(std::vector<complex>& fft_vec, const std::vector<double>& filter)
{
    for(int i = 0; i < fft_vec.size(); i++) {
        fft_vec[i][REAL] *= filter[i];
        fft_vec[i][IMAG] *= filter[i];
    }
}
