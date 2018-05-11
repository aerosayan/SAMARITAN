#pragma once
// FILE : Elem.h
// INFO : Elementary class type for computational elements from which all other
// 		objects will be derived

class Elem
{
public:
	virtual void setElemType(unsigned int _type) = 0;
private:


};
