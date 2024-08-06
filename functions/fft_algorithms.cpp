#include "fft_algorithms.h"
#include "complex_type.h"
#include <fftw3.h>

#define REAL 0
#define IMAG 1

std::vector<complex> computeFFT(const std::vector<double>& wavelet) {
    int Nt = wavelet.size();

    fftw_complex* in = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * Nt);
    fftw_complex* out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * Nt);

    for (int i = 0; i < Nt; i++) {
        in[i][REAL] = wavelet[i];
        in[i][IMAG] = 0;
    }

    fftw_plan plan = fftw_plan_dft_1d(Nt, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
    fftw_execute(plan);

    std::vector<complex> result(Nt);
    for (int i = 0; i < Nt; ++i) {
        result[i][REAL] = out[i][REAL];
        result[i][IMAG] = out[i][IMAG];
    }

    fftw_destroy_plan(plan);
    fftw_free(in);
    fftw_free(out);
    fftw_cleanup();

    return result;
}
