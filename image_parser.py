import numpy as np
import csv
import matplotlib.pyplot as plt
import scipy.signal as signal

#Vars for intensity values
#x = []
y = []

# Lens focal lengths in mm
f_condenser = 27
f_focus = 1000

# Pixel pitch of sensor in um
pix_pitch = 1.12

# Lines per mm of grating
lines = 1000
grating_pitch = 1 / (1000 * lines) #converts to meters

# Angle of diffraction in degrees
read_angle = 42

def sep_angle(pixels):
    d = pixels * pix_pitch / 1000 #in mm
    return np.arctan(d/f_focus)

def spectral_diff(theta): 
    value = grating_pitch * np.cos(np.radians(read_angle)) * theta
    return (value * (10**9)) #in nm

plt.figure(figsize=(20,2))

with open('168737.csv', 'r', newline='\n') as intensity:
    readI = csv.reader(intensity, delimiter=',')
    xpixels = 0
    for row in readI:
        y.append(float(row[2]))
        xpixels += 1
    x = np.arange(0,xpixels)

    maxima, _ = signal.find_peaks(y, distance=150)
    print("\nMaxima")
    for max in maxima:
        print(max,end=", ")

    print("\nSeparating pixels")   

    sep_pix = np.diff(maxima)

    for dist in sep_pix:
        print(int(dist), end=", ")

    pix_avg = np.average(sep_pix)
    sep_theta = sep_angle(pix_avg)
    delta_lambda = spectral_diff(sep_theta)
    print("\n\nAverage separation in px = " + str(pix_avg) + " px")
    print("Average separation in radians = " + str(sep_theta) + " rad")
    print("Average spectral separation = " + str(delta_lambda) + " nm")

    plt.plot(x,y)

    plt.xticks(np.arange(0,3500,250))
    plt.yticks(np.arange(0,255,25))
    
    plt.show()

