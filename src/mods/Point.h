#pragma once
// FILE : Point.h
// INFO : The class for creating point objects for vector calculations

class Point
{
public:
	Point(double _x,double _y):m_x(_x),m_y(_y){}
	virtual ~Point(){}
	//-----------------------------------
	// getter methods
	//-----------------------------------
	double getX(){return m_x;}
	double getY(){return m_y;}
	//-----------------------------------
	// setter methods
	//-----------------------------------
	void setX(double _x){m_x=_x;}
	void setY(double _y){m_y=_y;}
private:
	double m_x;
	double m_y;

};
