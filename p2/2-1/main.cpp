/*************************************************
* ADS Praktikum 2.1
* main.cpp
* 
*************************************************/
#define CATCH_CONFIG_RUNNER

#include <iostream>
#include <string>
#include "Ring.h"
#include "catch.hpp"


using namespace std;


int main()
{
	int result = Catch::Session().run();

	// Ihr Code hier:
	Ring OneRing;
	int eingabe = 0;

	cout << "Ein Ring, sie zu knechten, sie alle zu finden," << endl
		<< "Ins Dunkel zu treiben und ewig zu binden" << endl
		<< "================================================" << endl << endl;

	do
	{
		cin.clear();
		cout << "1) Backup einfuegen" << endl
			<< "2) Backup suchen" << endl
			<< "3) Alle Backups ausgeben" << endl
			<< "4) Programm beenden" << endl
			<< "?>";
		cin >> eingabe;
		cout << endl;
		if (eingabe == 1)
		{
			string beschreibung;
			string daten;
			cout << "+ Neuen Datensatz einfuegen +" << endl;
			cout << "Beschreibung ?> ";
			cin >> beschreibung; cout << endl;
			cout << "Daten ?> ";
			cin >> daten; cout << endl;
			OneRing.addNewNode(beschreibung, daten);
			if (OneRing.search(daten))
			{
				cout << "+ Ihr Datensatz wurde hinzugefuegt +" << endl << endl;
			}
			else
			{
				cout << "- Error Daten nicht hinzugefuegt -" << endl << endl;
			}
		}
		else if (eingabe == 2)
		{
			string zu_suchen;
			cout << "+ Nach welchen Daten soll gesucht werden? +" << endl;
			cout << "?> ";
			cin >> zu_suchen; 
			
			if (OneRing.search(zu_suchen))
			{
				cout << endl << "Gefunden in Backup: ";
				OneRing.print_one(zu_suchen);
			}
			else
			{
				cout << "+ Datensatz konnte nicht gefunden werden +" << endl<<endl;
			}
		}
		else if (eingabe == 3)
		{
			OneRing.print();
		}
		else if (eingabe < 1 || eingabe > 4)
		{
			cout << "Ungueltige Eingabe!" << endl << endl;
		}


	} while (eingabe != 4);


	//
	///////////////////////////////////////
	system("Pause");
	return 0;
}
