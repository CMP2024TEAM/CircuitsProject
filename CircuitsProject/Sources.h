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

private:
	complex<double> Value;
};

ISRC::ISRC(Node* SNode, Node* ENode, string name, complex<double> value) : ActiveElement(SNode, ENode, name)
{
	Value = value;
}

ISRC::~ISRC()
{
}