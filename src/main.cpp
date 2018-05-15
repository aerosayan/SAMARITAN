#include<iostream>
#include<vector>
#include "mods/Elem.h"
#include "mods/Node.h"
#include "mods/Point.h"
#include "mods/Manager.h"
#include "mods/Mesher.h"

int main(int argc,char **argv)
{
	Manager* manager = new Manager();
	Mesher* mesher = new Mesher(manager);

	// creating a test geometry [a line for now]
	std::vector<Point*> geom;
	geom.push_back(new Point(0.1f,0.1f));
	geom.push_back(new Point(0.5f,0.2f));
	std::vector<std::vector<Point*> > geometries;
	geometries.push_back(geom);
	geometries.push_back(geom);

	mesher->generateMesh(geometries);






	for(int i = manager->getNodeVec().size()-1;i>=0;i--)
	{
		std::cout<<"INF: deleting node pointer "
		<<": mesh level : "<<manager->getNodeVec().at(i)->getMeshLevel();
		std::cout<<" | sibling id : "<<manager->getNodeVec().at(i)->getSiblingId();
		if(manager->getNodeVec().at(i)->getMeshLevel() == 0){
			std::cout<<" | parent id : root"<<std::endl;
		}
		else{
			std::cout<<" | parent id : "<<manager->getNodeVec().at(i)->getParent()->getSiblingId()
			<<std::endl;
		}
		delete manager->getNodeVec().at(i);
		manager->getNodeVec().at(i) = nullptr;
	}

	manager->getNodeVec().clear();
	return 0;
}
