from scipy.io import wavfile
from matplotlib import pyplot as plt
from scipy.fftpack import fft
import sys



samplerate, data = wavfile.read(str(sys.argv[1]))

c = fft(data)
plt.plot(abs(c[:int(sys.argv[2])]),'r')
plt.show()
