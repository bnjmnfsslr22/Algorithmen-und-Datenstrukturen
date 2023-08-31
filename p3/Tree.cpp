/*************************************************
* ADS Praktikum 2.2
* Tree.cpp
* Erweiterung um Hilfsfunktionen gestattet.
*************************************************/
#include "Tree.h"
#include "TreeNode.h"
#include <iostream>
#include <iomanip>
#include <queue>

using namespace std;

//
//Hilfsfunktion für das finden des Parent für iterative Lösung da weniger Hardwareheavy
////////////////////////////////////
// Ihr Code hier:
Tree::Tree()
{
	anker = nullptr;
}

TreeNode* Tree::getParent(int _NodePosID)
{
	TreeNode* tmp = anker;

	if (tmp->getNodePosID() == _NodePosID)
	{
		return anker;
	}
	while (tmp != nullptr)
	{
		if (tmp->getNodePosID() < _NodePosID)
		{
			if (tmp->getRight() != nullptr)
			{
				if (tmp->getRight()->getNodePosID() == _NodePosID)
				{
					return tmp;
				}
			}
			tmp = tmp->getRight();
		}
		else
		{

			if (tmp->getLeft() != nullptr)
			{
				if (tmp->getLeft()->getNodePosID() == _NodePosID)
				{
					return tmp;
				}
			}
			tmp = tmp->getLeft();
		}
	}
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
		neu->setRed(Black);
	}
	else
	{
		TreeNode* tmp = anker;
		while (true)
		{
			if (tmp->getLeft() != nullptr && tmp->getRight() != nullptr && tmp->getLeft()->getRed() && tmp->getRight()->getRed())
			{
				tmp->setRed(Red);
				tmp->getRight()->setRed(Black);
				tmp->getLeft()->setRed(Black);
				anker->setRed(Black);
			}
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
	balanceTree();
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
		if (tmp2 == tmp3)
		{
			tmp->setLeft(tmp2->getRight()->getLeft());
			delete tmp2->getRight();
			tmp3->setRight(tmp);
		}
		else
		{
			tmp2->setLeft(tmp->getRight());
			tmp->setRight(tmp3->getRight()->getRight());
			tmp->setLeft(anker->getRight()->getLeft());
			delete tmp3->getRight();
			tmp3->setRight(tmp);
		}

	}
}

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
		{
			q.push(tmp->getLeft());
		}
		if (tmp->getRight() != nullptr)
		{
			q.push(tmp->getRight());
		}
	}
	if (counter > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Tree::printPreOrder()
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

bool Tree::rotateTreeRight(TreeNode* ptr, TreeNode* ptr2)
{
	if (ptr == anker)
	{
		ptr = ptr->getLeft();
		ptr2->setLeft(ptr->getRight());
		ptr->setRight(ptr2);
		anker = ptr;
		if (anker->getLeft() != nullptr)
			anker->getLeft()->setRed(Red);
		if (anker->getRight() != nullptr)
			anker->getRight()->setRed(Red);

		anker->setRed(Black);
		return true;
	}
	else if (ptr2->getLeft() != nullptr && ptr2->getLeft() == ptr)
	{
		ptr = ptr->getLeft();
		ptr2->getLeft()->setLeft(ptr->getRight());
		ptr->setRight(ptr2->getLeft());
		ptr2->setLeft(ptr);
		if (ptr->getLeft() != nullptr)
			ptr->getLeft()->setRed(Red);
		if (ptr->getRight() != nullptr)
			ptr->getRight()->setRed(Red);
		if (ptr2->getLeft() != nullptr)
			ptr2->getLeft()->setRed(Black);
		return true;
	}
	else if (ptr2->getRight() != nullptr && ptr2->getRight() == ptr)
	{
		ptr = ptr->getLeft();
		ptr2->getRight()->setLeft(ptr->getRight());
		ptr->setRight(ptr2->getRight());
		ptr2->setRight(ptr);
		if (ptr->getLeft() != nullptr)
			ptr->getLeft()->setRed(Red);
		if (ptr->getRight() != nullptr)
			ptr->getRight()->setRed(Red);
		if (ptr2->getRight() != nullptr)
			ptr2->getRight()->setRed(Black);
		return true;
	}
	return false;
}

bool Tree::rotateTreeLeft(TreeNode* ptr, TreeNode* ptr2)
{
	if (ptr == anker)
	{
		ptr = ptr->getRight();
		ptr2->setRight(ptr->getLeft());
		ptr->setLeft(ptr2);
		anker = ptr;
		anker->setRed(Black);
		if (anker->getLeft() != nullptr)
			anker->getLeft()->setRed(Red);
		if (anker->getRight() != nullptr)
			anker->getRight()->setRed(Red);
		return true;
	}
	else if (ptr2->getLeft() != nullptr && ptr2->getLeft() == ptr)
	{
		ptr = ptr->getRight();
		ptr2->getLeft()->setRight(ptr->getLeft());
		ptr->setLeft(ptr2->getLeft());
		ptr2->setLeft(ptr);
		ptr->setRed(Black);
		if (ptr->getLeft() != nullptr)
			ptr->getLeft()->setRed(Red);
		if (ptr->getRight() != nullptr)
			ptr->getRight()->setRed(Red);
		return true;
	}
	else if (ptr2->getRight() != nullptr && ptr2->getRight() == ptr)
	{
		ptr = ptr->getRight();
		ptr2->getRight()->setRight(ptr->getLeft());
		ptr->setLeft(ptr2->getRight());
		ptr2->setRight(ptr);
		ptr->setRed(Black);
		if (ptr->getLeft() != nullptr)
			ptr->getLeft()->setRed(Red);
		if (ptr->getRight() != nullptr)
			ptr->getRight()->setRed(Red);
		return true;
	}
	return false;
}

bool Tree::balanceTree()
{
	TreeNode* tmp = anker;
	TreeNode* tmp2 = anker;

	queue<TreeNode*> q;
	if (tmp != nullptr)
	{
		q.push(tmp);
	}
	while (!q.empty())
	{
		tmp = q.front();
		q.pop();
		//auf Rotation pruefen
		if (tmp == anker)
		{
			tmp->setRed(Black);
		}
		if (tmp->getRight() != nullptr && tmp->getRight()->getRight() != nullptr)
		{
			if (tmp->getRight()->getRed() == Red && tmp->getRight()->getRight()->getRed() == Red)
			{
				tmp2 = getParent(tmp->getNodePosID());
				rotateTreeLeft(tmp, tmp2);
			}
		}
		if (tmp->getLeft() != nullptr && tmp->getLeft()->getLeft() != nullptr)
		{
			if (tmp->getLeft()->getRed() == Red && tmp->getLeft()->getLeft()->getRed() == Red)
			{
				tmp2 = getParent(tmp->getNodePosID());
				rotateTreeRight(tmp, tmp2);
			}
		}
		if (tmp->getRight() != nullptr && tmp->getRight()->getLeft() != nullptr)
		{
			if (tmp->getRight()->getRed() == Red && tmp->getRight()->getLeft()->getRed() == Red)
			{
				//Rechts-Liksrotation
				tmp2 = getParent(tmp->getNodePosID());
				rotateTreeRight(tmp->getRight(), tmp);
				rotateTreeLeft(tmp, tmp2);
			}
		}
		if (tmp->getLeft() != nullptr && tmp->getLeft()->getRight() != nullptr)
		{
			if (tmp->getLeft()->getRed() == Red && tmp->getLeft()->getRight()->getRed() == Red)
			{
				//Links-Rechtrotation
				tmp2 = getParent(tmp->getNodePosID());
				rotateTreeLeft(tmp->getLeft(), tmp);
				rotateTreeRight(tmp, tmp2);
			}
		}
		if (tmp->getLeft() != nullptr)
		{
			q.push(tmp->getLeft());
		}
		if (tmp->getRight() != nullptr)
		{
			q.push(tmp->getRight());
		}
	}

	return true;
}

void Tree::printLevelOrder()
{
	queue<TreeNode*> q;
	TreeNode* tmp = anker;
	printLayout();
	if (anker != nullptr)
	{
		q.push(tmp);
		while (!q.empty())
		{
			tmp = q.front();
			q.pop();
			tmp->print();
			if (tmp->getLeft() != nullptr)
				q.push(tmp->getLeft());
			if (tmp->getRight() != nullptr)
				q.push(tmp->getRight());
		}
	}
}


//
////////////////////////////////////