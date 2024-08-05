import matplotlib.pyplot as plt
import numpy as np

path = "/home/davi/Desktop/coding_tests/frequency_filters/"

wavelet = np.loadtxt(path + "wavelet.txt")

plt.plot(wavelet)
plt.show()