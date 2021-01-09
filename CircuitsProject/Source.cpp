﻿#include<Eigen/Dense>
#include<Eigen/sparse>
#include<complex>
#include<iostream>
#include"Global.h"
#include"Element.h"
#include"Resestance.h"
#include"Capacitor.h"
#include"Inductor.h"
#include"Sources.h"
# define M_PI          3.141592653589793238462643383279502884L /* pi */
using namespace std;
using namespace Eigen;
using namespace std::complex_literals;
double ToRadian(double degree)
{
	return degree / 180 * M_PI;
}
double ToDegree(double radian)
{
	return radian / M_PI * 180;
}
bool NodesCreated[10] = { 0 };
PassiveElements** GetAllPassiveWithNode(Element* E[], int size, Node* N, int& countofelements)
{
	countofelements = 0;
	for (int i = 0; i < size; i++)
	{
		PassiveElements* PE = dynamic_cast<PassiveElements*>(E[i]);
		if (PE != NULL)
		{
			if (E[i]->GetEndNode() == N || E[i]->GetStartNode() == N)
			{
				countofelements++;
			}
		}
	}
	PassiveElements** Elements = new PassiveElements * [countofelements];
	int k = 0;
	for (int i = 0; i < size; i++)
	{
		PassiveElements* PE = dynamic_cast<PassiveElements*>(E[i]);
		if (PE != NULL)
		{
			if (E[i]->GetEndNode() == N || E[i]->GetStartNode() == N)
			{
				Elements[k++] = PE;
			}
		}
	}
	return Elements;
}
PassiveElements** GetAllPassiveBetweenNodes(Element* E[], int size, Node* N1, Node* N2, int& countofelements)
{
	countofelements = 0;
	for (int i = 0; i < size; i++)
	{
		PassiveElements* PE = dynamic_cast<PassiveElements*>(E[i]);
		if (PE != NULL)
		{
			if (E[i]->GetEndNode() == N1 && E[i]->GetStartNode() == N2 || E[i]->GetEndNode() == N2 && E[i]->GetStartNode() == N1)
			{
				countofelements++;
			}
		}
	}
	PassiveElements** Elements = new PassiveElements * [countofelements];
	int k = 0;
	for (int i = 0; i < size; i++)
	{
		PassiveElements* PE = dynamic_cast<PassiveElements*>(E[i]);
		if (PE != NULL)
		{
			if (E[i]->GetEndNode() == N1 && E[i]->GetStartNode() == N2 || E[i]->GetEndNode() == N2 && E[i]->GetStartNode() == N1)
			{
				Elements[k++] = PE;
			}
		}
	}
	return Elements;
}
int main()
{
	UI.Omega = 0;
	int n = 0, m = 0;
	string omega;
	getline(cin, omega);
	double o = stod(omega.substr(2, omega.length()));
	UI.Omega = o;
	string s;
	Node* Nodes[20];
	Element* Elements[20];
	int NumberOfElements = 0;
	do
	{
		getline(cin, s);
		string type = "";
		string name = "";
		int i = 0;
		for (; i < s.length(); i++)
		{
			if (s[i] == ' ')
			{
				break;
			}
			type += s[i];
		}
		i++;
		for (; i < s.length(); i++)
		{
			if (s[i] == ' ')
			{
				break;
			}
			name += s[i];
		}
		i++;
		if (type == "vsrc")
		{
			string node1 = "", node2 = "", v = "", phase = "";
			for (; i < s.length(); i++)
			{
				if (s[i] == ' ')
				{
					break;
				}
				node1 += s[i];
			}
			i++;
			for (; i < s.length(); i++)
			{
				if (s[i] == ' ')
				{
					break;
				}
				node2 += s[i];
			}
			i++;
			for (; i < s.length(); i++)
			{
				if (s[i] == ' ')
				{
					break;
				}
				v += s[i];
			}
			i++;
			for (; i < s.length(); i++)
			{
				if (s[i] == ' ')
				{
					break;
				}
				phase += s[i];
			}
			int N1, N2;
			double Value;
			double Phase;
			N1 = (int)stod(node1);
			N2 = (int)stod(node2);
			Value = stod(v);
			Phase = stod(phase);
			complex<double> ComplexValue = polar(Value, ToRadian(Phase));
			if (NodesCreated[N1] == false)
			{
				Nodes[N1] = new Node(N1);
				NodesCreated[N1] = true;
				n++;
			}
			if (NodesCreated[N2] == false)
			{
				Nodes[N2] = new Node(N2);
				NodesCreated[N2] = true;
				n++;
			}
			Elements[NumberOfElements] = new VSRC(Nodes[N1], Nodes[N2], name, ComplexValue);
			NumberOfElements++;
			m++;
		}
		else if (type == "isrc")
		{
			string node1 = "", node2 = "", v = "", phase = "";
			for (; i < s.length(); i++)
			{
				if (s[i] == ' ')
				{
					break;
				}
				node1 += s[i];
			}
			i++;
			for (; i < s.length(); i++)
			{
				if (s[i] == ' ')
				{
					break;
				}
				node2 += s[i];
			}
			i++;
			for (; i < s.length(); i++)
			{
				if (s[i] == ' ')
				{
					break;
				}
				v += s[i];
			}
			i++;
			for (; i < s.length(); i++)
			{
				if (s[i] == ' ')
				{
					break;
				}
				phase += s[i];
			}
			int N1, N2;
			double Value;
			double Phase;
			N1 = (int)stod(node1);
			N2 = (int)stod(node2);
			Value = stod(v);
			Phase = stod(phase);
			complex<double> ComplexValue = polar(Value, ToRadian(Phase));
			if (NodesCreated[N1] == false)
			{
				Nodes[N1] = new Node(N1);
				NodesCreated[N1] = true;
				n++;
			}
			if (NodesCreated[N2] == false)
			{
				Nodes[N2] = new Node(N2);
				NodesCreated[N2] = true;
				n++;
			}
			Elements[NumberOfElements] = new ISRC(Nodes[N1], Nodes[N2], name, ComplexValue);
			NumberOfElements++;

		}
		else if (type == "res")
		{
			string node1 = "", node2 = "", v = "";
			for (; i < s.length(); i++)
			{
				if (s[i] == ' ')
				{
					break;
				}
				node1 += s[i];
			}
			i++;
			for (; i < s.length(); i++)
			{
				if (s[i] == ' ')
				{
					break;
				}
				node2 += s[i];
			}
			i++;
			for (; i < s.length(); i++)
			{
				if (s[i] == ' ')
				{
					break;
				}
				v += s[i];
			}
			int N1, N2;
			double Value;
			double Phase;
			N1 = (int)stod(node1);
			N2 = (int)stod(node2);
			Value = stod(v);
			complex<double> ComplexValue = Value;
			if (NodesCreated[N1] == false)
			{
				Nodes[N1] = new Node(N1);
				NodesCreated[N1] = true;
				n++;
			}
			if (NodesCreated[N2] == false)
			{
				Nodes[N2] = new Node(N2);
				NodesCreated[N2] = true;
				n++;
			}
			Elements[NumberOfElements] = new Resistance(Nodes[N1], Nodes[N2], name, ComplexValue);
			NumberOfElements++;
		}
		else if (type == "cap")
		{
			string node1 = "", node2 = "", v = "";
			for (; i < s.length(); i++)
			{
				if (s[i] == ' ')
				{
					break;
				}
				node1 += s[i];
			}
			i++;
			for (; i < s.length(); i++)
			{
				if (s[i] == ' ')
				{
					break;
				}
				node2 += s[i];
			}
			i++;
			for (; i < s.length(); i++)
			{
				if (s[i] == ' ')
				{
					break;
				}
				v += s[i];
			}
			int N1, N2;
			double Value;
			double Phase;
			N1 = (int)stod(node1);
			N2 = (int)stod(node2);
			Value = stod(v);
			complex<double> ComplexValue = Value;
			if (NodesCreated[N1] == false)
			{
				Nodes[N1] = new Node(N1);
				NodesCreated[N1] = true;
				n++;
			}
			if (NodesCreated[N2] == false)
			{
				Nodes[N2] = new Node(N2);
				NodesCreated[N2] = true;
				n++;
			}
			Elements[NumberOfElements] = new Capacitor(Nodes[N1], Nodes[N2], name, Value);
			NumberOfElements++;
		}
		else if (type == "ind")
		{
			string node1 = "", node2 = "", v = "";
			for (; i < s.length(); i++)
			{
				if (s[i] == ' ')
				{
					break;
				}
				node1 += s[i];
			}
			i++;
			for (; i < s.length(); i++)
			{
				if (s[i] == ' ')
				{
					break;
				}
				node2 += s[i];
			}
			i++;
			for (; i < s.length(); i++)
			{
				if (s[i] == ' ')
				{
					break;
				}
				v += s[i];
			}
			int N1, N2;
			double Value;
			double Phase;
			N1 = (int)stod(node1);
			N2 = (int)stod(node2);
			Value = stod(v);
			complex<double> ComplexValue = Value;
			if (NodesCreated[N1] == false)
			{
				Nodes[N1] = new Node(N1);
				NodesCreated[N1] = true;
				n++;
			}
			if (NodesCreated[N2] == false)
			{
				Nodes[N2] = new Node(N2);
				NodesCreated[N2] = true;
				n++;
			}
			Elements[NumberOfElements] = new Inductor(Nodes[N1], Nodes[N2], name, Value);
			NumberOfElements++;
		}
		else if (type == "vcvs")
		{
			string node1 = "", node2 = "", v = "", node3 = "", node4 = "";
			for (; i < s.length(); i++)
			{
				if (s[i] == ' ')
				{
					break;
				}
				node1 += s[i];
			}
			i++;
			for (; i < s.length(); i++)
			{
				if (s[i] == ' ')
				{
					break;
				}
				node2 += s[i];
			}
			i++;
			for (; i < s.length(); i++)
			{
				if (s[i] == ' ')
				{
					break;
				}
				node3 += s[i];
			}
			i++;
			for (; i < s.length(); i++)
			{
				if (s[i] == ' ')
				{
					break;
				}
				node4 += s[i];
			}
			i++;
			for (; i < s.length(); i++)
			{
				if (s[i] == ' ')
				{
					break;
				}
				v += s[i];
			}
			i++;
			int N1, N2, N3, N4;
			double Value;
			double Phase;
			N1 = (int)stod(node1);
			N2 = (int)stod(node2);
			N3 = (int)stod(node3);
			N4 = (int)stod(node4);
			Value = stod(v);
			if (NodesCreated[N1] == false)
			{
				Nodes[N1] = new Node(N1);
				NodesCreated[N1] = true;
				n++;
			}
			if (NodesCreated[N2] == false)
			{
				Nodes[N2] = new Node(N2);
				NodesCreated[N2] = true;
				n++;
			}
			Elements[NumberOfElements] = new VCVS(Nodes[N1], Nodes[N2], name, Value, Nodes[N3], Nodes[N4]);
			NumberOfElements++;
			m++;

		}
		else if (type == "vccs")
		{
			string node1 = "", node2 = "", v = "", node3 = "", node4 = "";
			for (; i < s.length(); i++)
			{
				if (s[i] == ' ')
				{
					break;
				}
				node1 += s[i];
			}
			i++;
			for (; i < s.length(); i++)
			{
				if (s[i] == ' ')
				{
					break;
				}
				node2 += s[i];
			}
			i++;
			for (; i < s.length(); i++)
			{
				if (s[i] == ' ')
				{
					break;
				}
				node3 += s[i];
			}
			i++;
			for (; i < s.length(); i++)
			{
				if (s[i] == ' ')
				{
					break;
				}
				node4 += s[i];
			}
			i++;
			for (; i < s.length(); i++)
			{
				if (s[i] == ' ')
				{
					break;
				}
				v += s[i];
			}
			i++;
			int N1, N2, N3, N4;
			double Value;
			double Phase;
			N1 = (int)stod(node1);
			N2 = (int)stod(node2);
			N3 = (int)stod(node3);
			N4 = (int)stod(node4);
			Value = stod(v);

			if (NodesCreated[N1] == false)
			{
				Nodes[N1] = new Node(N1);
				NodesCreated[N1] = true;
				n++;
			}
			if (NodesCreated[N2] == false)
			{
				Nodes[N2] = new Node(N2);
				NodesCreated[N2] = true;
				n++;
			}
			Elements[NumberOfElements] = new VCCS(Nodes[N1], Nodes[N2], name, Value, Nodes[N3], Nodes[N4]);
			NumberOfElements++;
		}
		else if (type == "ccvs")
		{
			string node1 = "", node2 = "", v = "", node3 = "", node4 = "", DN = "";
			for (; i < s.length(); i++)
			{
				if (s[i] == ' ')
				{
					break;
				}
				node1 += s[i];
			}
			i++;
			for (; i < s.length(); i++)
			{
				if (s[i] == ' ')
				{
					break;
				}
				node2 += s[i];
			}
			i++;
			for (; i < s.length(); i++)
			{
				if (s[i] == ' ')
				{
					break;
				}
				node3 += s[i];
			}
			i++;
			for (; i < s.length(); i++)
			{
				if (s[i] == ' ')
				{
					break;
				}
				node4 += s[i];
			}
			i++;
			for (; i < s.length(); i++)
			{
				if (s[i] == ' ')
				{
					break;
				}
				DN += s[i];
			}
			i++;
			for (; i < s.length(); i++)
			{
				if (s[i] == ' ')
				{
					break;
				}
				v += s[i];
			}
			int N1, N2, N3, N4;
			double Value;
			double Phase;
			N1 = (int)stod(node1);
			N2 = (int)stod(node2);
			N3 = (int)stod(node3);
			N4 = (int)stod(node4);
			Value = stod(v);
			if (NodesCreated[N1] == false)
			{
				Nodes[N1] = new Node(N1);
				NodesCreated[N1] = true;
				n++;
			}
			if (NodesCreated[N2] == false)
			{
				Nodes[N2] = new Node(N2);
				NodesCreated[N2] = true;
				n++;
			}

			Elements[NumberOfElements] = new CCVS(Nodes[N1], Nodes[N2], name, DN, Value, Nodes[N3], Nodes[N4]);
			NumberOfElements++;
			m++;
		}
		else if (type == "cccs")
		{
			string node1 = "", node2 = "", v = "", node3 = "", node4 = "", DN = "";
			for (; i < s.length(); i++)
			{
				if (s[i] == ' ')
				{
					break;
				}
				node1 += s[i];
			}
			i++;
			for (; i < s.length(); i++)
			{
				if (s[i] == ' ')
				{
					break;
				}
				node2 += s[i];
			}
			i++;
			for (; i < s.length(); i++)
			{
				if (s[i] == ' ')
				{
					break;
				}
				node3 += s[i];
			}
			i++;
			for (; i < s.length(); i++)
			{
				if (s[i] == ' ')
				{
					break;
				}
				node4 += s[i];
			}
			i++;
			for (; i < s.length(); i++)
			{
				if (s[i] == ' ')
				{
					break;
				}
				DN += s[i];
			}
			i++;
			for (; i < s.length(); i++)
			{
				if (s[i] == ' ')
				{
					break;
				}
				v += s[i];
			}
			int N1, N2, N3, N4;
			double Value;
			double Phase;
			N1 = (int)stod(node1);
			N2 = (int)stod(node2);
			N3 = (int)stod(node3);
			N4 = (int)stod(node4);
			Value = stod(v);
			if (NodesCreated[N1] == false)
			{
				Nodes[N1] = new Node(N1);
				NodesCreated[N1] = true;
				n++;
			}
			if (NodesCreated[N2] == false)
			{
				Nodes[N2] = new Node(N2);
				NodesCreated[N2] = true;
				n++;
			}

			Elements[NumberOfElements] = new CCCS(Nodes[N1], Nodes[N2], name, DN, Value, Nodes[N3], Nodes[N4]);
			NumberOfElements++;
		}
	} while (s != "");
	int ActualNumberOfElements = NumberOfElements;
	UI.NumberofActualNodes = n;
	for (int l = 0; l < NumberOfElements; l++)
	{
		CCVS* batr = dynamic_cast<CCVS*> (Elements[l]);
		if (batr != NULL)
			for (int k = 0; k < NumberOfElements; k++)
				if (Elements[k]->Name == batr->DName)
				{
					VSRC* batar1 = dynamic_cast<VSRC*>(Elements[k]);
					CCVS* batar2 = dynamic_cast<CCVS*>(Elements[k]);
					VCVS* batar3 = dynamic_cast<VCVS*>(Elements[k]);
					if (batar1 == NULL && batar2 == NULL && batar3 == NULL)
					{

						Nodes[n] = new Node(n);
						Elements[NumberOfElements] = new VSRC(Elements[k]->GetStartNode(), Nodes[n], Elements[k]->Name + "src", 0.0);
						Elements[k]->setStartNode(Nodes[n]);
						batr->DName = Elements[NumberOfElements]->Name;
						NumberOfElements++;
						m++;
						n++;

					}
				}
		CCCS* batr1 = dynamic_cast<CCCS*> (Elements[l]);
		if (batr1 != NULL)
			for (int k = 0; k < NumberOfElements; k++)
				if (Elements[k]->Name == batr1->DName)
				{
					VSRC* batar1 = dynamic_cast<VSRC*>(Elements[k]);
					CCVS* batar2 = dynamic_cast<CCVS*>(Elements[k]);
					VCVS* batar3 = dynamic_cast<VCVS*>(Elements[k]);
					if (batar1 == NULL && batar2 == NULL && batar3 == NULL)
					{

						Nodes[n] = new Node(n);
						Elements[NumberOfElements] = new VSRC(Elements[k]->GetStartNode(), Nodes[n], Elements[k]->Name + "src", 0.0);
						Elements[k]->setStartNode(Nodes[n]);
						batr1->DName = Elements[NumberOfElements]->Name;
						NumberOfElements++;
						m++;
						n++;

					}
				}
	}
	MatrixXcd G(n - 1, n - 1);
	MatrixXcd B(n - 1, m);
	MatrixXcd C(m, n - 1);
	MatrixXcd D(m, m);
	MatrixXcd i(n - 1, 1);
	MatrixXcd e(m, 1);
	i.setZero();
	e.setZero();
	G.setZero();
	B.setZero();
	C.setZero();
	D.setZero();
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i; j < n - 1; j++)
		{
			if (i == j)
			{
				int count;
				PassiveElements** E = GetAllPassiveWithNode(Elements, NumberOfElements, Nodes[i + 1], count);
				for (int k = 0; k < count; k++)
				{
					G(i, j) += 1.0 / E[k]->GetZ();
				}
			}
			else
			{
				int count;
				PassiveElements** E = GetAllPassiveBetweenNodes(Elements, NumberOfElements, Nodes[j + 1], Nodes[i + 1], count);
				for (int k = 0; k < count; k++)
				{
					G(i, j) -= 1.0 / E[k]->GetZ();
					G(j, i) -= 1.0 / E[k]->GetZ();
				}
			}
		}
	}
	int Batterycount = 0;
	for (int i = 0; i < NumberOfElements; i++)
	{
		VSRC* Ba = dynamic_cast<VSRC*>(Elements[i]);
		if (Ba != NULL)
		{
			if (Ba->GetStartNode()->GetID() != 0)
			{
				B(Ba->GetStartNode()->GetID() - 1, Batterycount) += 1.0;
				C(Batterycount, Ba->GetStartNode()->GetID() - 1) += 1.0;
			}
			if (Ba->GetEndNode()->GetID() != 0)
			{
				B(Ba->GetEndNode()->GetID() - 1, Batterycount) += -1.0;
				C(Batterycount, Ba->GetEndNode()->GetID() - 1) += -1.0;
			}
			e(Batterycount, 0) = Ba->Value;
			Ba->index = Batterycount;
			Batterycount++;
		}
		VCVS* Bat = dynamic_cast<VCVS*>(Elements[i]);
		if (Bat != NULL)
		{
			if (Bat->GetStartNode()->GetID() != 0)
			{
				B(Bat->GetStartNode()->GetID() - 1, Batterycount) += 1.0;
				C(Batterycount, Bat->GetStartNode()->GetID() - 1) += 1.0;
			}
			if (Bat->GetEndNode()->GetID() != 0)
			{
				B(Bat->GetEndNode()->GetID() - 1, Batterycount) += -1.0;
				C(Batterycount, Bat->GetEndNode()->GetID() - 1) += -1.0;
			}
			if (Bat->Dstart->ID != 0)
			{
				C(Batterycount, Bat->Dstart->ID - 1) -= Bat->Coff;
			}
			if (Bat->Dend->ID != 0)
			{
				C(Batterycount, Bat->Dend->ID - 1) += Bat->Coff;
			}
			e(Batterycount, 0) = 0;
			Bat->index = Batterycount;
			Batterycount++;
		}
		CCVS* Bate = dynamic_cast<CCVS*>(Elements[i]);
		if (Bate != NULL)
		{
			if (Bate->GetStartNode()->GetID() != 0)
			{
				int x = Bate->GetStartNode()->GetID() - 1;
				B(x, Batterycount) += 1.0;
				C(Batterycount, Bate->GetStartNode()->GetID() - 1) += 1.0;
			}
			if (Bate->GetEndNode()->GetID() != 0)
			{
				B(Bate->GetEndNode()->GetID() - 1, Batterycount) += -1.0;
				C(Batterycount, Bate->GetEndNode()->GetID() - 1) += -1.0;
			}
			e(Batterycount, 0) = 0;
			Bate->index = Batterycount;
			Batterycount++;
		}

	}
	for (int j = 0; j < NumberOfElements; j++)
	{
		ISRC* Ba = dynamic_cast<ISRC*>(Elements[j]);
		if (Ba != NULL)
		{
			if (Ba->GetStartNode()->GetID() != 0)
			{
				i(Ba->GetStartNode()->GetID() - 1, 0) += Ba->Value;
			}
			if (Ba->GetEndNode()->GetID() != 0)
			{
				i(Ba->GetEndNode()->GetID() - 1, 0) -= Ba->Value;
			}
		}
		CCCS* Bater = dynamic_cast<CCCS*>(Elements[j]);
		if (Bater != NULL)
		{
			for (int js = 0; js < NumberOfElements; js++)
				if (Bater->DName == Elements[js]->Name)
				{
					if (Bater->GetStartNode()->GetID() != 0)
					{
						VSRC* Vsrc1 = dynamic_cast<VSRC*>(Elements[js]);
						if (Vsrc1 != NULL)
						{
							B(Bater->GetStartNode()->GetID() - 1, Vsrc1->index) -= Bater->Coff;
						}
						VCVS* Vsrc2 = dynamic_cast<VCVS*>(Elements[js]);
						if (Vsrc2 != NULL)
						{
							B(Bater->GetStartNode()->GetID() - 1, Vsrc2->index) -= Bater->Coff;
						}
						CCVS* Vsrc3 = dynamic_cast<CCVS*>(Elements[js]);
						if (Vsrc3 != NULL)
						{
							B(Bater->GetStartNode()->GetID() - 1, Vsrc3->index) -= Bater->Coff;
						}
					}
					if (Bater->GetEndNode()->GetID() != 0)
					{
						VSRC* Vsrc1 = dynamic_cast<VSRC*>(Elements[js]);
						if (Vsrc1 != NULL)
						{
							B(Bater->GetEndNode()->GetID() - 1, Vsrc1->index) += Bater->Coff;
						}
						VCVS* Vsrc2 = dynamic_cast<VCVS*>(Elements[js]);
						if (Vsrc2 != NULL)
						{
							B(Bater->GetEndNode()->GetID() - 1, Vsrc2->index) += Bater->Coff;
						}
						CCVS* Vsrc3 = dynamic_cast<CCVS*>(Elements[js]);
						if (Vsrc3 != NULL)
						{
							B(Bater->GetEndNode()->GetID() - 1, Vsrc3->index) += Bater->Coff;
						}
					}
				}
		}
	}
	for (int k = 0; k < NumberOfElements; k++) //Fill D Elements
	{
		CCVS* Bate = dynamic_cast<CCVS*>(Elements[k]);
		if (Bate != NULL)
		{
			for (int l = 0; l < NumberOfElements; l++)
			{
				if (Bate->DName == Elements[l]->Name)
				{
					VSRC* v1 = dynamic_cast<VSRC*>(Elements[l]);
					if (v1)
					{
						D(Bate->index, v1->index) -= Bate->Coff;
					}
					else
					{
						VCVS* v2 = dynamic_cast<VCVS*>(Elements[l]);
						D(Bate->index, v2->index) -= Bate->Coff;
					}
				}
			}
		}
	}
	//C = B.transpose();
	MatrixXcd A(n - 1 + m, n - 1 + m);
	A << G, B, C, D;
	MatrixXcd z(n - 1 + m, 1);
	z << i, e;
	MatrixXcd Result = A.inverse() * z;
	cout << Result << endl;
	Nodes[0]->SetVoltage(0);
	for (int i = 0; i < n - 1; i++)
	{
		if (Nodes[i + 1] != NULL)
		{
			Nodes[i + 1]->SetVoltage(Result(i, 0));
		}
	}
	for (int i = 0; i < UI.NumberofActualNodes; i++)
	{
		if (Nodes[i] != NULL)
		{
			cout << "The Voltage At Node " << i << " Equals " << abs(Nodes[i]->GetVoltage()) << " < " << ToDegree(arg(Nodes[i]->GetVoltage())) << endl;
		}
	}
	for (int i = 0; i < ActualNumberOfElements; i++)
	{
		PassiveElements* Pa = dynamic_cast<PassiveElements*>(Elements[i]);
		if (Pa != NULL)
		{
			Elements[i]->Current = (Elements[i]->GetStartNode()->GetVoltage() - Elements[i]->GetEndNode()->GetVoltage()) / Pa->GetZ();
			cout << "The Current Passing in Element " << Elements[i]->Name << " Equals " << abs(Elements[i]->Current) << " < " << ToDegree(arg(Elements[i]->Current)) << endl;
		}
	}
	for (int i = 0; i < ActualNumberOfElements; i++)
	{
		VSRC* V1 = dynamic_cast<VSRC*>(Elements[i]);
		if (V1 != NULL)
		{
			Elements[i]->Current = Result(V1->index + n - 1, 0);
			cout << "The Current Passing in Element " << Elements[i]->Name << " Equals " << abs(Elements[i]->Current) << " < " << ToDegree(arg(Elements[i]->Current)) << endl;
		}
		VCVS* V2 = dynamic_cast<VCVS*>(Elements[i]);
		if (V2 != NULL)
		{
			Elements[i]->Current = Result(V2->index + n - 1, 0);
			cout << "The Current Passing in Element " << Elements[i]->Name << " Equals " << abs(Elements[i]->Current) << " < " << ToDegree(arg(Elements[i]->Current)) << endl;
		}
		CCVS* V3 = dynamic_cast<CCVS*>(Elements[i]);
		if (V3 != NULL)
		{
			Elements[i]->Current = Result(V3->index + n - 1, 0);
			cout << "The Current Passing in Element " << Elements[i]->Name << " Equals " << abs(Elements[i]->Current) << " < " << ToDegree(arg(Elements[i]->Current)) << endl;
		}
		ISRC* I1 = dynamic_cast<ISRC*>(Elements[i]);
		if (I1 != NULL)
		{
			Elements[i]->Current = I1->Value;
			cout << "The Current Passing in Element " << Elements[i]->Name << " Equals " << abs(Elements[i]->Current) << " < " << ToDegree(arg(Elements[i]->Current)) << endl;
		}

	}
	for (int ic = ActualNumberOfElements; ic < NumberOfElements; ic++)//get new current
	{
		VSRC* V1 = dynamic_cast<VSRC*>(Elements[ic]);
		if (V1 != NULL)
		{
			Elements[ic]->Current = Result(V1->index + n - 1, 0);
		}
	}
	for (int i = 0; i < ActualNumberOfElements; i++)//set current in branch of VCCS and CCCS 
	{
		VCCS* C1 = dynamic_cast<VCCS*>(Elements[i]);
		if (C1 != NULL)
		{
			Elements[i]->Current = (C1->Dstart->GetVoltage() - C1->Dend->GetVoltage()) * C1->Coff;
			cout << "The Current Passing in Element " << Elements[i]->Name << " Equals " << abs(Elements[i]->Current) << " < " << ToDegree(arg(Elements[i]->Current)) << endl;
		}
		CCCS* C2 = dynamic_cast<CCCS*>(Elements[i]);
		if (C2 != NULL)
		{
			for (int ic = 0; ic < NumberOfElements; ic++)
				if (Elements[ic]->Name == C2->DName)
				{
					Elements[i]->Current = Elements[ic]->Current * C2->Coff;
					cout << "The Current Passing in Element " << Elements[i]->Name << " Equals " << abs(Elements[i]->Current) << " < " << ToDegree(arg(Elements[i]->Current)) << endl;
				}
		}
	}
	return 0;
}
/*
w 0
vsrc v1 2 1 2 0
isrc i1 1 0 2 0
isrc i2 0 2 7 0
res r1 1 2 10
res r2 0 1 2
res r3 0 2 4

(-7.33333,0)
(-5.33333,0)
(-5.86667,0)
*/
/*
w 1
vsrc v1 1 0 10 -45
vsrc v2 3 0 5 -60
cap c1 2 0 1
res r1 1 2 3
ind n1 2 3 1‏

(7.07107,-7.07107)
(-5.91931,-14.5711)
	 (2.5,-4.33013)
	(-4.33013,-2.5)
 (-10.2409,8.41931)
*/
/*
W 0
res r1 1 0 2
vsrc v1 1 2 20 0
isrc i1 2 0 10 0
res r2 2 0 4
res r3 1 3 2
res r4 3 0 1
vcvs v2 2 3 1 3 2‏*/
/*
W 2
res r1 0 1 2
res r2 2 3 4
ind i3 2 0 2
isrc i1 1 0 10 -90
cap c1 1 2 0.2
vcvs v1 3 0 1 0 3
*/
/*
W 0
res r1 1 2 2
res r2 0 2 1
res r3 2 3 8
res r4 1 3 4
isrc i1 1 0 3 0
vccs v1 3 0 1 2 2
*/
/*
W 0
res r1 1 2 2
res r2 0 2 1
res r3 1 3 4
res r4 2 3 8
isrc i1 0 1 3 0
ccvs c1 0 3 1 2 2
*/
/*
W 0
res r1 1 2 2
res r2 0 2 1
res r3 1 3 4
res r4 2 3 8
isrc i1 0 1 3 0
cccs c1 0 3 1 2 2
*/
/*
input
w 0
/*
w 0
vsrc V1 1 0 12 0
res R1 1 2 1000
res R2 2 0 1000
res R3 3 0 1000
ccvs Ha 3 2 1 0 V1 5‏


final answer
(12,0)
(4.01331,0)
(3.97338,0)
(-0.00798669,0)
(-0.00397338,0)
*/
/*
W 0
res r1 1 2 2
res r2 0 2 1
res r3 1 3 4
res r4 2 3 8
isrc i1 1 0 3 0
ccvs c1 3 0 1 2 r1 2

final answer
 (7.30435,0)
  (2.6087,0)
 (4.69565,0)
 (7.30435,0)
(0.391304,0)
 (2.34783,0)
*/
/*
w 0
vsrc V1 1 0 12 0
res R1 1 2 1000
res R2 2 0 1000
res R3 3 0 1000
cccs Fa 3 2 1 0 V1 5
*/
/*
w 1000
vsrc v1 1 0 10 0
res r1 1 2 20
res r2 2 0 20
cap c1 2 3 0.00005
cccs i1 0 3 0 2 r2 4
ind l1 3 4 0.01
res r3 4 0 30

final answer

(10,0)
(1.43564,-0.643564)
(0.148515,6.48515)
(2.07921,5.79208)
(1.43564,-0.643564)
(-0.428218,-0.0321782)
(0.0717822,-0.0321782)
*/
/*
w 1000
vsrc vs 1 0 10 30
ind L1 1 2 .001
cap C2 2 3 0.0001
res R3 3 0 10

*/
/*
w 0
res r1 0 1 10
vsrc v1 1 0 10 0
*/
/*
w 0
res r1 2 1 10
res r2 3 1 24
res r3 3 2 4
res r4 0 2 12
vsrc v 1 0 24 0
ccvs v2 3 0 2 1 r1 4
*/
/*w 0
res r1 1 2 40000
res r2 2 3 10000
res r3 4 0 5000
res r4 3 0 5000‏
vsrc v1 1 0 5 0
vsrc v2 3 4 3 0
ccvs v3 2 4 1 0 v1 10
*/