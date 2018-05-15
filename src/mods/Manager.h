#pragma once
#include<vector>
// FILE : Manager.h
// INFO : manage all the different assets of the software including clearing
//		memory used by pointers. Also, managing things like geometric cache
//		and software essential control laws will be handled.
class Elem;
class Node;
class Point;

class Manager
{
public:
	Manager(){};
	virtual ~Manager(){};
	void registerNodes(Node* _node);
	void setMaxGeomLOD(unsigned int _maxLOD);
private:
	// maximum level of detail or mesh level to be stored in the geom cache
	unsigned int m_maxGeomCacheLOD;
	// maximum level of subdivision allowed
	unsigned int m_maxMeshLevel;

	// the list of the nodes stored in order of creation
	std::vector<Node*> m_nodes;
	// the geometry that is to be meshed
	// // NOTE : the geometry vector is kept as a 2D matrix to allow multiple
	// // geometries in the same mesh. But, the nodes will accept only a 1D vector
	// // so I have some things to do.
	std::vector<std::vector<Point*> > m_geom;

};
