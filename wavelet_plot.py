import matplotlib.pyplot as plt
import numpy as np

path = "/home/davi/Desktop/coding_tests/frequency_filters/"

# Loading data files
wavelet = np.loadtxt(path + "wavelet.txt")
fft_data = np.loadtxt(path + "fft_result.txt", delimiter=",")
filtered_fft_data = np.loadtxt(path + "filtered_fft_result.txt", delimiter=",")
ifft_data = np.loadtxt(path + "ifft_result.txt", delimiter=",")

# Creating a mask for Filtered FFT data
real_part_filtered = filtered_fft_data[:, 0]
imaginary_part_2 = filtered_fft_data[:, 1]

filtered_fft_result = real_part_filtered + 1j * imaginary_part_2

n2 = len(filtered_fft_result)
freq_2 = np.fft.fftfreq(n2, d=0.001)
mask_filtered_fft = freq_2 > 0
filtered_fft_abs = 2.0 * np.abs(filtered_fft_result / n2)

# IFFT
real_part_ifft = ifft_data[:, 0]

# Plotting the results
fig, ax = plt.subplots(nrows=3, ncols=1, figsize=(18, 10))

ax[0].plot(np.arange(len(wavelet)), wavelet)
ax[0].set_title("Wavelet", fontsize=18)
ax[0].set_xlabel("Time [s]", fontsize=15)

ax[1].plot(freq_2[mask_filtered_fft], filtered_fft_abs[mask_filtered_fft], label="cut-off frequency = 35Hz")
ax[1].set_title("Filtered Wavelet Frequency Spectrum", fontsize=18)
ax[1].set_xlabel("Frequency [Hz]", fontsize=15)
ax[1].set_ylabel("Amplitude", fontsize=15)
ax[1].legend(loc="lower right")

ax[2].plot(np.arange(len(real_part_ifft)), real_part_ifft, label="cut-off frequency = 35Hz")
ax[2].set_title("Wavelet Filtered", fontsize=18)
ax[2].set_xlabel("Time [s]", fontsize=15)
ax[2].legend(loc="lower right")

for i in range(len(ax)):
    ax[i].grid(True)

plt.tight_layout()
plt.show()

# Creating a mask for FFT data
# real_part_fft = fft_data[:, 0]
# imaginary_part = fft_data[:, 1]

# fft_result = real_part_fft + 1j * imaginary_part

# n = len(fft_result)
# freq = np.fft.fftfreq(n, d=0.001)
# mask_fft = freq > 0
# fft_abs = 2.0 * np.abs(fft_result / n)

# ax[1].plot(freq[mask_fft], fft_abs[mask_fft])
# ax[1].set_title("Wavelet Frequency Spectrum", fontsize=18)
# ax[1].set_ylabel("Amplitude", fontsize=15)