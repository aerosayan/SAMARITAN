#include "Manager.h"
#include "Elem.h"
#include "Node.h"
#include "Point.h"
#include <fstream>
#include <iostream>

void Manager::readInGeometry(std::string _filepath)
{
	std::ifstream file;
	std::vector<Point*> points;

	file.open(_filepath);

	double x,y;
	points.clear();
	Point* p1,*p2;
	int i =0;
	while(file)
	{
		file >>x>>y;
		if(i==0){
			points.push_back(new Point(x,y));
		}else{
			points.push_back(points.at(i-1));
			points.push_back(new Point(x,y));
		}

		i+=1;
	}
	m_geom.push_back(points);


}
