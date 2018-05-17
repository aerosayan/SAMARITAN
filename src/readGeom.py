import numpy as np
import matplotlib.pyplot as plt

# load the geometry information
geom = np.loadtxt("../geoms/naca2412.dat.txt",dtype=np.float64)
# separate the data into x and y arrays
x = geom[:,0]
y = geom[:,1]

print(x)
print(y)

x = (x+0.5)
y = (y+0.5)
plt.plot(x,y,'ro-');
plt.title("NACA 2412");plt.grid()
plt.xlim([0,2]);plt.ylim([0,1])
plt.show()


np.savetxt("../geoms/mod_naca2412.dat",np.c_[x,y],fmt="%1.6e")
