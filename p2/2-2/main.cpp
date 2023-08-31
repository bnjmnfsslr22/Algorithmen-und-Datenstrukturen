/*************************************************
* ADS Praktikum 2.2
* main.cpp
*
*************************************************/
#define CATCH_CONFIG_RUNNER
#include <iostream>
#include <fstream>
#include "Tree.h"
#include "catch.h"

using namespace std;

//Antworten auf Fragen
//1)
//Es w�rde ein entarteter Baum enstehen Left Pointer useless
//2)
//W�rde nicht eingef�gt werden da weder kleiner noch groesser
//3)
//wie oft ein Name vorkommt
//ob Daten gel�scht wurden da Node ID einmalig
//Je nach verwendung den Schluessel anders w�hlen fuer bessere interpretationen
//4)
//Ringpuffer um nach Namen oder PLZ zu sortieren
//jede RingNode ein Bin�rbaum der nach Buchstaben oder PLZ bzw einkommen sortiert
//
//Je nach datengroesse eine Doppelt verkettete Liste mit mehreren Ankern 
//die auf verschiedene anfaenge von Namen oder PLZ zeigen


	///////////////////////////////////////
	// Hilfsmethoden f�rs Men� hier:



	//
	///////////////////////////////////////
int main() {

	int result = Catch::Session().run();
	

	///////////////////////////////////////
	// Ihr Code hier:

	Tree DerBaum;
	int eingabe;
	cout << "A TreeNode is never at the wrong place, Frodo Baggins. Nor is it at the right place; it is precisely where it means to be." << endl;
	do
	{
		cin.clear();
		cout << "===================================================================================" << endl<<endl<<endl;
		cout << "1) Datensatz einfuegen, mmanuell" << endl
			<< "2) Datensatz einfuegen, CSV Datei" << endl
			<< "3) Datensatz loeschen" << endl
			<< "4) Suchen" << endl
			<< "5) Datenstruktur anzeigen" << endl
			<< "6) Programm beenden" << endl
			<< "?>";
		cin >> eingabe;
		cout << endl << endl;
		if (eingabe == 1)
		{
			string Name;
			int Alter;
			int Einkommen;
			int PLZ;
			cout << "Name ?> "; cin >> Name;
			cout << "Alter ?> "; cin >> Alter; 
			cout << "Einkommen ?> "; cin >> Einkommen; 
			cout << "PLZ ?> "; cin >> PLZ;
			DerBaum.addNode(Name, Alter, Einkommen, PLZ);
			
			cout << "+ Ihr Datensatz wurde eingefuegt +" << endl << endl;
		}
		else if (eingabe == 2)
		{
			char eingabe2;
			cout << "Moechten Sie Daten aus der Datei \"ExportZielanalyse.csv\" importieren (j/n) ?> ";
			cin >> eingabe2;
			if (eingabe2 == 'j')
			{
				fstream data_in;
				data_in.open("ExportZielanalyse.csv", ios::in);
				if (data_in)
				{
					string Name;
					string Alter;
					string Einkommen;
					string PLZ;
					while (getline(data_in, Name, ';') && getline(data_in, Alter, ';') && getline(data_in, Einkommen, ';') && getline(data_in, PLZ, '\n'))
					{
						DerBaum.addNode(Name, stoi(Alter), stod(Einkommen), stoi(PLZ));
					}
				}
				data_in.close();
			}
			else
			{
				cout << "Dann halt nicht! Entscheiden Sie sich doch einfach vorher" << endl;
			}
		}
		else if (eingabe == 3)
		{
			int PosID;
			cout << "Bitte geben Sie den zu loeschenden Datensatz ein" << endl << "PosID ? >";
			cin >> PosID;
			DerBaum.deleteNode(PosID);
			cout << endl << "+ Datensatz wurde gel�scht +" << endl;
		}
		else if (eingabe == 4)
		{
			string Name;
			cout << "Bitte geben Sie den zu suchenden Datensatz an" << endl
				<< "Name ?>";
			cin >> Name;
			if (DerBaum.searchNode(Name))
			{
				cout << "Der Datensatz wurde gefunden (siehe oben)" << endl;
			}
			else
			{
				cout << "Der Datensatz wurde nicht gefunden" << endl;
			}
		}
		else if (eingabe == 5)
		{
			DerBaum.printAll();
		}
		else if (eingabe == 6)
		{
			cout << "Um das Programm zu beenden wiederholen Sie die eingabe :>";
			cin >> eingabe;
		}

	} while (eingabe != 6);

	//
	///////////////////////////////////////
	system("PAUSE");

	return 0;
}
