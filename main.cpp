#include <iostream>
#include <vector>
#include <fstream>
#include "functions/complex_type.h"
#include "functions/generate_wavelet.h"
#include "functions/fft_algorithms.h"

#define REAL 0
#define IMAG 1

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
    int Nt = 501;
    double dt = 0.001;
    int fmax = 25;

    std::string path = "/home/davi/Desktop/coding_tests/frequency_filters/";

    std::vector<double> wavelet = generateRickerWavelet(Nt, dt, fmax);
    exportFile(wavelet, path + "wavelet.txt");

    std::vector<complex> fft_result = computeFFT(wavelet);
    exportFFTResults(fft_result, Nt, path + "fft_result.txt");

    return 0;
}
