#pragma
#include"ActiveElement.h"
class VSRC : public ActiveElement
{
public:
	VSRC(Node* SNode,Node* ENode,string name,complex<double> value);
	~VSRC();
	complex<double> Value;
private:

};

VSRC::VSRC(Node* SNode, Node* ENode, string name, complex<double> value) : ActiveElement(SNode,ENode,name)
{
	Value = value;
}

VSRC::~VSRC()
{
}

class ISRC : public ActiveElement
{
public:
	ISRC(Node* SNode, Node* ENode, string name, complex<double> value);
	~ISRC();
	complex<double> Value;
private:
	
};

ISRC::ISRC(Node* SNode, Node* ENode, string name, complex<double> value) : ActiveElement(SNode, ENode, name)
{
	Value = value;
}

ISRC::~ISRC()
{
}
class VCVS : public ActiveElement
{
public:
	VCVS(Node* SNode, Node* ENode, string name,double coff,Node* thestart,Node* theend);
	~VCVS();
	double Coff;
	Node* Dstart;
	Node* Dend;
private:

};
VCVS::VCVS(Node* SNode, Node* ENode, string name, double coff, Node* thestart, Node* theend) : ActiveElement(SNode, ENode, name)
{
	Coff = coff;
	Dstart = thestart;
	Dend = theend;
	

}
VCVS::~VCVS()
{
}
class VCCS : public ActiveElement
{
public:
	VCCS(Node* SNode, Node* ENode, string name, double coff, Node* thestart, Node* theend);
	~VCCS();
	
	double Coff;
	Node* Dstart;
	Node* Dend;
private:

};
VCCS::VCCS(Node* SNode, Node* ENode, string name, double coff, Node* thestart, Node* theend) : ActiveElement(SNode, ENode, name)
{
	Coff = coff;
	Dstart = thestart;
	Dend = theend;
	

}
VCCS::~VCCS()
{
}