#include<iostream>
#include<vector>
#include "mods/Elem.h"
#include "mods/Node.h"

int main(int argc,char **argv)
{
	std::vector<Node*> resMan;
	Node* n = new Node(0,resMan);
	Node* t;
	n->subdivide();
	n->getChild1()->subdivide();
	n->getChild4()->subdivide();

	std::cout<<resMan.size()<<std::endl;

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
