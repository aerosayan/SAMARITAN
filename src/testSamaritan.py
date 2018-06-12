import samaritan as sam

# the maximum level of mesh creation
maxMeshLevel = 8
# the base level of mesh that is to be created
baseMeshLevel = 2

# For now geometry is called from ../geoms/mod/naca2412.dat
sam.cy_runMeshGenerator(maxMeshLevel,baseMeshLevel)
