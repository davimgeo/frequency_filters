import matplotlib.pyplot as plt
import numpy as np

path = "/home/davi/Desktop/coding_tests/frequency_filters/"

data = np.loadtxt(path + "fft_result.txt", delimiter=",")

real_part = data[:, 0]
imaginary_part = data[:, 1]

fft_result = real_part + 1j * imaginary_part

n = len(fft_result)
freq = np.fft.fftfreq(n, d=0.001)
mask = freq > 0
fft_abs = 2.0 * np.abs(fft_result / n)

fig, ax = plt.subplots(nrows=1, ncols=1, figsize=(18, 10))

ax.plot(freq[mask], fft_abs[mask])

plt.show()
