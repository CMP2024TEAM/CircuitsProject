#pragma
#include"ActiveElement.h"
class VSRC : public ActiveElement
{
public:
	VSRC(Node* SNode,Node* ENode,string name,complex<double> value);
	~VSRC();
	complex<double> Value;
	int index;
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
	int index;
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
class CCVS : public ActiveElement
{
public:
	CCVS(Node* SNode, Node* ENode, string name,string dname ,double coff, Node* thestart, Node* theend);
	~CCVS();
	
	double Coff;
	Node* Dstart;
	Node* Dend;
	string DName;
	int index;
private:

};
CCVS::CCVS(Node* SNode, Node* ENode, string name, string dname,double coff, Node* thestart, Node* theend) : ActiveElement(SNode, ENode, name)
{
	Coff = coff;
	Dstart = thestart;
	Dend = theend;
	DName = dname;

}
CCVS::~CCVS()
{
}
class CCCS :public ActiveElement
{
public:
	CCCS(Node* SNode, Node* ENode, string name, double coff, Node* thestart, Node* theend);
	~CCCS();
	double Coff;
	Node* Dstart;
	Node* Dend;
private:

};

CCCS::CCCS(Node* SNode, Node* ENode, string name, double coff, Node* thestart, Node* theend):ActiveElement(SNode, ENode, name)
{
	Coff = coff;
	Dstart = thestart;
	Dend = theend;
}

CCCS::~CCCS()
{
}