#include "Mesher.h"
#include "Manager.h"
#include "Elem.h"
#include "Node.h"
#include "Point.h"
#include <iostream>


void Mesher::generateMesh(std::vector<std::vector<Point*> >& _geom)
{
	Node* root = new Node(0,getResoruceManager()->getNodeVec());
	unsigned int maxMeshLevel = 6;
	// used to traverse the mesh node vector to go through all the children
	unsigned int currentMeshLevelStart = 0;
	unsigned int currentMeshLevelEnd = 0;
	// Traverse over the geomtry matrix
	for(int i=0;i<maxMeshLevel;i++)
	{
		// handle working on the root node specially
		if(i==0){
			root->genGeomLOD(_geom);
			// set the starting iterations
			currentMeshLevelStart  = 1;
		}else if(root->isCut() == false){
			std::cerr<<"ERR: the root did not subdivide ..."<<std::endl;
			std::cerr<<"ERR: critical error , must suspend execution ..."<<std::endl;
		}else {
			currentMeshLevelEnd = getResoruceManager()->getNodeVec().size();
			for(int j=currentMeshLevelStart ;j<currentMeshLevelEnd;j++)
			{
				//std::cout<<"INF: mesh level start : "<<currentMeshLevelStart<<std::endl;
				//std::cout<<"INF: mesh level end : "<<currentMeshLevelEnd<<std::endl;
				getResoruceManager()->getNodeVec().at(j)->genGeomLOD(_geom);
			}
			currentMeshLevelStart = currentMeshLevelEnd ;
		}

	}
}
