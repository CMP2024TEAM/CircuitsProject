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
	complex<float> voltage;
public:
	void SetID(int);
	void SetVoltage(complex<float>);
	int GetID();
	complex<float> GetVoltage();
	Node(int);
};