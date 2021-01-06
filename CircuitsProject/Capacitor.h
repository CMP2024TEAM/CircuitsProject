#pragma once
#include"PassiveElements.h"

class Capacitor :public PassiveElements
{
public:
	Capacitor(Node* StartNd, Node* EndNd, string nm, double);
	~Capacitor();
	complex<double> GetZ();

private:
	double C;
};

Capacitor::Capacitor(Node* StartNd, Node* EndNd, string nm, double c) :PassiveElements(StartNd, EndNd, nm)
{
	C = c;
}

complex<double>  Capacitor::GetZ()
{
	return ((1.0 / (UI.Omega * C)) * (-1i));
}



Capacitor::~Capacitor()
{
}