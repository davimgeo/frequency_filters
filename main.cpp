#include "functions/complex_type.hpp"
#include "functions/generate_wavelet.hpp"
#include "functions/fft_algorithms.hpp"
#include "functions/frequency_filters.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>

auto start = std::chrono::high_resolution_clock::now();

/*
Created 05/08/24 at 2:52 AM

@author: Davi Mendes
*/

template <typename T>
void exportFile(const std::vector<T>& file, const std::string& file_path) 
{
    std::ofstream outfile(file_path);
    if (!outfile.is_open()) {
        throw std::runtime_error("Could not open file. Please Verify the file Path.");
    }
    for (const auto& value : file) {
        outfile << value << "\n";
    }
}

void exportFFTResults(const std::vector<complex>& fft_vector, int size, const std::string& file_path) {
    std::ofstream outfile(file_path);
    if (!outfile.is_open()) {
        throw std::runtime_error("Could not open file. Please Verify the file Path.");
    }
    for (int i = 0; i < size; ++i) {
        outfile << fft_vector[i][REAL] << "," << fft_vector[i][IMAG] << "\n";
    }
}

int main() 
{
    auto start = std::chrono::high_resolution_clock::now();
    
    int Nt = 501;
    double dt = 0.001;
    double fmax = 25.0;
    double cutoff_freq = 50.0;

    std::string path = "/home/davi/Desktop/coding_tests/frequency_filters/";

    std::vector<double> wavelet = generateRickerWavelet(Nt, dt, fmax);
    exportFile(wavelet, path + "wavelet.txt");

    std::vector<complex> fft_result = computeFFT(wavelet);

    exportFFTResults(fft_result, Nt, path + "fft_result.txt");

    int id = 0; // 0 - low pass filter; 1 - high pass filter

    std::vector<double> filter;
    switch(id) 
    {
        case 0:
            filter = lowPassFilter(cutoff_freq, Nt, 1.0 / dt);
            break;
        case 1:
            filter = highPassFilter(cutoff_freq, Nt, 1.0 / dt);
            break;            
    }

    applyLowPassFilter(fft_result, filter);

    exportFFTResults(fft_result, Nt, path + "filtered_fft_result.txt");

    std::vector<complex> ifft_result = computeIFFT(fft_result);
    exportFFTResults(ifft_result, Nt, path + "ifft_result.txt");

    std::vector<double> parameters_vector = {static_cast<double>(Nt), dt, fmax, cutoff_freq};
    exportFile(parameters_vector, path + "parameters_file.txt");

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
 
    std::cout << "Runtime: " << duration.count() / 1e6 << " seconds" << "\n";

    return 0;
}
