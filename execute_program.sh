#!/bin/bash

compiled_name="generate_wavelet"

echo "Compiling C++ file..."
g++ main.cpp functions/generate_wavelet.cpp functions/fft_algorithms.cpp functions/frequency_filters.cpp -o $compiled_name -lfftw3
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

echo "Executing C++ file..."
./$compiled_name

rm $compiled_name

echo "Executing Python file..."
python3 wavelet_plot.py
if [ $? -ne 0 ]; then
    echo "Python file execution failed."
    exit 1
fi

echo "Cleaning temporary files..."
if [ -f wavelet.txt ]; then
    rm wavelet.txt
fi

if [ -f fft_result.txt ]; then
    rm fft_result.txt
fi

if [ -f filtered_fft_result.txt ]; then
    rm filtered_fft_result.txt
fi

if [ -f ifft_result.txt ]; then
    rm ifft_result.txt
fi

echo "Success."
