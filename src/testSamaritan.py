import samaritan as sam

# the maximum level of mesh creation
maxMeshLevel = 9
# the base level of mesh that is to be created
baseMeshLevel = 0

#sam.cy_addGeometry('../geoms/mod_naca2412.dat')
#sam.cy_addGeometry('../geoms/naca2412.dat')
sam.cy_runMeshGenerator(maxMeshLevel,baseMeshLevel,"geomScramjetTest.txt")
