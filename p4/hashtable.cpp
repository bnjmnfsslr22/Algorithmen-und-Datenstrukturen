#include "hashtable.h"
#include <iostream>

using namespace std;

HashTable::HashTable(int size) 
{
	
	//*****************************
	// implement constructor here *
	//*****************************
	hashTable = new vector<int>(size);
	for (int i = 0; i < size; i++)
	{
		hashTable->at(i) = -1;
	}
	this->size = size;
	collisionCount = 0;
	elements = 0;
}

HashTable::~HashTable()
{
	//****************************
	// implement destructor here *
	//****************************
	delete hashTable;
}

int HashTable::hashValue(int item) 
{
	
	//******************************************
	// implement calculation of hashindex here *
	//******************************************
	int index;
	int N = this->getSize();
	int i = 0;
	
	index = ((item + i * i) % N);

	while (true)
	{
		if (hashTable->at(index) != -1)
		{
			i++;
			index = ((item + i * i) % N);
			collisionCount++;
		}
		else
		{
			break;
		}
	}

	return index;
}

bool HashTable::insert(int item) 
{
	//******************************************
	// implement insertion of new element here *
	//******************************************

	int hash_value = hashValue(item);
	hashTable->at(hash_value) = item;
	return true;
}


int HashTable::at(int i) 
{
	return hashTable->at(i);
}

int HashTable::getCollisionCount() 
{
	return this->collisionCount;
}

int HashTable::getSize() 
{
	return this->size;
}

int HashTable::getElements() 
{
	return this->elements;
}
