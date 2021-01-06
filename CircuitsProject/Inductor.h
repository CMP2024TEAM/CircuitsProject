#pragma once
#include"PassiveElements.h"

class Inductor :public PassiveElements
{
public:
	Inductor(Node* StartNd, Node* EndNd, string nm, double);
	~Inductor();
	complex<double> GetZ();

private:
	double H;
};

Inductor::Inductor(Node* StartNd, Node* EndNd, string nm, double h) :PassiveElements(StartNd, EndNd, nm)
{
	H = h;
}

complex<double> Inductor::GetZ()
{
	double z= (UI.Omega * H);
	return (z*(1i));
}



Inductor::~Inductor()
{
}