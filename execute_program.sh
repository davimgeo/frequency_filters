#!/bin/bash

compiled_name="generate_wavelet"

echo "Compiling C++ file..."
g++ main.cpp functions/generate_wavelet.cpp -o $compiled_name
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

echo "Executing C++ file..."
./$compiled_name

rm $compiled_name

echo "Executing Python file..."
python3 wavelet.py
if [ $? -ne 0 ]; then
    echo "Python file execution failed."
    exit 1
fi

echo "Cleaning temporary files..."
if [ -f wavelet.txt ]; then
    rm wavelet.txt
fi

echo "Success."
