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

print(x1.size)

plt.plot([x1,x1,x1+geom[:,3],x1+geom[:,3],x1],[y1,y1+geom[:,2],y1+geom[:,2],y1,y1],'ko-',markerSize=2);
plt.title("mesh");plt.grid()
orgGeom1= np.loadtxt("../geoms/scramjet_body.dat",dtype=np.float64)
plt.plot(orgGeom1[:,0],orgGeom1[:,1],'r-')
orgGeom2= np.loadtxt("../geoms/scramjet_ramp.dat",dtype=np.float64)
plt.plot(orgGeom2[:,0],orgGeom2[:,1],'r-')
plt.show()
