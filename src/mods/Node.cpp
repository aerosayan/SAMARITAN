#include "Elem.h"
#include "Node.h"
#include<iostream>

Node::Node(int _siblingId,std::vector<Node*>& _resMan):
m_siblingId(_siblingId),m_meshLevel(0),m_resMan(_resMan)
{
		if(getSiblingId() == 0) {
			std::cout<<"INF: registering QuadTree root ..."<<std::endl;
			// resgister to resource manager
			registerToResMan();
		}
		else{
			std::cerr<<"ERR: can't register QuadTree root without " \
			"setting m_siblingId to 0 ... "<<std::endl;
		}
}

Node:: Node(Node* _parent,int _siblingId,std::vector<Node*>& _resMan):
m_parent(_parent),m_resMan(_resMan),m_siblingId(_siblingId)
{
	if(m_parent == NULL){
		std::cerr<<"ERR: child can't be created with NULL parent"<<std::endl;
	}
	//else
	// TODO : Set a maximum mesh level restiction to prevent blow up
	m_meshLevel = m_parent->getMeshLevel() + 1;
	// register to resouce manager
	registerToResMan();
}

Node::~Node()
{

}

void Node::setChild1(Node* _child) { m_child1 = _child; }

void Node::setChild2(Node* _child) { m_child2 = _child; }

void Node::setChild3(Node* _child) { m_child3 = _child; }

void Node::setChild4(Node* _child) { m_child4 = _child; }

void Node::subdivide()
{
	setChild1(new Node(this,1,m_resMan));
	setChild2(new Node(this,2,m_resMan));
	setChild3(new Node(this,3,m_resMan));
	setChild4(new Node(this,4,m_resMan));
}

void Node::registerToResMan()
{
	std::cout<<"INF: registering node : mesh level : "<<getMeshLevel()
	<<" | sibling id : "<<getSiblingId();

	if(getMeshLevel() == 0){
		std::cout<<" | parent id : root "<<std::endl;
	}
	else{

		std::cout<<" | parent id : "<<getParent()->getSiblingId()<<std::endl;
	}

	m_resMan.push_back(this);
}
