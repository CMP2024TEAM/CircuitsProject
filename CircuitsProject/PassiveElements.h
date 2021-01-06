#pragma once
#include"Element.h"
class PassiveElements:public Element	
{
public:
	PassiveElements(Node* StartNd, Node* EndNd, string nm);
	~PassiveElements();
	virtual complex<double> GetZ();


protected:
	complex<float> Z;
};

PassiveElements::PassiveElements(Node* StartNd, Node* EndNd, string nm):Element(StartNd, EndNd, nm)
{
}
complex<double> PassiveElements::GetZ()
{
	return Z;
}

PassiveElements::~PassiveElements()
{
}
