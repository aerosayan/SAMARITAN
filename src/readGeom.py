import numpy as np
import matplotlib.pyplot as plt

# load the geometry information
geom = np.loadtxt("../geoms/naca2412.dat.txt",dtype=np.float64)
# separate the data into x and y arrays
x = geom[:,0]
y = geom[:,1]

print(x)
print(y)

plt.plot(x,y,'ro-');
plt.title("NACA 2412");plt.grid()
plt.xlim([0,1]);plt.ylim([-0.5,0.5])
plt.show()
