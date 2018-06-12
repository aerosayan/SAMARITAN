#ifndef __MAIN_H__
#define __MAIN_H__

#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

EXTERNC void runMeshGenerator(unsigned int _maxMeshLevel,unsigned int _baseMeshLevel);

#undef EXTERNC
#endif
