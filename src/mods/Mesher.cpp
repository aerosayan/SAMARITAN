#include "Mesher.h"
#include "Manager.h"
#include "Elem.h"
#include "Node.h"
#include "Point.h"
#include <iostream>


void Mesher::generateMesh(std::vector<std::vector<Point*> >& _geom)
{
	Node* root = new Node(0,getResoruceManager()->getNodeVec(),2.0f,2.0f);
	// used to traverse the mesh node vector to go through all the children
	unsigned int currentMeshLevelStart = 0;
	unsigned int currentMeshLevelEnd = 0;
	// the level from which we would like to start cleaning of the mesh
	unsigned int meshCleanStartLevel = 3;

	// Traverse over the geomtry matrix to perform mesh creation
	for(int i=0;i<m_maxMeshLevel;i++)
	{
		// handle working on the root node specially
		std::cout<<"INF: meshing level :"<<i<<" ..."<<std::endl;
		if(i==0){
			root->genGeomLOD(_geom);
			// set the starting iterations
			currentMeshLevelStart  = 1;
			getMeshLevelIndices().push_back(0);
			getMeshLevelIndices().push_back(currentMeshLevelStart);
		}else if(root->isCut() == false){
			std::cerr<<"ERR: the root did not subdivide ..."<<std::endl;
			std::cerr<<"ERR: critical error , must suspend execution ..."<<std::endl;
		}else {
			currentMeshLevelEnd = getResoruceManager()->getNodeVec().size();
			for(int j=currentMeshLevelStart ;j<currentMeshLevelEnd;j++)
			{
				//std::cout<<"INF: mesh level start : "<<currentMeshLevelStart<<std::endl;
				//std::cout<<"INF: mesh level end : "<<currentMeshLevelEnd<<std::endl;
				if(i<m_baseMeshLevel){
					getResoruceManager()->getNodeVec().at(j)->subdivide();
				}
				getResoruceManager()->getNodeVec().at(j)->genGeomLOD(_geom);
			}
			currentMeshLevelStart = currentMeshLevelEnd ;
			getMeshLevelIndices().push_back(currentMeshLevelEnd);

		}

	} // end mesh creation

	//  start mesh cleaning

}
