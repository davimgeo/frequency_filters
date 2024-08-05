#include <iostream>
#include <vector>
#include <fstream>
#include "functions/generate_wavelet.h"

/*
Created 05/08/24 at 2:52 AM

@author: Davi Mendes
*/

template <typename T>
void ExportFile(const std::vector<T>& file, const std::string& file_path) 
{
    std::ofstream outfile(file_path);
    if (!outfile.is_open()) {
        throw std::runtime_error("Could not open file. Please Verify the file Path.");
    }
    for (const auto& value : file) {
        outfile << value << "\n";
    }
}

int main() {
    int Nt = 501;
    double dt = 0.001;
    int fmax = 25;

    std::vector<double> wavelet = generateRickerWavelet(Nt, dt, fmax);

    std::string path = "/home/davi/Desktop/coding_tests/frequency_filters/wavelet.txt";
    ExportFile(wavelet, path);

    return 0;
}