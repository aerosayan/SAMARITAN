#include "Manager.h"
#include "Elem.h"
#include "Node.h"
#include "Point.h"
#include <fstream>
#include <iostream>

void Manager::readInGeometry(std::string _filepath)
{
	std::ifstream file;
	// original points and modified points
	std::vector<Point*> orgPoints,modPoints;

	file.open(_filepath.c_str());

	double x,y;
	orgPoints.clear();
	modPoints.clear();
	int i =0;
	while(file)
	{
		file >>x>>y;
		orgPoints.push_back(new Point(x,y));
		i+=1;
	}

	//re order the stuff


	for(int j=1;j<orgPoints.size();j++)
	{
		modPoints.push_back(orgPoints.at(j-1));
		modPoints.push_back(orgPoints.at(j));
	}
	/*
	for(int j=0;j<modPoints.size();j++)
	{
		std::cout<<"x : "<<modPoints.at(j)->getX()<<" | y : "<<modPoints.at(j)->getY()<<std::endl;
	}
	*/

	m_geom.push_back(modPoints);
}
