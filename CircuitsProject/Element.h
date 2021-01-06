#pragma once
#include"Node.h"
#include"Global.h"

class Element
{
public:
	Element(Node* StartNd, Node* EndNd,string);
	~Element();

protected:
	Node* StartNode;
	Node* EndNode;
	string Name;
	


};

Element::Element(Node* StartNd,Node* EndNd,string nm)
{
	StartNode=StartNd;
	EndNode=EndNd;
	Name = nm;

}

Element::~Element()
{
}