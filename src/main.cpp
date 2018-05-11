#include<iostream>
#include "mods/Elem.h"
#include "mods/Node.h"
int main(int argc,char **argv)
{
	Node* n = new Node(0);
	n->subdivide();
	n->getChild2()->subdivide();
	n->getChild2()->getChild3()->subdivide();
	n->getChild3()->subdivide();
	n->delAllChild();
	n->~Node();
	return 0;
}
