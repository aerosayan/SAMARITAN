
# Cython code to link the C++ backend to python
cdef extern from "main.h":
	void runMeshGenerator(unsigned int _maxMeshLevel,unsigned int _baseMeshLevel)


def cy_runMeshGenerator(_maxMeshLevel,_baseMeshLevel):
	runMeshGenerator(_maxMeshLevel,_baseMeshLevel)
