import numpy as np
import matplotlib.pyplot as plt

# load the geometry information
geom = np.loadtxt("mesh.dat",dtype=np.float64)
# separate the data into x and y arrays
x1 = geom[:,0]
y1 = geom[:,1]

#print(x)
#print(y)
x2 = x1;
y2 = y1 + geom[:,2]

x3 = x1 + geom[:,3]
y3 = y2

x4 = x3
y4 = y1

plt.plot([x1,x2,x3,x4,x1],[y1,y2,y3,y4,y1],'ro-');
plt.title("mesh");plt.grid()
plt.show()
