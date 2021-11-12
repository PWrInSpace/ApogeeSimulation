import numpy as np
from scipy.interpolate import InterpolatedUnivariateSpline as interPolate
import matplotlib.pyplot as plt

data = np.genfromtxt('/media/krzysztof/dysk 2/PWr/Poliwrocket/Praca/Funkcja zamykająca zawór w silniku/Cd(machnum).csv', delimiter = ',')
func = interPolate(data[1:,0], data[1:,1])

# matplotlib plot
x = np.linspace(0, 1, num=1000, endpoint=True)
plt.plot(data[1:35,0], data[1:35,1], 'o')
plt.plot(x, func(x), '-')
plt.legend(['Data points', 'Interpolated'])
plt.xlabel('Mach number')
plt.ylabel('Cd')
plt.show()

savefile = open("/media/krzysztof/dysk 2/PWr/Poliwrocket/Praca/Funkcja zamykająca zawór w silniku/data.txt", "w")

for i in range(101):
    Cd = func(i/100.0)
    savefile.write(str(Cd))
    savefile.write("\n")

savefile.close()