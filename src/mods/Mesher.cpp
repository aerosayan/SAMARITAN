#include "Mesher.h"
#include "Point.h"
#include "Manager.h"
#include "Node.h"


void Mesher::generateMesh(std::vector<Point*>& _geom)
{
	Node* root = new Node(0,getResoruceManager());
	unisgned int workingMeshLevel = 0;
	std::vector<bool> rayTestStatus();
	// Traverse over the geomtry matrix
	for(int i=0;i<_geom.size();i++)
	{
		// send geometry vectors in for ray testing one by one






	}
}
