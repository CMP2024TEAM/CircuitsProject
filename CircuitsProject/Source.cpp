#include<Eigen/Dense>
#include<Eigen/sparse>
#include<complex>
#include<iostream>
#include"Global.h"
#include"Element.h"
#include"Resestance.h"
#include"Sources.h"
# define M_PI          3.141592653589793238462643383279502884L /* pi */
using namespace std;
using namespace Eigen;
using namespace std::complex_literals;
double ToRadian(double degree)
{
	return degree / 180 * M_PI;
}
bool NodesCreated[10] = {0};
PassiveElements** GetAllPassiveWithNode(Element* E[], int size, Node *N, int &countofelements)
{
	countofelements = 0;
	for (int i = 0;i < size;i++)
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
	for (int i = 0;i < size;i++)
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
PassiveElements** GetAllPassiveBetweenNodes(Element* E[], int size, Node* N1,Node*N2, int& countofelements)
{
	countofelements = 0;
	for (int i = 0;i < size;i++)
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
	for (int i = 0;i < size;i++)
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
	double o = stod(omega.substr(2,omega.length()));
	UI.Omega = o;
	string s;
	Node* Nodes[10];
	Element* Elements[11];
	int NumberOfElements = 0;
	do
	{
		getline(cin, s);
		string type = "";
		string name = "";
		int i = 0;
		for (;i < s.length();i++)
		{
			if (s[i] == ' ')
			{
				break;
			}
			type += s[i];
		}
		i++;
		for (;i < s.length();i++)
		{
			if (s[i] == ' ')
			{
				break;
			}
			name += s[i];
		}
		i++;
		if (type=="vsrc")
		{
			string node1="", node2="", v="", phase="";
			for (;i < s.length();i++)
			{
				if (s[i] == ' ')
				{
					break;
				}
				node1 += s[i];
			}
			i++;
			for (;i < s.length();i++)
			{
				if (s[i] == ' ')
				{
					break;
				}
				node2 += s[i];
			}
			i++;
			for (;i < s.length();i++)
			{
				if (s[i] == ' ')
				{
					break;
				}
				v += s[i];
			}
			i++;
			for (;i < s.length();i++)
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
			Elements[NumberOfElements] = new VSRC(Nodes[N1],Nodes[N2],name,ComplexValue);
			NumberOfElements++;
			m++;
		}
		else if (type=="isrc")
		{

		}
		else if (type=="res")
		{
			string node1 = "", node2 = "", v = "";
			for (;i < s.length();i++)
			{
				if (s[i] == ' ')
				{
					break;
				}
				node1 += s[i];
			}
			i++;
			for (;i < s.length();i++)
			{
				if (s[i] == ' ')
				{
					break;
				}
				node2 += s[i];
			}
			i++;
			for (;i < s.length();i++)
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
		else if (type=="cap")
		{

		}
		else if (type == "ind")
		{

		}
		else if (type == "vcvs")
		{

		}
		else if (type == "vccs")
		{

		}
		else if (type == "ccvs")
		{

		}
		else if (type == "cccs")
		{

		}
	} while (s != "");
	MatrixXcd G (n-1, n-1);
	MatrixXcd B (n-1, m);
	MatrixXcd C (m, n-1);
	MatrixXcd D (m, m);
	MatrixXcd i(n - 1, 1);
	MatrixXcd e(m, 1);
	i.setZero();
	e.setZero();
	G.setZero();
	B.setZero();
	C.setZero();
	D.setZero();
	for (int i = 0;i < n-1;i++)
	{
		for (int j = i;j < n-1;j++)
		{
			if (i==j)
			{
				int count;
				PassiveElements** E = GetAllPassiveWithNode(Elements,NumberOfElements,Nodes[i+1],count);
				for (int k = 0;k < count;k++)
				{
					G(i, j) += 1.0 / E[k]->GetZ();
				}
			}
			else
			{
				int count;
				PassiveElements** E = GetAllPassiveBetweenNodes(Elements, NumberOfElements, Nodes[j+1],Nodes[i+1], count);
				for (int k = 0;k < count;k++)
				{
					G(i, j) -= 1.0 / E[k]->GetZ();
					G(j, i) -= 1.0 / E[k]->GetZ();
				}
			}
		}
	}
	int Batterycount = 0;
	for (int i = 0;i < NumberOfElements;i++)
	{
		VSRC* Ba = dynamic_cast<VSRC*>(Elements[i]);
		if (Ba!=NULL)
		{
			if (Ba->GetStartNode()->GetID() != 0)
			{
				B(Ba->GetStartNode()->GetID() - 1, Batterycount) = 1.0;
			}
			if (Ba->GetEndNode()->GetID() != 0)
			{
				B(Ba->GetEndNode()->GetID() - 1, Batterycount) = -1.0;
			}
			e(Batterycount, 0) = Ba->Value;
			Batterycount++;
		}
	}
	C = B.transpose();
	MatrixXcd A(n - 1 + m, n - 1 + m);
	A << G, B, C, D;
	MatrixXcd z(n - 1 + m, 1);
	z << i, e;
	cout << A.inverse() * z << endl;
	return 0;
}