/*************************************************
* ADS Praktikum 2.2
* TreeNode.h
* Erweiterung um Hilfsattribute und -funktionen gestattet, wenn erforderlich.
*************************************************/
#pragma once
#include <string>

using namespace std;

class TreeNode{
	
	private:
		///////////////////////////////////////
		// Ihr Code hier:	
		int NodePosID;
		int NodeID;
		string Name;
		int Alter;
		double Einkommen;
		int PLZ;
		bool red;
		TreeNode* left;
		TreeNode* right;
		//
		////////////////////////////////////
	
	public:
		///////////////////////////////////////
		// Ihr Code hier:
		TreeNode(int _NodePosID, int _NodeID, string _Name, int _Alter, double _Einkommen, int _PLZ);
		int getNodePosID();
		int getNodeID();
		string getName();
		void setName(string _Name);
		int getAlter();
		void setAlter(int _Alter);
		double getEinkommen();
		void setEinkommen(double _Einkommen);
		int getPLZ();
		void setPLZ(int _PLZ);
		TreeNode* getLeft();
		void setLeft(TreeNode* _Left);
		TreeNode* getRight();
		void setRight(TreeNode* _Right);
		void print();
		bool getRed();
		void setRed(bool _red);
		//
		////////////////////////////////////
};
