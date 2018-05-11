#pragma once
// FILE : Node.h
// INFO : Class for all the elements in the quad tree structure
// Forward declaration
class Elem;

// A node in the quad tree. It can be either a parent node(branch) or a leaf node.
class Node : public Elem
{
public:
	//----------------------------------------------
	// Constructor and Destructor methods
	//----------------------------------------------
	// Register the QuadTree root node with _siblingId = 0
	Node(int _siblingId);
	// Register the subsequent childrens of the QuadTree root
	Node(Node* _parent,int _siblingId);

	virtual ~Node();

	void delAllChild();

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

	//----------------------------------------------
	// Set methods
	//----------------------------------------------
	void setChild1(Node* _child);
	void setChild2(Node* _child);
	void setChild3(Node* _child);
	void setChild4(Node* _child);

	//----------------------------------------------
	// Flag queries
	//----------------------------------------------

	// Whether the node is cut or not?
	bool isCut(){return m_isCut;}


	//----------------------------------------------
	// Mesh generation and traversal methods
	//----------------------------------------------

	// subdivide the node to create 4 children
	void subdivide();


private:
	//----------------------------------------------
	// Set methods
	//----------------------------------------------
	void setParent(Elem* _parent);

	//----------------------------------------------
	// Data members
	//----------------------------------------------

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
};
