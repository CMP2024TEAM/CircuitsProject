#include"Node.h"
Node::Node(int id) :ID(id) {}
void Node::SetID(int id) { ID = id; }
void Node::SetVoltage(complex<float> v) { voltage = v; }
int Node::GetID() { return ID; }
complex<float> Node::GetVoltage() { return voltage; }
