# SAMARITAN
*A block structured grid generator based on quad tree decomposition.*
### Author : Sayan Bhattacharjee
### Email : aero.sayan@gmail.com
LICENSE : DEFAULT : for now; will update to GPL v2 very soon.

![genius-hagrid](memes/hagrid-1.jpg)

### INTRODUCTION
This is a block stuctured grid generator based on quad tree decomposition for Computaional Fluid Dynamics(CFD). The quad tree decompositon is done after running a series of ray-box intersection tests. The ray is created from the geometric edges and the box are the internal domains of the mesh.

### AIM OF CREATION
#### Primary aim :
This grid generator was created by me to satisfy my personal intrigue of hypersonic CFD simulations.
Since, the grid created is block structured in nature, thus it is meant to be used effeciently using Adaptive Mesh Refinement(AMR), possibly for my PhD in distant future.
#### Secondary aim :
CFD is cool and very math and computational power intensive, thus I just wanted to learn how this things work under the hood. Adaptive Mesh Refinement has some common aspects with Machine Learning too, essentially both are based on minimizing error/cost/residual function results at positions of high gradients, which I just adore.

![spiderman-desk](memes/spiderman-desk-1.jpg)


### INSPIRATION
Inspiration came from SpaceX personell Adam Lichtl and Stephen Jones from their talk about simultating combustion in very large rocket engines.<br/>
From: GPU Tech Conference, San Jose, California, March 17 - 20, 2015.
Originally posted on :<br/>
http://on-demand.gputechconf.com/gtc/2015/video/S5398.html

### FOLDER STRUCTURE :
SAMARITAN
+ src/ : contains the source files
+ src/mods/ : contains the C++ backend
+ geoms/ : contains the mesh geometry
+ mesh-pictures/ : conatains mesh output pictures
+ memes/ : Can I has grid please?

### TECHNOLOGY USED
+ C++ for high performance backend code,
+ Cython for linking C++ code with Python,
+ Python for calling the C++ code,
+ Python for visualization.

### COMPILATION AND TEST
#### For developers :
To compile only the C++ code and do development.
First cd to src folder, then run scons, then run main.exe, then run visualizeMesh.py.
Note that MSYS2 was used to provide linux like environment in windows to provide good programming experience.
And if requried the basic cmd commands can also be used by a user who does not wish to use MSYS2.

```
$ cd src
$ scons
$ main.exe
$ python visualizeMesh.py
```
#### For use in python :
Cython is used to allow Python to call the grid generator from Python itself. For this, setuptools of Python 2.7 was used to create a .pyd file that can be imported into Python as a library.
It is to be noted that we are using Microsoft Visual Studio Compiler to compile our library for compatibility reasons.

```
$ cd src
$ python setup.py build_ext --inplace -cmsvc
$ ls | grep samaritan.pyd
samaritan.pyd*
$ python testSamaritan.py
$ python visualizeMesh.py
```

### Meshing result for a NACA-2412 aerofoil
Fig 1 : NACA 2412 mesh
![NACA 2412 mesh](mesh-pictures/01-01-mesh-original-zoom.png)

Fig 2 : NACA 2412 mesh zoomed
![NACA 2412 mesh zoomed](mesh-pictures/01-02-mesh-zoomed-view.png)

Fig 3 : NACA 2412 trailing edge mesh zoomed
![NACA 2412 trailing edge mesh zoomed ](mesh-pictures/02-01-trailing-edge-mesh.png)

For more pictures see mesh-pictures folder.

### Future work
+ For the sake of everything that is fluffy and sweet in this world, refactor the visulaization script to use bokeh or datashader instead of matplotlib.
+ Allow plotting of multiple geometries at once.
+ Clean out the un-necessary volumes inside the solid region of the aerofoil geometry.
+ Allow python full control over the geometry selection and mesh creation from Python.
+ Make it easy to select and name the different boundaries and set the boundary conditions.
+ Allow optional conversion of std::vector containers to simple C arrays to allow compatibility with Numpy.

### Current flow solver status

![gordon-angry](memes/gordon-1.jpg)

#### Disclaimer
I do not own the memes.Do I need to ?
