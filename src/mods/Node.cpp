#include "Elem.h"
#include "Node.h"
#include<iostream>

Node::Node(int _siblingId):m_siblingId(_siblingId),m_meshLevel(0)
{
		if(getSiblingId() == 0) {
			// TODO : Register this node as the quad tree root
			std::cout<<"INF: registering QuadTree root ..."<<std::endl;
		}
		else{
			std::cerr<<"ERR: can't register QuadTree root without " \
			"setting m_siblingId to 0 ... "<<std::endl;
		}
}
Node:: Node(Node* _parent,int _siblingId):m_parent(_parent),
	m_siblingId(_siblingId)
{
	if(m_parent == NULL){
		std::cerr<<"ERR: child can't be created with NULL parent"<<std::endl;
	}
	//else
	// TODO : Set a maximum mesh level restiction to prevent blow up
	m_meshLevel = m_parent->getMeshLevel() + 1;
}

Node::~Node()
{

}
void Node::delAllChild()
{
	// For root level
	if(this->getMeshLevel() == 0){
		// TODO : do nothing for now
		std::cout<<"INF: deleting children from root ..."<<std::endl;
		//std::cout<<"test1"<<std::endl;
		getChild1()->delAllChild();
		//std::cout<<"test2"<<std::endl;
		//delete getChild1();
		//std::cout<<"test3"<<std::endl;

		//std::cout<<"test4"<<std::endl;
		getChild2()->delAllChild();
		//std::cout<<"test5"<<std::endl;
		//delete getChild2();
		//std::cout<<"test6"<<std::endl;

		//std::cout<<"test7"<<std::endl;
		getChild3()->delAllChild();
		//std::cout<<"test8"<<std::endl;
		//delete getChild3();
		//std::cout<<"test9"<<std::endl;

		//std::cout<<"test10"<<std::endl;
		getChild4()->delAllChild();
		//std::cout<<"test11"<<std::endl;
		//delete getChild4();
		//std::cout<<"test12"<<std::endl;
		std::cout<<"------------"<<std::endl;
	}
	// else for children level
	else{
	if(getChild1() != nullptr){
		//std::cout<<"testA"<<std::endl;
		std::cout<<"INF: mesh level : "<<getMeshLevel()<<"..."<<std::endl;
		std::cout<<"INF: deleting child 1 of child "<<getParent()->getSiblingId()
		<<" of mesh level : " <<getMeshLevel()-1<<"..."<<std::endl;
		//std::cout<<"test13"<<std::endl;
		getChild1()->delAllChild();
		//std::cout<<"test14"<<std::endl;
		//delete getChild1();
		//std::cout<<"test15"<<std::endl;
	}
	if(getChild2() != nullptr){
		//std::cout<<"testB"<<std::endl;
		std::cout<<"INF: mesh level : "<<getMeshLevel()<<"..."<<std::endl;
		std::cout<<"INF: deleting child 2 of child "<<getParent()->getSiblingId()
		<<" of mesh level : " <<getMeshLevel()-1<<"..."<<std::endl;
		//std::cout<<"test16"<<std::endl;
		getChild2()->delAllChild();
		//std::cout<<"test17"<<std::endl;
		//delete getChild2();
		//std::cout<<"test18"<<std::endl;
	}
	if(getChild3() != nullptr){
		//std::cout<<"testC"<<std::endl;
		std::cout<<"INF: mesh level : "<<getMeshLevel()<<"..."<<std::endl;
		std::cout<<"INF: deleting child 3 of child "<<getParent()->getSiblingId()
		<<" of mesh level : " <<getMeshLevel()-1<<"..."<<std::endl;
		//std::cout<<"test19"<<std::endl;
		getChild3()->delAllChild();
		//std::cout<<"test20"<<std::endl;
		//delete getChild3();
		//std::cout<<"test21"<<std::endl;
	}
	if(getChild4() != nullptr){
		//std::cout<<"testD"<<std::endl;
		std::cout<<"INF: mesh level : "<<getMeshLevel()<<"..."<<std::endl;
		std::cout<<"INF: deleting child 4 of child "<<getParent()->getSiblingId()
		<<" of mesh level : " <<getMeshLevel()-1<<"..."<<std::endl;
		//std::cout<<"test22"<<std::endl;
		getChild4()->delAllChild();
		//std::cout<<"test23"<<std::endl;
		//delete getChild4();
		//std::cout<<"test24"<<std::endl;
	}
	}
}

void Node::setChild1(Node* _child) { m_child1 = _child; }

void Node::setChild2(Node* _child) { m_child2 = _child; }

void Node::setChild3(Node* _child) { m_child3 = _child; }

void Node::setChild4(Node* _child) { m_child4 = _child; }

void Node::subdivide()
{
	setChild1(new Node(this,1));
	setChild2(new Node(this,2));
	setChild3(new Node(this,3));
	setChild4(new Node(this,4));
}
