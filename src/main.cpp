#include<iostream>
#include<vector>
#include "mods/Elem.h"
#include "mods/Node.h"
#include "mods/Point.h"
#include "mods/Manager.h"
#include "mods/Mesher.h"
#include <fstream>
#include <iomanip>

void runMeshGenerator(unsigned int _maxMeshLevel,unsigned int _baseMeshLevel)
{
Manager* manager = new Manager();
manager->readInGeometry("../geoms/mod_naca2412.dat");

Mesher* mesher = new Mesher(manager,_maxMeshLevel,_baseMeshLevel);

mesher->generateMesh(manager->getGeometries());

// Output file
std::ofstream meshFile;
meshFile.open("mesh.dat");

Node * n = nullptr;
std::cout<<"INF: creating mesh file ... "<<std::endl;
for(int i =0;i<manager->getNodeVec().size();i++)
{
	n = manager->getNodeVec().at(i);
	meshFile <<std::fixed<<std::setprecision(6)<<std::endl;
	meshFile << n->getPos()->getX() <<"\t"<<n->getPos()->getY()<<"\t"
	<< n->getBoxHeight() <<"\t" <<n->getBoxLength()<<"\n";
}
meshFile.close();



for(int i = manager->getNodeVec().size()-1;i>=0;i--)
{
	/*
	std::cout<<"INF: deleting node pointer "
	<<": mesh level : "<<manager->getNodeVec().at(i)->getMeshLevel();
	std::cout<<" | sibling id : "<<manager->getNodeVec().at(i)->getSiblingId();
	*/
	if(manager->getNodeVec().at(i)->getMeshLevel() == 0){
		//std::cout<<" | parent id : root"<<std::endl; // debug
	}
	else{
		/*std::cout<<" | parent id : "
		<<manager->getNodeVec().at(i)->getParent()->getSiblingId()
		<<std::endl; // debug
		*/
	}
	// delete the pointers and make them free
	delete manager->getNodeVec().at(i);
	manager->getNodeVec().at(i) = nullptr;
}

manager->getNodeVec().clear();
}
int main(int argc,char **argv)
{
	runMeshGenerator(8,3);
	return 0;
}
