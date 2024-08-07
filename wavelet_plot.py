import matplotlib.pyplot as plt
import numpy as np

path = "/home/davi/Desktop/coding_tests/frequency_filters/"

# Loading data files
wavelet = np.loadtxt(path + "wavelet.txt")
fft_data = np.loadtxt(path + "fft_result.txt", delimiter=",")
filtered_fft_data = np.loadtxt(path + "filtered_fft_result.txt", delimiter=",")
ifft_data = np.loadtxt(path + "ifft_result.txt", delimiter=",")
parameters_file = np.loadtxt(path + "parameters_file.txt")

# Defining Parameters
Nt = parameters_file[0]
dt = parameters_file[1]
fmax = parameters_file[2]
cutoff_frequency = parameters_file[3]
lowcutoff_freq = parameters_file[4]
highcutoff_freq = parameters_file[5]
filter_type = parameters_file[6]

# Creating a mask for Filtered FFT data
real_part_filtered = filtered_fft_data[:, 0]
imaginary_part_2 = filtered_fft_data[:, 1]

filtered_fft_result = real_part_filtered + 1j * imaginary_part_2

n2 = len(filtered_fft_result)
freq_2 = np.fft.fftfreq(n2, d=dt)
mask_filtered_fft = freq_2 > 0
filtered_fft_abs = 2.0 * np.abs(filtered_fft_result / n2)

# IFFT
real_part_ifft = ifft_data[:, 0]

# Defining label type
if filter_type < 1:
    freq_label = f"cut-off frequency = {cutoff_frequency} Hz\nfmax = {fmax} Hz"
else:
    freq_label = f"low-cut-off frequency = {lowcutoff_freq} Hz\nhigh-cut-off frequency = {highcutoff_freq} Hz\nfmax = {fmax} Hz"   

# Plotting the results
fig, ax = plt.subplots(nrows=3, ncols=1, figsize=(18, 10))

# Plot Wavelet
ax[0].plot(np.arange(len(wavelet)) * dt, wavelet, label="Original Wavelet")
ax[0].set_title("Wavelet", fontsize=18)
ax[0].set_xlabel("Time [s]", fontsize=15)

# Plot Filtered FFT
ax[1].plot(freq_2[mask_filtered_fft], filtered_fft_abs[mask_filtered_fft], label=freq_label)
ax[1].set_title("Filtered Wavelet Frequency Spectrum", fontsize=18)
ax[1].set_xlabel("Frequency [Hz]", fontsize=15)
ax[1].set_ylabel("Amplitude", fontsize=15)

# Plotting IFFT (Filtered Wavelet)
ax[2].plot(np.arange(len(real_part_ifft)) * dt, real_part_ifft, label=f"cut-off frequency = {cutoff_frequency} Hz")
ax[2].set_title("Filtered Wavelet", fontsize=18)
ax[2].set_xlabel("Time [s]", fontsize=15)

for i in range(len(ax)):
    ax[i].legend(loc="lower right")
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