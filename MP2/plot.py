import numpy as np
import matplotlib.pyplot as plt
import sys

g = open(sys.argv[1],"r")
param = g.read().split()
with open(sys.argv[2]) as f:
	Vout = [line.strip() for line in open(sys.argv[2])]

omega1 = float(param[0])
omega2 = float(param[1])
T = 3*2*np.pi/omega1
N = 20*T/(2*np.pi/omega2)
dt = T/N
t = np.arange(0.0,T,dt)
Vin = np.sin(omega1*t) + .5*np.sin(omega2*t)
Vout = map(float,Vout)
N2 = len(Vout)
t2 = np.arange(0.0,N2*dt,dt)

plt.figure(1)
plt.subplot(121)
plt.plot(t,Vin)
plt.xlabel('Time [s]')
plt.ylabel('Signal [V]')
plt.title('Input')

plt.subplot(122)
plt.plot(t2,Vout)
plt.xlabel('Time [s]')
plt.ylabel('Signal [V]')
plt.title('Output')

plt.show()
