/*************************************************
* ADS Praktikum 2.1
* Ring.cpp
* Erweiterung um Hilfsfunktionen gestattet.
*************************************************/
// Ring .cpp
#include "Ring.h"
#include<string>
#include <iostream>
using namespace std;
// Ihr Code hier:

Ring::Ring()
{

}

void Ring::addNewNode(string _description, string _data)
{
	RingNode* neu = new RingNode(0, _description, _data);
	RingNode* tmp = anker;

	if (anker == nullptr)
	{
		anker = neu;
		neu->setNext(neu);
		AnzahlNodes++;

	}
	else if (AnzahlNodes < max_nodes && AnzahlNodes > 0)
	{
		for (int i = 0; i < AnzahlNodes; i++)
		{
			tmp->setAge(tmp->getAge() + 1);
			tmp = tmp->getNext();
		}
		neu->setNext(anker->getNext());//nicht Anker sonder erste/letztes Element 
		tmp->setNext(neu);
		anker = neu;
		AnzahlNodes++;
	}
	else if (AnzahlNodes == max_nodes)
	{
		for (int i = 0; i < max_nodes; i++)
		{
			tmp->setAge(tmp->getAge() + 1);
			tmp = tmp->getNext();
		}

		RingNode* tmp2 = anker;

		while (tmp2->getNext()!= anker)
		{
			if (tmp2->getNext()->getAge() == 6)
			{
				neu->setNext(tmp2->getNext()->getNext());

				if (tmp2->getNext() == anker)
				{
					anker = neu;
				}
				delete tmp2->getNext();
				tmp2->setNext(neu);
				anker = neu;
				break;
			}
			tmp2 = tmp2->getNext();
		}
	}

}
bool Ring::search(string _data)
{
	RingNode* tmp = anker;
	int counter = 0;
	for (int i = 0; i < AnzahlNodes; i++)
	{
		if (tmp->getData() == _data)
		{
			counter++;
		}
		tmp = tmp->getNext();
	}
	if(counter>0)
		return true;
	else
		return false;
}
void Ring::print()
{
	for (int i = 0; i < AnzahlNodes; i++)
	{
		RingNode* tmp = anker;
		do
		{
			if (tmp->getAge() == i)
			{
				cout << "OldAge: " << tmp->getAge() << ", Descr: " << tmp->getDescription() << ", Data: " << tmp->getData() << endl
					<< "____________________________________________________________________________" << endl << endl;
				break;
			}
			tmp = tmp->getNext();
		} while (tmp != anker);
	}
}

void Ring::print_one(string _data)
{
	RingNode* tmp = anker;
	for (int i=0;i<AnzahlNodes;i++)
	{
		if (tmp->getData() == _data)
		{
			cout << "OldAge: " << tmp->getAge() << ", Descr: " << tmp->getDescription() << ", Data: " << tmp->getData() << endl
				<< "____________________________________________________________________________" << endl << endl;
		}
		tmp = tmp->getNext();
	}
}



//
////////////////////////////////////
