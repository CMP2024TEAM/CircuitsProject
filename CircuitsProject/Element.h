#pragma once
#include"Node.h"
#include"Global.h"

class Element
{
public:
	Element(Node* StartNd, Node* EndNd, string);
	virtual ~Element();
	Node* GetStartNode();
	Node* GetEndNode();
	void setStartNode(Node*);
	void setEndNode(Node*);
	string Name;
	complex<double>Current;
protected:
	Node* StartNode;
	Node* EndNode;

};

Element::Element(Node* StartNd, Node* EndNd, string nm)
{
	StartNode = StartNd;
	EndNode = EndNd;
	Name = nm;

}
Node* Element::GetStartNode()
{
	return StartNode;
}
Node* Element::GetEndNode()
{
	return EndNode;
}
void Element::setStartNode(Node* New) {
	StartNode = New;
}
void Element::setEndNode(Node* New)
{
	EndNode = New;
}
Element::~Element()
{
}