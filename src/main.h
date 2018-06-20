#ifndef __MAIN_H__
#define __MAIN_H__

#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

// Import and add geometries listed in the _geomListFile
// NOTE : This is to prevent repeated writing of the geometry files
// // We just write it down in a file once and let it be.
// TODO : Delete this function and let runMeshGenerator handle it internally
EXTERNC void addGeometry(char * _geomListFile);

EXTERNC void runMeshGenerator(unsigned int _maxMeshLevel,
	unsigned int _baseMeshLevel,
	char * _geomListFile);


#undef EXTERNC
#endif
