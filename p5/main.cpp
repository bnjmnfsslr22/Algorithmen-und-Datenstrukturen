#define CATCH_CONFIG_RUNNER
#include<iostream>
#include"Graph.h"
#include"catch.h"

using namespace std;


int main()
{
	Catch::Session().run();
	
	cout << "Working on Graphs, please choose:" << endl;
	
	char eingabe;
	Graph _graph;
	do
	{
		cin.clear();
		cout << "1) Graph einlesen" << endl
			<< "2) Tiefensuche" << endl
			<< "3) Breitensuche" << endl
			<< "4) Prim" << endl
			<< "5) Kruskal" << endl
			<< "6) Print Graph" << endl
			<< "7) Dijkstra"<<endl
			<< "0) Programm beenden" << endl
			<< "?> ";
		cin >> eingabe;
		cout << endl;
		if (eingabe == '1')
		{
			char auswahl_graph;
			do
			{
				cout << "Welchen Graphen moechten sie bearbeiten 1, 2 oder 3 ?>";
				cin >> auswahl_graph;
				if (auswahl_graph == '1')
				{
					_graph.init("graph1.txt");
				}
				else if (auswahl_graph == '2')
				{
					_graph.init("graph2.txt");
				}
				else if (auswahl_graph == '3')
				{
					_graph.init("graph3.txt");
				}
			} while (auswahl_graph<'0'&&auswahl_graph>'3');
			cout << endl;
		}
		else if (eingabe == '2')
		{
			int start;
			cout << "Mit welchem Knoten wollen Sie starten (0-" << _graph.getAnzKnoten() << ") ?>";
			cin >> start;
			if (_graph.depthSearchRek(start) == true)
			{
				cout << "Es wurden alle Knoten besucht" << endl<<endl;
			}
			else
			{
				cout << "Nicht alle Knoten konnten besucht werden" << endl<<endl;
			}
			
		}
		else if (eingabe == '3')
		{
			int start;
			cout << "Mit welchem Knoten wollen Sie starten (0-" << _graph.getAnzKnoten() << ") ?>";
			cin >> start;
			if (_graph.breadthSearchIter(start) == true)
			{
				cout << "Es wurden alle Knoten besucht" << endl << endl;
			}
			else
			{
				cout << "Nicht alle Knoten konnten besucht werden" << endl << endl;
			}
		}
		else if (eingabe == '4')
		{
			int start;
			cout << "Mit welchem Knoten moechten Sie starten (0-" << _graph.getAnzKnoten() << ") ?>";
			cin >> start;
			cout << "Die kosten des MST betragen: " << _graph.prim(start) << endl << endl;
		}
		else if (eingabe == '5')
		{
			int start;
			cout << "Mit welchem Knoten moechten Sie starten (0-" << _graph.getAnzKnoten() << ") ?>";
			cin >> start;
			cout << "Die kosten des MST betragen: " << _graph.kruskal() << endl << endl;
		}
		else if (eingabe == '6')
		{
			_graph.print_all();
		}
		else if (eingabe == '7')
		{
			int start;
			cout << "Mit welchem Knoten moechten Sie starten (0-" << _graph.getAnzKnoten() << ") ?>";
			cin >> start;
			_graph.dijkstra(start);
		}

	} while (eingabe != '0');

	std::system("PAUSE");
	return 0;
}