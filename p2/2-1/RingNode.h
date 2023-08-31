/*************************************************
* ADS Praktikum 2.1
* RingNode.h
* Erweiterung um Hilfsfunktionen gestattet.
*************************************************/
#pragma once
#include <string>

class RingNode{
	
private:
	// Ihr Code hier:
	int OldAge = 0;
	std::string Description;
	std::string SymbolicData;
	RingNode* next = nullptr;


	//	
public:
	// Ihr Code hier:
	RingNode();
	RingNode(int a, std::string _descrition, std::string _data);

	int getAge();
	void setAge(int _age);
	std::string getDescription();
	void setDescription(std::string _description);
	std::string getData();
	void setData(std::string _data);
	RingNode* getNext();
	void setNext(RingNode* _next);

	//
};
