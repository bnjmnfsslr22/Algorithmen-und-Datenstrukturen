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

const bool Black = false;
const bool Red = true;

class Tree {

private:
	///////////////////////////////////////
	// Ihr Code hier:	
	TreeNode* anker;
	int NodeIDCounter =0;
	bool rotateTreeRight(TreeNode* ptr, TreeNode* ptr2);
	bool rotateTreeLeft(TreeNode* ptr, TreeNode* ptr2);
	//
	////////////////////////////////////	

public:
	///////////////////////////////////////
	// Ihr Code hier:	
	Tree();
	void addNode(string _Name, int _Alter, double _Einkommen, int _PLZ);
	void deleteNode(int _NodePosID);
	bool searchNode(string _name);
	void printPreOrder();
	void printLayout();
	void preorder(TreeNode* ptr);
	bool balanceTree();
	void printLevelOrder();
	TreeNode* getParent(int NodePosID);




	//
	////////////////////////////////////
	// friend-Funktionen sind für die Tests erforderlich und müssen unangetastet bleiben! 
	friend TreeNode * get_anker(Tree& TN);
};
