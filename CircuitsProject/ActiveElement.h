#pragma once
#include"Element.h"
class ActiveElement
	:public Element
{
public:
	ActiveElement(Node* StartNd, Node* EndNd, string);
	~ActiveElement();

protected:

};

ActiveElement::ActiveElement(Node* StartNd, Node* EndNd, string nm):Element(StartNd,EndNd,nm)
{
	StartNode = StartNd;
	EndNode = EndNd;
	Name = nm;
}
ActiveElement::~ActiveElement()
{}