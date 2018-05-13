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
	void registerGeomLOD(std::vector<Point*> _points);
private:
	// maximum level of detail or mesh level to be stored in the geom cache
	unsigned int m_maxGeomCacheLOD;
	// the list of the nodes stored in order of creation
	std::vector<Node*> m_nodes;

	// geometry level of detail cache storing the pieces of geometry for
	// // which we need to run ray intersection tests. Storing in different
	// // levels allow us to spend less time doing computation on geometry which
	// // is clearly  not in the domain of interest. But the LOD has been capped
	// // to a certain max value to prevent creation of infinite LOD which are
	// // not necessary
	std::vector< std::vector<Point*> > m_geomLODCache;
};
