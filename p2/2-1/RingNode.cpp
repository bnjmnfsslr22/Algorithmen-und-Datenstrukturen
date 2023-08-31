/*************************************************
* ADS Praktikum 2.1
* RingNode.cpp
* Erweiterung um Hilfsfunktionen gestattet.
*************************************************/
#include "RingNode.h"
using namespace std;

// Ihr Code hier:
RingNode::RingNode()
{
}
RingNode::RingNode(int a, string _descrition, string _data)
{
	OldAge = a;
	Description = _descrition;
	SymbolicData = _data;
}
int RingNode::getAge()
{
	return this->OldAge;
}
void RingNode::setAge(int _age)
{
	this->OldAge = _age;
}
string RingNode::getDescription()
{
	return this->Description;
}
void RingNode::setDescription(string _description)
{
	this->Description = _description;
}
string RingNode::getData()
{
	return this->SymbolicData;
}
void RingNode::setData(string _data)
{
	this->SymbolicData = _data;
}
RingNode* RingNode::getNext()
{
	return this->next;
}
void RingNode::setNext(RingNode* _next)
{
	this->next = _next;
}
// 
////////////////////////////////////