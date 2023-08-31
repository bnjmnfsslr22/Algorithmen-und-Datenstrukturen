/*************************************************
* ADS Praktikum 2.2
* Tree.h
* Erweiterung um Hilfsattribute und -funktionen gestattet, wenn erforderlich.
*************************************************/
#pragma once
#include <string>
#include "TreeNode.h"
#include "catch.h"

using namespace std;

class Tree {

private:
	///////////////////////////////////////
	// Ihr Code hier:	
	TreeNode* anker;
	int NodeIDCounter = 0;
	//
	////////////////////////////////////	

public:
	///////////////////////////////////////
	// Ihr Code hier:	
	Tree();
	void addNode(string _Name, int _Alter, double _Einkommen, int _PLZ);
	void deleteNode(int _NodePosID);
	bool searchNode(string _name);
	void printAll();
	void printLayout();
	void preorder(TreeNode* ptr);


	//
	////////////////////////////////////
	// friend-Funktionen sind für die Tests erforderlich und müssen unangetastet bleiben! 
	friend TreeNode * get_anker(Tree& TN);
};
