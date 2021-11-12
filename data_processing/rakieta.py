#!/usr/bin/python3
import pandas as pd

# fileLot = open("/media/krzysztof/dysk 2/PWr/Poliwrocket/Praca/Funkcja zamykająca zawór w silniku/R4_data.txt", "r")

file = pd.read_csv("/media/krzysztof/dysk 2/PWr/Poliwrocket/Praca/Funkcja zamykająca zawór w silniku/R4_data.csv", delimiter=',')

savefile = open("/media/krzysztof/dysk 2/PWr/Poliwrocket/Praca/Funkcja zamykająca zawór w silniku/data_EUROC2.txt", "w")
savefile2 = open("/media/krzysztof/dysk 2/PWr/Poliwrocket/Praca/Funkcja zamykająca zawór w silniku/data_EUROC2_t.txt", "w")
flightData = []
flightData2 = []

for item in file['Altitude']:
    flightData.append(item)

for item in file['Time (ms)']:
    flightData2.append(item)


for data in flightData:
    savefile.write(str(data))
    savefile.write('\n')

for data in flightData2:
    savefile2.write(str(data))
    savefile2.write('\n')

savefile.close()
savefile2.close()