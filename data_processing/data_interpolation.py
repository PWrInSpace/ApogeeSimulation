import numpy as np
from scipy.interpolate import InterpolatedUnivariateSpline as interPolate
import matplotlib.pyplot as plt

data = np.genfromtxt('/media/krzysztof/dysk 2/PWr/Poliwrocket/Praca/Funkcja zamykająca zawór w silniku/R4S_raw_data.csv', delimiter = ',')
func = interPolate(data[1:,5], data[1:,13])

savefile = open("/media/krzysztof/dysk 2/PWr/Poliwrocket/Praca/Funkcja zamykająca zawór w silniku/lot.txt", "w")

for i in range(26,1826):
    t = i/10.0
    savefile.write(str(t - 2.6))
    savefile.write(" ")
    Cd = func(i/10.0)
    savefile.write(str(Cd))
    savefile.write("\n")

savefile.close()

data = np.genfromtxt('/media/krzysztof/dysk 2/PWr/Poliwrocket/Praca/Funkcja zamykająca zawór w silniku/lot.txt', delimiter = ' ')

x = np.linspace(0, 180,endpoint=True)
plt.plot(data[1:1800,0], data[1:1800,1], 'o')
plt.plot(x, func(x), '-')
plt.legend(['Data points', 'Interpolated'])
plt.xlabel('Time [s]')
plt.ylabel('Height [m]')
plt.show()