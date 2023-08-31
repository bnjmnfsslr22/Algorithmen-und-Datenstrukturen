/*************************************************
* ADS Praktikum 2.2
* TreeNode.cpp
* Erweiterung um Hilfsfunktionen gestattet.
*************************************************/
#include "TreeNode.h"
#include <iostream>
#include <string>
#include <iomanip>


////////////////////////////////////
// Ihr Code hier:
TreeNode::TreeNode(int _NodePosID, int _NodeID, string _Name, int _Alter, double _Einkommen, int _PLZ)
{
	NodePosID = _NodePosID;
	NodeID = _NodeID;
	Name = _Name;
	Alter = _Alter;
	Einkommen = _Einkommen;
	PLZ = _PLZ;
	left = nullptr;
	right = nullptr;
}
int TreeNode::getNodePosID()
{
	return NodePosID;
}
int TreeNode::getNodeID()
{
	return NodeID;
}
string TreeNode::getName()
{
	return Name;
}
void TreeNode::setName(string _Name)
{
	Name = _Name;
}
int TreeNode::getAlter()
{
	return Alter;
}
void TreeNode::setAlter(int _Alter)
{
	Alter = _Alter;
}
double TreeNode::getEinkommen()
{
	return Einkommen;
}
void TreeNode::setEinkommen(double _Einkommen)
{
	Einkommen = _Einkommen;
}
int TreeNode::getPLZ()
{
	return PLZ;
}
void TreeNode::setPLZ(int _PLZ)
{
	PLZ = _PLZ;
}
TreeNode* TreeNode::getLeft()
{
	return left;
}
void TreeNode::setLeft(TreeNode* _Left)
{
	left = _Left;
}
TreeNode* TreeNode::getRight()
{
	return right;
}
void TreeNode::setRight(TreeNode* _Right)
{
	right = _Right;
}
void TreeNode::print()
{
	
	cout << setfill(' ');
	cout << setw(5) << NodeID << " | "  << setw(10) << Name << " | "  << setw(10) << Alter << " | "  << setw(10) << Einkommen << " | "  << setw(5) << PLZ << " | "   << NodePosID << endl;

}


//
////////////////////////////////////
