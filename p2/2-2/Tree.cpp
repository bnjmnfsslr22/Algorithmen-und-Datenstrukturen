/*************************************************
* ADS Praktikum 2.2
* Tree.cpp
* Erweiterung um Hilfsfunktionen gestattet.
*************************************************/
#include "Tree.h"
#include "TreeNode.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>

using namespace std;

////////////////////////////////////
// Ihr Code hier:
Tree::Tree()
{
	anker = nullptr;
}

void Tree::addNode(string _Name, int _Alter, double _Einkommen, int _PLZ)
{
	int _NodePosID = _Alter + _PLZ + _Einkommen;

	int _NodeID = NodeIDCounter;
	NodeIDCounter++;
	TreeNode* neu = new TreeNode(_NodePosID, _NodeID, _Name, _Alter, _Einkommen, _PLZ);
	if (anker == nullptr)
	{
		anker = neu;
	}
	else
	{
		TreeNode* tmp = anker;
		while (true)
		{
			if (_NodePosID < tmp->getNodePosID())
			{
				if (tmp->getLeft() != nullptr)
				{
					tmp = tmp->getLeft();
				}
				else
				{
					tmp->setLeft(neu);
					break;
				}
			}
			else if (_NodePosID > tmp->getNodePosID())
			{
				if (tmp->getRight() != nullptr)
				{
					tmp = tmp->getRight();
				}
				else
				{
					tmp->setRight(neu);
					break;
				}
			}
		}
	}
}

void Tree::deleteNode(int _NodePosID)
{
	TreeNode* tmp = anker;
	TreeNode* tmp2 = anker;
	//Wurzel ist zu löschende Node
	if (tmp->getNodePosID() == _NodePosID)
	{
		if (tmp->getRight() != nullptr)
		{
			tmp = tmp->getRight();

			while (tmp->getLeft() != nullptr)
			{
				if (tmp->getLeft() != nullptr)
				{
					tmp2 = tmp;
					tmp = tmp->getLeft();
				}
			}

			if (tmp2 == anker)
			{
				tmp->setLeft(tmp2->getLeft());
				delete tmp2;
				anker = tmp;
			}
			else
			{
				tmp2->setLeft(tmp->getRight());
				tmp->setRight(anker->getRight());
				tmp->setLeft(anker->getLeft());
				delete anker;
				anker = tmp;
			}
		}
		else if (tmp->getLeft() != nullptr && tmp->getRight() == nullptr && anker->getNodePosID() == _NodePosID)
		{
			tmp = tmp->getLeft();

			while (tmp->getRight() != nullptr)
			{
				if (tmp->getRight() != nullptr)
				{
					tmp2 = tmp;
					tmp = tmp->getRight();
				}
			}

			if (tmp2 == anker)
			{
				delete tmp2;
				anker = tmp;
			}
			else
			{
				tmp2->setRight(tmp->getLeft());
				tmp->setLeft(anker->getLeft());
				delete anker;
				anker = tmp;
			}
		}
		else if (tmp->getRight() == nullptr && tmp->getLeft() == nullptr && anker->getNodePosID() == _NodePosID)
		{
			delete tmp;
			anker = nullptr;
		}
	}
	//Suche nach der Node tmp2 zeigt auf den Vorgänger tmp auf die zu loeschende Node
	else
	{
		while (tmp != nullptr)
		{
			if (tmp->getNodePosID() != _NodePosID)
				tmp2 = tmp;
			else
				break;

			if (tmp->getNodePosID() > _NodePosID)
				tmp = tmp->getLeft();
			else if (tmp->getLeft()->getNodePosID() < _NodePosID)
				tmp = tmp->getRight();
		}
	}
	//Keine Nachfolger
	if (tmp->getLeft() == nullptr && tmp->getRight() == nullptr && tmp->getNodePosID() == _NodePosID)
	{
		if (tmp2->getLeft() == tmp)
			tmp2->setLeft(nullptr);
		else
			tmp2->setRight(nullptr);
		delete tmp;
	}
	//Nur ein Nachfolger
	else if (tmp->getRight() != nullptr && tmp->getLeft() == nullptr && _NodePosID == tmp->getNodePosID() || tmp->getRight() == nullptr && tmp->getLeft() != nullptr && _NodePosID == tmp->getNodePosID())
	{
		if (tmp2->getLeft() == tmp)
		{
			if (tmp->getRight() != nullptr)
			{
				tmp2->setLeft(tmp->getRight());
				delete tmp;
			}
			else
			{
				tmp2->setLeft(tmp->getLeft());
				delete tmp;
			}
		}
		else
		{
			if (tmp->getRight() != nullptr)
			{
				tmp2->setRight(tmp->getRight());
				delete tmp;
			}
			else
			{
				tmp2->setRight(tmp->getLeft());
				delete tmp;
			}
		}
	}
	//Zwei Nachfolger
	else if (tmp->getRight() != nullptr && tmp->getLeft() != nullptr && tmp->getNodePosID() == _NodePosID)
	{
		TreeNode* tmp3 = tmp2;
		tmp = tmp->getRight();

		while (tmp->getLeft() != nullptr)
		{
			if (tmp->getLeft() != nullptr)
			{
				tmp2 = tmp;
				tmp = tmp->getLeft();
			}
		}
			tmp2->setLeft(tmp->getRight());
			tmp->setRight(tmp3->getRight()->getRight());
			tmp->setLeft(tmp3->getRight()->getLeft());
			delete tmp3->getRight();
			tmp3->setRight(tmp);

	}
}

//Iterativ Besser da eventuell Stack overflow bei grossen datensätzen! Und keine andere Wahl da kein PTR übergeben
bool Tree::searchNode(string _name)
{
	TreeNode* tmp = anker;
	int counter = 0;
	printLayout();

	queue<TreeNode*> q;
	if (tmp != nullptr)
	{
		q.push(tmp);
	}
	while (!q.empty())
	{
		tmp = q.front();
		q.pop();
		if (tmp->getName() == _name)
		{
			tmp->print();
			counter++;
		}
		if (tmp->getLeft() != nullptr)
			q.push(tmp->getLeft());
		if (tmp->getRight() != nullptr)
			q.push(tmp->getRight());
	}
	if (counter > 0)
		return true;
	else
		return false;
}
void Tree::printAll()
{
	printLayout();
	preorder(anker);
}
void Tree::printLayout()
{
	cout << setfill(' ');
	cout << setw(5) << "ID" << " | " << setw(10) << "Name" << " | " << setw(10) << "Alter" << " | " << setw(10) << "Einkommen" << " | " << setw(5) << "PLZ" << " | " << "Pos" << endl;
	cout << setfill('-');
	cout << setw(5) << "-" << "-+-" << setw(10) << "-" << "-+-" << setw(10) << "-" << "-+-" << setw(10) << "-" << "-+-" << setw(5) << "-" << "-+-" << setw(10) << "-" << endl;
}
void Tree::preorder(TreeNode* ptr)
{
	if (ptr != nullptr)
	{
		ptr->print();
		preorder(ptr->getLeft());
		preorder(ptr->getRight());
	}
}
//
////////////////////////////////////