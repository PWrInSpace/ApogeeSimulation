import numpy as np
from scipy.interpolate import InterpolatedUnivariateSpline as interPolate
import matplotlib.pyplot as plt

CdFile = 'air_breaker_drag.csv'


data = np.genfromtxt(CdFile, delimiter = ' ')
func = interPolate(data[0:,0], data[0:,2])

# matplotlib plot
x = np.linspace(0, 3, num=1000, endpoint=True)
plt.plot(data[0:100,0], data[0:100,2], 'o')
plt.plot(x, func(x), '-')
plt.legend(['Data points', 'Interpolated'])
plt.xlabel('Mach number')
plt.ylabel('Cd')
plt.show()

savefile = open("../sim/data/air_breaker_data.txt", "w")

for i in range(301):
    Cd = func(i/100.0)
    savefile.write(str(Cd))
    savefile.write("\n")

savefile.close()