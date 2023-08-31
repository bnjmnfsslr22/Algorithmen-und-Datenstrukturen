/*************************************************
* ADS Praktikum 2.1
* Ring.h
* Erweiterung um Hilfsfunktionen gestattet.
*************************************************/
// Ring .h
#pragma once
#include<string>
#include "catch.hpp"
#include"RingNode.h"

const int max_age = 5; // 0-5 == 6 Nodes!
const int max_nodes = 6;

class Ring{
	
	private:
		// Ihr Code hier:	
		int AnzahlNodes = 0;
		RingNode* anker = nullptr;
		//
		////////////////////////////////////
	public:
		// Ihr Code hier:
		Ring();

		void addNewNode(std::string _description, std::string _data);
		bool search(std::string _description);
		void print();
		void print_one(std::string _data);

		//
		////////////////////////////////////
		// friend Funktionen müssen unangetastet bleiben! 
		friend RingNode * get_anker(Ring& r);
		friend int get_AnzahlNodes(Ring& r);
};
