# Cython code to link the C++ backend to python
from cpython cimport array

cdef extern from "main.h":
	void addGeometry(char * _geomListFile)

cdef extern from "main.h":
	void runMeshGenerator(unsigned int _maxMeshLevel,
	unsigned int _baseMeshLevel,
	char * _geomListFile)

def cy_addGeometry(_geomListFile):
	addGeometry(_geomListFile)

def cy_runMeshGenerator(_maxMeshLevel,_baseMeshLevel,_geomListFile):
	runMeshGenerator(_maxMeshLevel,_baseMeshLevel,_geomListFile)
