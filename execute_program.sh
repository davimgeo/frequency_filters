#!/bin/bash

compiled_name="filtered_wavelet"
functions=(functions/generate_wavelet.cpp functions/fft_algorithms.cpp functions/frequency_filters.cpp)
temp_files=(wavelet.txt fft_result.txt filtered_fft_result.txt ifft_result.txt parameters_file.txt)

echo "Compiling C++ file..."
g++ main.cpp "${functions[@]}" -o $compiled_name -lfftw3
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

echo "Executing C++ file..."
./$compiled_name

if [ $? -ne 0 ]; then
    echo "C++ file execution failed."
    exit 1
fi

echo "Executing Python file..."
python3 wavelet_plot.py
if [ $? -ne 0 ]; then
    echo "Python file execution failed."
    exit 1
fi

echo "Cleaning temporary files..."

remove_temp_files() 
{
    for temp_file in "${temp_files[@]}"
    do
        if [ -f "$temp_file" ]; then
            rm "$temp_file"
        fi
    done
}

remove_temp_files

rm $compiled_name

echo "Success."