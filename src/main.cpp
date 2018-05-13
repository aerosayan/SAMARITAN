#include<iostream>
#include<vector>
#include "mods/Elem.h"
#include "mods/Node.h"
#include "mods/Point.h"
#include "mods/Manager.h"

int main(int argc,char **argv)
{
	std::vector<Node*> resMan;
	Node* n = new Node(0,resMan);
	Node* t;
	n->subdivide();

	std::cout<<resMan.size()<<std::endl;

	std::vector<Point*> geom;
	geom.push_back(new Point(0.5f,0.5f));
	geom.push_back(new Point(1.0f,1.0f));

	n->runIntersectionTests(geom);









	for(int i = resMan.size()-1;i>=0;i--)
	{
		std::cout<<"INF: deleting node pointer "
		<<": mesh level : "<<resMan.at(i)->getMeshLevel();
		std::cout<<" | sibling id : "<<resMan.at(i)->getSiblingId();
		if(resMan.at(i)->getMeshLevel() == 0){
			std::cout<<" | parent id : root"<<std::endl;
		}
		else{
			std::cout<<" | parent id : "<<resMan.at(i)->getParent()->getSiblingId()
			<<std::endl;
		}
		delete (resMan.at(i));
		resMan.at(i) = nullptr;
	}

	resMan.clear();
	return 0;
}
