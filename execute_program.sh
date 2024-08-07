#!/bin/bash

compiled_name="filtered_wavelet"
functions=(functions/generate_wavelet.cpp functions/fft_algorithms.cpp functions/frequency_filters.cpp)
temp_files=(wavelet.txt fft_result.txt filtered_fft_result.txt ifft_result.txt parameters_file.txt)

compile_cpp_file()
{
    echo "Compiling C++ file..."
    g++ main.cpp "${functions[@]}" -o $compiled_name -lfftw3
    if [ $? -ne 0 ]; then
        echo "Compilation failed."
        exit 1
    fi
}

execute_cpp_file()
{
   echo "Executing C++ file..."
    ./$compiled_name
    if [ $? -ne 0 ]; then
        echo "C++ file execution failed."
        exit 1
    fi 
}

execute_python_file()
{
    python3 wavelet_plot.py
    if [ $? -ne 0 ]; then
        echo "Python file execution failed."
        exit 1
    fi    
}

remove_temp_files() 
{
    echo "Cleaning temporary files..."
    for temp_file in "${temp_files[@]}"
    do
        if [ -f "$temp_file" ]; then
            rm "$temp_file"
        fi
    done
}

compile_cpp_file
execute_cpp_file
execute_python_file
remove_temp_files

rm $compiled_name

echo "Success."