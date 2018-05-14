#include "Point.h"
#include "Elem.h"
#include "Node.h"
#include<iostream>
#include <cmath>

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


bool Node::runIntersectionTests(std::vector<Point*>& _geometry)
{
	int result = -1;
	std::cout<<"INF: running intersection test 1 of 3 ..."<<std::endl;
	if(rayBoxIntersectionTest2D(_geometry, 1,1,1e-3,1e-3) >= 1){
		return true;
	}
	std::cout<<"INF: running intersection test 2 of 3 ..."<<std::endl;
	result = rayBoxIntersectionTest2D(_geometry,1,101,1e-3,1e-3);
	std::cout<<"result : "<<result<<std::endl;
	if(result >=1 && (result % 2) != 0){
		std::cout<<"test1"<<std::endl;
		return true;
	}
	std::cout<<"INF: running intersection test 3 of 3 ..."<<std::endl;
	result = -1; // resetting variable to prevent perevious result creeping in
	result = rayBoxIntersectionTest2D(_geometry,101,1,1e-3,1e-3);
	std::cout<<"result : "<<result<<std::endl;
	if(result >=1 && (result % 2) != 0){
		std::cout<<"test2"<<std::endl;
		return true;
	}
	// if all else fails then no intersection has occured
	std::cout<<"INF:  intersection test 3 of 3 have failed ..."<<std::endl;
	return false;
}

