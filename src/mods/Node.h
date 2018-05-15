#pragma once
#include<vector>
// FILE : Node.h
// INFO : Class for all the elements in the quad tree structure
// Forward declaration
class Elem;
class Point;
// A node in the quad tree. It can be either a parent node(branch) or a leaf node.
class Node : public Elem
{
public:
	//----------------------------------------------
	// Constructor and Destructor methods
	//----------------------------------------------
	// Register the QuadTree root node with _siblingId = 0
	Node(int _siblingId,std::vector<Node*>& _resMan);
	// Register the subsequent childrens of the QuadTree root
	Node(Node* _parent,int _siblingId,std::vector<Node*>& _resMan);

	virtual ~Node();

	//----------------------------------------------
	// Abstract method deabstraction
	//----------------------------------------------
	void setElemType(unsigned int _type){};

	//----------------------------------------------
	// Get methods
	//----------------------------------------------

	// get sibling id
	int getSiblingId(){return m_siblingId;}

	// get the parent node
	Node* getParent(){return m_parent;}

	// get the child nodes
	Node* getChild1(){return m_child1;}
	Node* getChild2(){return m_child2;}
	Node* getChild3(){return m_child3;}
	Node* getChild4(){return m_child4;}

	unsigned int getMeshLevel(){return m_meshLevel;}

	// get child1 node positon
	Point* getPos(){return m_pos;}
	// get bounding box lengths
	double getBoxLength(){return m_boxLength;}
	double getBoxHeight(){return m_boxHeight;}
	// get bounding box
	std::vector<Point*>& getBoundingBox(){return m_boundingBox;}

	// get geometry level of detail
	std::vector<std::vector<Point*> >& getGeomLOD(){return m_geomLOD;}

	//----------------------------------------------
	// Set methods
	//----------------------------------------------
	void setChild1(Node* _child);
	void setChild2(Node* _child);
	void setChild3(Node* _child);
	void setChild4(Node* _child);

	void setPos(Point* _point){m_pos = _point;}

	void setBoundingBox();
	//----------------------------------------------
	// Flag queries
	//----------------------------------------------

	// Whether the node is cut or not?
	bool isCut(){return m_isCut;}


	//----------------------------------------------
	// mesh generation,ray intersection et.al methods
	//----------------------------------------------

	// run geometry LOD generator on multiple geometries
	void genGeomLOD(std::vector<std::vector<Point*> >& _geometries );

	// subdivide the node to create 4 children
	void subdivide();

	// run all intersection tests
	// _edge is the edges fed in one by one to run intersection tests on
	bool runIntersectionTests(std::vector<Point*>& _edge);

private:
	//----------------------------------------------
	// Set methods
	//----------------------------------------------
	void setParent(Elem* _parent);
	void setIsCut(){m_isCut = true;}
	//----------------------------------------------
	// Resource management
	//----------------------------------------------
	// register to resource manager
	void registerToResMan();
	//----------------------------------------------
	// mesh generation,ray intersection et.al methods
	//----------------------------------------------
	// run an intersection test in 2d for the bounding boxes and geometry edges
	int rayBoxIntersectionTest2D(std::vector<Point*>& ,int ,int ,double ,double );

	//----------------------------------------------
	// Data members
	//----------------------------------------------

	// resource manager
	std::vector<Node*>& m_resMan;
	// The identity of the current node amongst its siblings
	// // That is whether it is child 1,2,3 or 4.
	// // If it is 0 then that particular node is the QuadTree root
	// // If it is <0 then it is uninitialized
	int m_siblingId = -1;

	// The parent of this node
	Node* m_parent = nullptr;

	// The children of this node
	// // Either they will be leaf nodes or parent nodes themeselves
	Node* m_child1 = nullptr;
	Node* m_child2 = nullptr;
	Node* m_child3 = nullptr;
	Node* m_child4 = nullptr;

	// The cut status for the node
	bool m_isCut = false;

	// mesh subdivision level
	unsigned int m_meshLevel = -1;

	// node child1 position
	Point* m_pos;
	// node bounding box
	std::vector<Point*> m_boundingBox;

	// geometry level of detail
	// // each of the seperate vectors will store LOD for different geometries
	std::vector<std::vector<Point*> > m_geomLOD;

	// boudning box length and width
	double m_boxLength;
	double m_boxHeight;
};
