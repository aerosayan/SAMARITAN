#pragma once
#include<vector>
// FILE : Mesher.h
// INFO : This is the class which will handle all the high level mesh generation
// // tasks. And the mesher will ask the Manager about the important parameters ,such
// // as the maximum level of subdivision level and maximum level of geometry
// // level of detail cache. And the mesher will also take the geometry and
// // set the bounding box details and create the quad tree based unstructured
// // grid.

// forward declarations
class Manager;
class Point;


class Mesher
{
public:
	Mesher(Manager* _resMan):m_resMan(_resMan){}
	virtual ~Mesher(){}

	Manager* getResoruceManager(){return m_resMan;}

	void generateMesh(std::vector<std::vector<Point*> >& _geom);
private:
	Manager* m_resMan;
};
