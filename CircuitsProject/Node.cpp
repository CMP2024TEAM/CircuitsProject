#include"Node.h"
Node::Node(int id) :ID(id) {}
void Node::SetID(int id) { ID = id; }
void Node::SetVoltage(complex<double> v) { voltage = v; }
int Node::GetID() { return ID; }
complex<double> Node::GetVoltage() { return voltage; }
