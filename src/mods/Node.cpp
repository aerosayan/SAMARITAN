#include "Elem.h"
#include "Node.h"
#include "Point.h"
#include<iostream>

Node::Node(int _siblingId,std::vector<Node*>& _resMan):
m_siblingId(_siblingId),m_meshLevel(0),m_resMan(_resMan),m_boxLength(10.0f),
m_boxHeight(7.0f)
{
		if(getSiblingId() == 0) {
			std::cout<<"INF: registering QuadTree root ..."<<std::endl;
			// resgister to resource manager
			registerToResMan();
			// set node central position
			m_pos = new Point(0.0f,0.0f);

			double x = getPos()->getX();
			double y = getPos()->getY();
			// set bounding box
			m_boundingBox.clear();
			m_boundingBox.push_back(new Point(x,y));
			m_boundingBox.push_back(new Point(x,y+getBoxHeight()));
			m_boundingBox.push_back(new Point(x+getBoxLength(),y+getBoxHeight()));
			m_boundingBox.push_back(new Point(x+getBoxLength(),y));
			m_boundingBox.push_back(m_boundingBox.at(0));
			// TODO : Set positon and bounding box in a better way
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
	// TODO : Set positon and bounding box in better way
}

Node::~Node()
{

}

void Node::setChild1(Node* _child) { m_child1 = _child; }

void Node::setChild2(Node* _child) { m_child2 = _child; }

void Node::setChild3(Node* _child) { m_child3 = _child; }

void Node::setChild4(Node* _child) { m_child4 = _child; }

void Node::setBoundingBox()
{
	// ERROR
	double x = getPos()->getX();
	double y = getPos()->getY();

	m_boxLength = getParent()->getBoxLength()/2.0f;
	m_boxHeight = getParent()->getBoxHeight()/2.0f;
	// set bounding box
	m_boundingBox.clear();
	m_boundingBox.push_back(new Point(x,y));
	m_boundingBox.push_back(new Point(x,y+getBoxHeight()));
	m_boundingBox.push_back(new Point(x+getBoxLength(),y+getBoxHeight()));
	m_boundingBox.push_back(new Point(x+getBoxLength(),y));
	m_boundingBox.push_back(m_boundingBox.at(0));
}

void Node::subdivide()
{
	double x = getPos()->getX();
	double y = getPos()->getY();

	setChild1(new Node(this,1,m_resMan));
	getChild1()->setPos(new Point(x,y));
	getChild1()->setBoundingBox();

	setChild2(new Node(this,2,m_resMan));
	getChild2()->setPos(new Point(x+getBoxLength()/2.0f,y));
	getChild2()->setBoundingBox();

	setChild3(new Node(this,3,m_resMan));
	getChild3()->setPos(new Point(x,y+getBoxHeight()/2.0f));
	getChild3()->setBoundingBox();

	setChild4(new Node(this,4,m_resMan));
	getChild4()->setPos(new Point(x+getBoxLength()/2.0f,y+getBoxHeight()/2.0f));
	getChild4()->setBoundingBox();
}

bool Node::rayBoxIntersectionTest2D(std::vector<Point*>& _geometry)
{
	// Point placeholders
	Point *p1,*p2,*p3,*p4;
	// vector directional components
	double rx,ry,sx,sy;
	// vector cross product magnitude
	double rs;
	// the intercepts
	double u,t;
	// run loop to go over all the defined geometry edges
	for (int i = 0;i<_geometry.size()-1;i++)
	{
		// select the geometry edge points
		p1 = _geometry.at(i);
		p2 = _geometry.at(i+1);
		rx = p2->getX() - p1->getX();
		ry = p2->getY() - p1->getY();
		// run loop to go over the bounding box vectors
		for(int j = 0;j<m_boundingBox.size()-1;j++)
		{
			// select the bounding box side points
			p3 = m_boundingBox.at(j);
			p4 = m_boundingBox.at(j+1);
			std::cout<<"-----------------------------"<<std::endl;
			std::cout<<"p1.x : "<<p1->getX()<<"\t| p1.y : "<<p1->getY()<<std::endl;
			std::cout<<"p2.x : "<<p2->getX()<<"\t| p2.y : "<<p2->getY()<<std::endl;
			std::cout<<"p3.x : "<<p3->getX()<<"\t| p3.y : "<<p3->getY()<<std::endl;
			std::cout<<"p4.x : "<<p4->getX()<<"\t| p4.y : "<<p4->getY()<<std::endl;
			sx = p4->getX() - p3->getX();
			sy = p4->getY() - p3->getY();
			// calculate r*s cross product
			rs = ( rx*sy - ry*sx); // dont care about direction
			// finaly calculate intercepts
			u = (float)((p3->getX()-p1->getX())*ry - \
			 	(p3->getY()-p1->getY())*rx)/(float)rs;
			t = (float)((p3->getX()-p1->getX())*sy - \
				(p3->getY()-p1->getY())*sx)/(float)rs;

			std::cout<<"u : "<<u<<"\t\t| t : "<<t<<std::endl;
			//std::cout<<"rs : "<<rs<<" | rx : "<<rx<<" | ry : "<<ry<<std::endl;
			//std::cout<<"sx : "<<sx<<" | sy : "<<sy<<std::endl;

			// intercept test
			if(u>=0 && u<=1 && t>=0 && t<=1){
				std::cout<<"-------------------------------\n";
				std::cout<<"INF: ray intersection test has succedded ...\n";
				std::cout<<"-------------------------------"<<std::endl;
				break;
			}
			else{
				std::cout<<"INF: ray intersection tes has failed ..."<<std::endl;
			}
		}
	}

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
