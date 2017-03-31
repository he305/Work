from mpl_toolkits.mplot3d import Axes3D
import numpy as np
import matplotlib.pyplot as plt
import sys

fig = plt.figure()

size = float(sys.argv[1].replace(',', '.'))
for i in range (1, size+1):
    points[i-1] = float(sys.argv[1+i].replace(',', '.'))

for i in range(size+1, size*2+1):
    time[i-1] = float(sys.argv[1+size+i].replace(',', '.'))
    
a = float(sys.argv[size*2+1].replace(',', '.'))
b = float(sys.argv[size*2+2].replace(',', '.'))

def f(x):
    return x * a + b
    

x = np.arange(-20.0, 20.0, 0.01)
y = np.arange(-20.0, 20.0, 0.01)

plt.plot(x, f(x), 'r-')

for i in range(size):
    print(points[i], end='\n')