int Node::rayBoxIntersectionTest2D(std::vector<Point*>& _geometry, int _s1,int _s2,double _xtol,double _ytol)
{
	// Point placeholders
	Point *p1,*p2,*p3,*p4;
	// vector directional components
	double rx,ry,sx,sy;
	// vector cross product magnitude
	double rs;
	// the intercepts
	double u,t;
	// coordinates
	double x1,y1,x2,y2,x3,y3,x4,y4;
	// line segment external division factors
	double m,n;
	// number of intersection
	int intersectionCount = 0;

	// hit domain edges flags
	std::vector<bool> hitDomainEdges(getBoundingBox().size()-1,false);

	// run loop to go over all the defined geometry edges
	for (int i = 0;i<_geometry.size()-1;i++)
	{
		// select the geometry edge points
		p1 = _geometry.at(i);
		p2 = _geometry.at(i+1);
		x1 = p1->getX(); y1 = p1->getY();
		x2 = p2->getX(); y2 = p2->getY();

		// vector scaling operation
		// first check based on the x co-ordinates
		// NOTE : a preferential treatment is given to the x component
		// // for my case it is okay to give preferential treatment to the
		// // x component however in somebody else's case it may not be.
		// // So is there something that can be done for this?
		// considering x1 is of left point and x2 is of right point
		// TODO : it is not correct . correct it
		std::cout<<"INF: vector scaling requested is ..."<<std::endl;
		std::cout<<"------------------------------------"<<std::endl;
		std::cout<<"s1 : "<<_s1<<" | s2 : "<<_s2<<std::endl;
		std::cout<<"xtol : "<<_xtol<<" | ytol : "<<_ytol<<std::endl;

		if(_s1 == 1 && _s2 == 1 ){
			// do nothing
		}else if(_s1 == 1 && _s2 > 1){
			// first run tol check then write equations based on which is left and right
			if((double)fabs(x2-x1) > _xtol){
				// set the values of m and n
				m = _s2;
				n = m-1;
				if(x2>x1){
					// change x2 and y2
					x2 = (double)(m*x2 - n*x1)/(double)(m-n);
					y2 = (double)(m*y2 - n*y1)/(double)(m-n);
				}else{ //x1>x2
					// change x1 and y1
					x1 = (double)(m*x1 - n*x2)/(double)(m-n);
					y1 = (double)(m*y1 - n*y2)/(double)(m-n);
				}
			}
			else{ //abs(x2-x1) < _xtol i.e  x1 == x2 boss
				if((double)fabs(y2-y1) > _ytol){
					// set the values of m and n
					m = _s2;
					n = m-1;
					// TODO : We are writing extra code. need to refactor
					if(y2>y1){
						// change x2 and y2
						x2 = (double)(m*x2 - n*x1)/(double)(m-n);
						y2 = (double)(m*y2 - n*y1)/(double)(m-n);
					}else{
						// change x1 and y1
						x1 = (double)(m*x1 - n*x2)/(double)(m-n);
						y1 = (double)(m*y1 - n*y2)/(double)(m-n);
					}
				}
			}
		}else if(_s1 >1 && _s2 == 1){
			// first run tol check then write equations based on which is left and right
			if((double)fabs(x2-x1) > _xtol){
				// set the values of m and n
				m = _s1;
				n = m-1;
				if(x1<x2){
					// change x1 and y1
					x1 = (double)(m*x1 - n*x2)/(double)(m-n);
					y1 = (double)(m*y1 - n*y2)/(double)(m-n);
				}else{ //x1>x2
					// change x2 and y2
					x2 = (double)(m*x2 - n*x1)/(double)(m-n);
					y2 = (double)(m*y2 - n*y1)/(double)(m-n);
				}
			}
			else{ //abs(x2-x1) < _xtol i.e  x1 == x2 boss
				if((double)fabs(y2-y1) > _ytol){
					// set the values of m and n
					m = _s1;
					n = m-1;
					// TODO : We are writing extra code. need to refactor
					if(y1<y2){
						// change x1 and y1
						x1 = (double)(m*x1 - n*x2)/(double)(m-n);
						y1 = (double)(m*y1 - n*y2)/(double)(m-n);
					}else{
						// change x2 and y2
						x2 = (double)(m*x2 - n*x1)/(double)(m-n);
						y2 = (double)(m*y2 - n*y1)/(double)(m-n);
					}
				}
			}
			std::cout<<"INF: vector scaling operation has been completed ..."<<std::endl;
		}else{
			std::cerr<<"ERR: we have an error unexpected scaling factors are given ...."<<std::endl;
			std::cerr<<"s1 : "<<_s1<<" | s2 : "<<_s2<<std::endl;
		}

		rx = x2 - x1;
		ry = y2 - y1;
		// run loop to go over the bounding box vectors
		for(int j = 0;j<m_boundingBox.size()-1;j++)
		{
			// select the bounding box side points
			p3 = m_boundingBox.at(j);
			p4 = m_boundingBox.at(j+1);
			x3 = p3->getX(); y3 = p3->getY();
			x4 = p4->getX(); y4 = p4->getY();

			std::cout<<"-----------------------------"<<std::endl;
			std::cout<<"p1.x : "<<x1<<"\t| p1.y : "<<y1<<std::endl;
			std::cout<<"p2.x : "<<x2<<"\t| p2.y : "<<y2<<std::endl;
			std::cout<<"p3.x : "<<x3<<"\t| p3.y : "<<y3<<std::endl;
			std::cout<<"p4.x : "<<x4<<"\t| p4.y : "<<y4<<std::endl;
			sx = x4 - x3;
			sy = y4 - y3;
			// calculate r*s cross product
			rs = ( rx*sy - ry*sx); // dont care about direction
			// finaly calculate intercepts
			u = (float)((x3-x1)*ry - (y3-y1)*rx)/(float)rs;
			t = (float)((x3-x1)*sy - (y3-y1)*sx)/(float)rs;

			std::cout<<"u : "<<u<<"\t\t| t : "<<t<<std::endl;
			//std::cout<<"rs : "<<rs<<" | rx : "<<rx<<" | ry : "<<ry<<std::endl;
			//std::cout<<"sx : "<<sx<<" | sy : "<<sy<<std::endl;

			// intercept test
			if(u>=0 && u<=1 && t>=0 && t<=1){
				std::cout<<"-------------------------------\n";
				std::cout<<"INF: ray intersection test has succedded\n";
				std::cout<<"-------------------------------"<<std::endl;
				// mark in hit domian edges flag vector
				hitDomainEdges.at(j) = true;
				intersectionCount += 1;
			}
			else{
				std::cout<<"INF: ray intersection tes has failed ..."<<std::endl;
			}
		}
	}
	if(intersectionCount == 0){
		return -1;
	}

	std::cout<<"INF: preliminary ray intersection test succedded : "<<intersectionCount<<" times ..."<<std::endl;
	std::cout<<"INF: performing test result validation ...."<<std::endl;
	// test result validation
	for(int i=0;i<hitDomainEdges.size();i++)
	{
		std::cout<<"INF: domain edge : " <<i+1<<" | hit status flag set to : "<<hitDomainEdges.at(i)<<" ..."<<std::endl;
	}
	if(hitDomainEdges.at(0) == true && hitDomainEdges.at(hitDomainEdges.size()-1) == true){
		intersectionCount -= 1;
	}//further more
	for(int i=1;i<hitDomainEdges.size();i++)
	{
		if(hitDomainEdges.at(i-1) == true && hitDomainEdges.at(i) == true) {
			intersectionCount -= 1;
		}
	}
	std::cout<<"--------------------------------------------------------"<<std::endl;
	std::cout<<"INF: test result validation completed ...."<<std::endl;
	std::cout<<"INF: validated ray intersection count is : "<<intersectionCount<<" times ..."<<std::endl;
	std::cout<<"--------------------------------------------------------"<<std::endl;
	return intersectionCount;
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
