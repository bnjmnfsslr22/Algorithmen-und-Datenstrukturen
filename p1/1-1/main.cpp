#include <iostream>
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "List.h"
using namespace std;

int main(void)
{
	int result = Catch::Session().run();
	int i;
	List MyList;

	for (i = 0; i < 10; i++) {
		MyList.insertFront(i + 1);
		MyList.insertBack(i + 100);
	}

	cout << MyList;

	cout << "100: " << (MyList.search(100) ? "gefunden" : "nicht gefunden") << endl;
	cout << "99: " << (MyList.search(99) ? "gefunden" : "nicht gefunden") << endl << endl;

	while (MyList.getBack(i))
		cout << i << " ";
	cout << endl << endl;

	List MyList1, MyList2, MyList3;
	List * MyList_dyn = new List;

	for (i = 0; i < 10; i++) {
		MyList1.insertFront(i + 1);
		MyList2.insertBack(i + 100);
	}

	MyList1.format("MyList1\n<<", ", ", ">>\n\n");
	cout << MyList1;

	MyList_dyn->format("MyList_dyn\n<<", ", ", ">>\n\n");
	MyList_dyn->insertFront(-111);
	cout << MyList_dyn;

	MyList2.format("MyList2\n<<", ", ", ">>\n\n");
	cout << MyList2;

	MyList3 = MyList1 + MyList_dyn + MyList2;

	delete MyList_dyn;

	cout << "Groesse von MyList3: " << MyList3.size() << endl << endl;

	MyList3.format("MyList3\n<<", ", ", ">>\n\n");
	cout << MyList3 << endl;

	MyList3.swap(8, 103);

	cout << MyList3;

	if (MyList3.test())
		cout << "MyList3: Zeiger OK\n\n";
	else
		cout << "MyList3: Zeiger ******Error\n\n";


	cout << "=============================================================================================" << endl << endl;
	List MyList4, MyList5, MyList6, MyList9,MyList10;
	List* MyList7 = new List;
	List* MyList8 = new List;
	
	if (MyList4.search(7))
	{
		cout << "gefunden in leerer Liste" << endl<<endl;
	}
	else
	{
		cout << "Nicht in leerer Liste gefunden" << endl<<endl;
	}

	for (int i = 0; i < 10; i++)
	{
		MyList10.insertFront(i);
		MyList4.insertFront(i);
		MyList9.insertFront(i);
		MyList5.insertFront(i + 10);
		MyList6.insertFront(i);
		MyList7->insertFront(i + 10);
		MyList8->insertFront(i + 10);
	}

	cout << "Test Liste vorne anhaengen Referenz-Pointer" << endl;
	cout << MyList4 << endl;
	MyList4.insertFront(MyList5);
	cout << MyList4 << endl;

	MyList4.insertFront(MyList7);
	cout << MyList4 << endl << endl;

	if (MyList4.test())
		cout << "MyList4: Zeiger OK\n\n";
	else
		cout << "MyList4: Zeiger ******Error\n\n";

	cout << "Test Liste hinten anhaengen Referenz-Pointer" << endl;
	cout << MyList6 << endl;
	MyList6.insertBack(MyList9);
	cout << MyList6 << endl;

	MyList6.insertBack(MyList8);
	cout << MyList6 << endl << endl;

	if (MyList6.test())
		cout << "MyList6: Zeiger OK\n\n";
	else
		cout << "MyList6: Zeiger ******Error\n\n";
	cout << "=============================================================================================" << endl << endl;

	int test1, test2;
	MyList6.getFront(test1);
	MyList6.getBack(test2);

	cout <<  test1 << endl;
	cout <<  test2 << endl;

	cout << MyList6 << endl;
	if (MyList6.test())
		cout << "MyList6: Zeiger OK\n\n";
	else
		cout << "MyList6: Zeiger ******Error\n\n";
	cout << "=============================================================================================" << endl << endl;

	cout << "Suche die 8" << endl;
	if (MyList6.search(8))
		cout << "Suche erfolgreich" << endl;
	else
		cout << "Int nicht gefunden" << endl;

	MyList6.del(8);
	MyList6.del(8);
	cout << " 8 wurde geloescht" << endl;

	if (MyList6.search(8))
		cout << "Suche erfolgreich" << endl;
	else
		cout << "Integer nicht gefunden" << endl;

	cout << MyList6.size() << endl;

	if (MyList6.test())
		cout << "MyList6: Zeiger OK\n\n";
	else
		cout << "MyList6: Zeiger ******Error\n\n";

	cout << "=============================================================================================" << endl << endl;

	cout << "Testen der restlichen swap Methoden" << endl;

	
	cout <<endl<< MyList10 << endl;
	//Erster und letzter Knoten
	MyList10.swap(0, 9);
	cout << endl << MyList10 << endl;
	//nebeneinaner am Ende
	MyList10.swap(0, 8);
	cout << endl << MyList10 << endl;
	//nebeneinander am Anfang
	MyList10.swap(1, 9);
	cout << endl << MyList10 << endl;
	//Knoten nicht in Liste
	MyList10.swap(11, 9);
	cout << endl << MyList10 << endl;

	if (MyList6.test())
		cout << "MyList6: Zeiger OK\n\n";
	else
		cout << "MyList6: Zeiger ******Error\n\n";
	

	system("PAUSE");
	return 0;
}
