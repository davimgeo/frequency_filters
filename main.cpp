#include "functions/complex_type.hpp"
#include "functions/generate_wavelet.hpp"
#include "functions/fft_algorithms.hpp"
#include "functions/frequency_filters.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>

enum waveletType
{
    RICKER_WAVELET,
    ORMSBY_WAVELET
};

enum filterType 
{
    LOW_PASS,
    HIGH_PASS,
    BAND_PASS,
    BAND_STOP
};

template <typename T>
void exportFile(const std::vector<T>& file, const std::string& file_path) 
{
    std::ofstream outfile(file_path);
    if (!outfile.is_open()) {
        throw std::runtime_error("Could not open file. Please verify the file path.");
    }
    for (const auto& value : file) {
        outfile << value << "\n";
    }
}

void exportFFTResults(const std::vector<complex>& fft_vector, const std::string& file_path) {
    std::ofstream outfile(file_path);
    if (!outfile.is_open()) {
        throw std::runtime_error("Could not open file. Please verify the file path.");
    }
    for (const auto& value : fft_vector) {
        outfile << value[REAL] << "," << value[IMAG] << "\n";
    }
}

int main() 
{
    auto start = std::chrono::high_resolution_clock::now();
    
    int Nt = 501;
    double dt = 0.001;
    double fmax = 25.0;
    std::vector<double> ormsby_freqs = {5.0, 10.0, 40.0, 45.0};
    double sampling_rate = 1.0 / dt;
    double cutoff_freq = 25.0;
    double lowcutoff_freq = 10.0;
    double highcutoff_freq = 30.0;

    std::string path = "/home/davi/Desktop/coding_tests/frequency_filters/";

    waveletType waveletType = ORMSBY_WAVELET;

    std::vector<double> wavelet;
    switch(waveletType)
    {
    case RICKER_WAVELET:
        wavelet = generateRickerWavelet(Nt, dt, fmax);
        break;
    case ORMSBY_WAVELET:
        wavelet = generateOrmsbyWavelet(Nt, dt, ormsby_freqs);
        break;
    }

    exportFile(wavelet, path + "wavelet.txt");

    std::vector<complex> fft_result = computeFFT(wavelet);
    exportFFTResults(fft_result, path + "fft_result.txt");

    filterType filterType = BAND_STOP;

    std::vector<double> filter;
    switch(filterType) 
    {
        case LOW_PASS:
            filter = lowPassFilter(cutoff_freq, Nt, sampling_rate);
            break;
        case HIGH_PASS:
            filter = highPassFilter(cutoff_freq, Nt, sampling_rate);
            break;
        case BAND_PASS:
            filter = bandPassFilter(lowcutoff_freq, highcutoff_freq, Nt, sampling_rate);
        case BAND_STOP:
            filter = bandStopFilter(lowcutoff_freq, highcutoff_freq, Nt, sampling_rate);
    }

    applyFilter(fft_result, filter);

    exportFFTResults(fft_result, path + "filtered_fft_result.txt");

    std::vector<complex> ifft_result = computeIFFT(fft_result);
    exportFFTResults(ifft_result, path + "ifft_result.txt");

    std::vector<double> parameters_vector = {static_cast<double>(Nt), dt, fmax, cutoff_freq, lowcutoff_freq, highcutoff_freq, static_cast<double>(filterType)};
    exportFile(parameters_vector, path + "parameters_file.txt");

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "Runtime: " << duration.count() / 1e6 << " seconds\n";

    return 0;
}

