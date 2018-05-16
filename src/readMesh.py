import numpy as np
import matplotlib.pyplot as plt

# load the geometry information
geom = np.loadtxt("mesh.dat",dtype=np.float64)
# separate the data into x and y arrays
x1 = geom[:,0]
y1 = geom[:,1]

#print(x)
#print(y)
"""
x2 = x1;
y2 = y1 + geom[:,2]

x3 = x1 + geom[:,3]
y3 = y2

x4 = x3
y4 = y1
"""

plt.plot([x1,x1,x1+geom[:,3],x1+geom[:,3],x1],[y1,y1+geom[:,2],y1+geom[:,2],y1,y1],'ro-',markerSize=2);
plt.title("mesh");plt.grid()
orgGeom = np.loadtxt("../geoms/mod_naca2412.dat",dtype=np.float64)
plt.plot(orgGeom[:,0],orgGeom[:,1],'bo-')
plt.show()
