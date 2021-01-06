#pragma once
#include"PassiveElements.h"

class Resistance :public PassiveElements
{
public:
	Resistance(Node* StartNd, Node* EndNd, string nm, complex<double>);
	~Resistance();
	virtual complex<double> GetZ();

private:
	complex<double> R;
};

Resistance::Resistance(Node* StartNd, Node* EndNd, string nm, complex<double> r):PassiveElements(StartNd, EndNd, nm)
{
	R = r;
}

complex<double>  Resistance::GetZ()
{
	return R;
}



Resistance::~Resistance()
{
}