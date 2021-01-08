#pragma once
#include<Eigen/Dense>
#include<Eigen/sparse>
#include<complex>
#include<iostream>
using namespace std;
using namespace Eigen;
using namespace std::complex_literals;
class Node
{
public:
	int ID;
	complex<double> voltage;
public:
	void SetID(int);
	void SetVoltage(complex<double>);
	int GetID();
	complex<double> GetVoltage();
	Node(int);
};