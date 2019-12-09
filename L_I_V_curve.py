import numpy as np
import csv
import matplotlib.pyplot as plt

#Vars for L, I, V data
v_in = []
lux = []
m_amps = []

plt.figure(figsize=(4,3))

with open('liv.csv', 'r', newline='\n') as liv_data:
    readLIV = csv.reader(liv_data, delimiter=',')
    for row in readLIV:
        v_in.append(float(row[0]))
        lux.append(row[1])
        m_amps.append(float(row[2]))

    plt.scatter(v_in, m_amps, alpha=0.5)
    plt.xlabel('x')
    plt.ylabel('y')
    plt.show()