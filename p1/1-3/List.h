#ifndef _LIST_H
#define _LIST_H
#include "Node.h"
#include <string>
#include <iostream>


template <typename T>
class List
{
	/*
	Die Klasse List dient zur Verwaltung von Knoten (Node). Mit Hilfe der Klasse List
	kann ein Stapel oder Warteschlange realisiert werden.
	*/
private:
	struct form { std::string start = "<< "; std::string zwischen = ", "; std::string ende = " >>\n"; } list_form;
	Node<T> * head_tail;						// Zeiger auf Kopf- und End-Element -> next der 1. Knoten; -> prev der letzte Knoten
	int list_size;							// L�nge der Kette
	bool temp;								// normalerweise false; ist true, wenn es sich um eine temor�re Liste handelt
											// die innerhalb der �berladenen Operatoren angelegt wird
public:
	List();
	List(const List<T> & _List);				// Kopie Konstruktor
	List(const List<T> * _List);				// Kopie Konstruktor
	~List();
	void insertFront(T key);				// Einf�gen eines Knotens am Anfang
	void insertFront(List & _List);			// Einf�gen einer vorhandenen Liste am Anfang
	void insertFront(List * _List);			// Einf�gen einer vorhandenen Liste am Anfang
	void insertBack(T key);				// Einf�gen eines Knotesn am Ende
	void insertBack(List & _List);			// Einf�gen einer vorhandenen Liste am Ende
	void insertBack(List * _List);			// Einf�gen einer vorhandenen Liste am Ende
	bool getFront(T & key);				// Entnehmen eines Knoten am Anfang
	bool getBack(T & key);				// Entnehmen eines Knoten am Ende
	bool del(T key);						// l�schen eines Knotens [key]
	bool search(T key);					// Suchen eines Knoten
	bool swap(T key1, T key2);			// Knoten in der Liste vertauschen
	int size(void);							// Gr��e der Lise (Anzahl der Knoten)
	bool test(void);						// �berpr�fen der Zeigerstruktur der Liste
	void format(const std::string & start, const std::string & zwischen, const std::string & ende);	
											// Mit der format-Methode kann die Ausgabe gesteuert werden: operator <<
											// start: stirng vor der Ausgabe der Liste
											// zwischen: string zwischen Listenknoten
											// ende: string am Ende der Liste
	List & operator = (const List & _List);						// Zuweisungsoperator definieren
	List & operator = (const List * _List);						// Zuweisungsoperator definieren
	List & operator + (const List & List_Append);				// Listen zusammenf�hren zu einer Liste
	List & operator + (const List * List_Append);				// Listen zusammenf�hren zu einer Liste
	template <typename T>
	friend std::ostream & operator << (std::ostream & stream, List<T> const & Liste);		// Ausgabeoperator �berladen
	template <typename T>
	friend std::ostream & operator << (std::ostream & stream, List<T> const * Liste);		// Ausgabeoperator �berladen
	friend Node<T>* get_anker(List& l);
	friend int get_AnzahlNodes(List& l);
	template <typename T>
	friend std::ostream & operator<<(std::ostream & stream, const List<T> & Liste);
};


template <typename T>
List<T>::List()
{
	// Konstruktor f�r eine leere Liste
	head_tail = new Node<T>;
	list_size = 0;
	temp = false;
	head_tail->next = head_tail;
	head_tail->prev = head_tail;
}

template <typename T>
List<T>::List(const List<T> & _List)
{
	// Konstruktor mit �bergabe einer Liste, die dann kopiert wird.
	// in dem Objekt _List sind die Knotenwerte enthalten, die Kopiert werden sollen.
	list_form = _List.list_form;
	head_tail = new Node<T>;
	list_size = 0;
	temp = _List.temp;
	head_tail->next = head_tail;
	head_tail->prev = head_tail;
	Node<T> * tmp_node;
	tmp_node = _List.head_tail->next;
	while (tmp_node != _List.head_tail)
	{
		head_tail->prev = new Node<T>(tmp_node->key, head_tail->prev->next, head_tail->prev);
		head_tail->prev->prev->next = head_tail->prev;
		list_size++;
		tmp_node = tmp_node->next;
	}
	if (_List.temp) delete & _List;		// ist die �bergebene Liste eine tempor�re Liste? -> aus Operator +
}
template <typename T>
List<T>::List(const List<T> * _List)
{
	// Konstruktor mit �bergabe einer Liste, die dann kopiert wird.
	// in dem Objekt _List sind die Knotenwerte enthalten, die Kopiert werden sollen.
	list_form = _List->list_form;
	head_tail = new Node<T>;
	list_size = 0;
	temp = _List->temp;
	head_tail->next = head_tail;
	head_tail->prev = head_tail;
	Node<T> * tmp_node;
	tmp_node = _List->head_tail->next;
	while (tmp_node != _List->head_tail)
	{
		head_tail->prev = new Node<T>(tmp_node->key, head_tail->prev->next, head_tail->prev);
		head_tail->prev->prev->next = head_tail->prev;
		list_size++;
		tmp_node = tmp_node->next;
	}
	if (_List->temp) delete _List;		// ist die �bergebene Liste eine tempor�re Liste? -> aus Operator +
}
template <typename T>
List<T>::~List()
{
	// Dekonstruktor
	// Alle Knoten der Liste m�ssen gel�scht werden, wenn die Liste gel�scht wird.
/*
	hier alle Knoten l�schen, die im Objekt List allokiert wurden
*/
	Node<T>* tmp_node = head_tail->next;
	while (tmp_node != head_tail)
	{
		tmp_node = tmp_node->next;
		delete tmp_node->prev;
	}
	list_size = 0;
	delete tmp_node;


}
template <typename T>
void List<T>::insertFront(T key)
{
	// Einf�gen eines neuen Knotens am Anfang der Liste
/*
	Einen neuen Knoten mit dem Schl�sselwert key am Anfang der Liste einf�gen
*/
	Node<T>* neuer_eintrag = new Node<T>(key);
	neuer_eintrag->next = head_tail->next;
	head_tail->next->prev = neuer_eintrag;
	neuer_eintrag->prev = head_tail;
	head_tail->next = neuer_eintrag;
	list_size++;
}
template <typename T>
void List<T>::insertFront(List<T> & _List)
{
	// Einf�gen einer vorhandenen Liste am Anfang
	/*
	Die einzuf�genden Knoten werden �bernommen (nicht kopiert)
	Die einzuf�gende Liste _List ist anschlie�end leer.
	Es darf keine Schleife und kein new benutzt werden.
	*/
	/*
		Es wird ein Objekt �bergeben in dem Knoten vorhanden sein k�nnen.
		Diese Knoten (koplette Kette) werden an den Anfang der Liste (this) �bertragen ohne sie zu kopieren!
	*/

	//if (_List.list_size != 0)
	//{
	//	this->list_size = this->list_size + _List.list_size;

	//	head_tail->next->prev = _List.head_tail->prev;
	//	_List.head_tail->prev->next = head_tail->next;
	//	head_tail->next = _List.head_tail->next;
	//	_List.head_tail->next->prev = head_tail;

	//	_List.head_tail->next = _List.head_tail;
	//	_List.head_tail->prev = _List.head_tail;
	//	_List.list_size = 0;
	//}
	List<T>*ptr = &_List;
	this->insertFront(ptr);
}
template <typename T>
void List<T>::insertFront(List<T> * _List)
{
	// Einf�gen einer vorhandenen Liste am Anfang
	/*
	Die einzuf�genden Knoten werden �bernommen (nicht kopiert)
	Die einzuf�gende Liste _List ist anschlie�end leer.
	Es darf keine Schleife und kein new benutzt werden.
	*/
	/*
		Es wird ein Objekt �bergeben in dem Knoten vorhanden sein k�nnen.
		Diese Knoten (koplette Kette) werden an den Anfang der Liste (this) �bertragen ohne sie zu kopieren!
	*/
	if (_List->list_size != 0)
	{
		this->list_size = this->list_size + _List->list_size;

		head_tail->next->prev = _List->head_tail->prev;
		_List->head_tail->prev->next = head_tail->next;
		head_tail->next = _List->head_tail->next;
		_List->head_tail->next->prev = head_tail;

		_List->head_tail->next = _List->head_tail;
		_List->head_tail->prev = _List->head_tail;
		_List->list_size = 0;
	}
}
template <typename T>
void List<T>::insertBack(T key)
{
	// Einf�gen eines neuen Knotens am Ende der Liste
/*
	Einen neuen Knoten mit dem Schl�sselwert key am Ende der Liste einf�gen
*/
	Node<T>* neuer_eintrag = new Node<T>(key);
	neuer_eintrag->next = head_tail;
	neuer_eintrag->prev = head_tail->prev;
	head_tail->prev->next = neuer_eintrag;
	head_tail->prev = neuer_eintrag;
	list_size++;
}
template <typename T>
void List<T>::insertBack(List<T> & _List)
{
	// Einf�gen einer vorhandenen Liste am Ende
	/*
	Die einzuf�genden Knoten werden �bernommen (nicht kopiert)
	Die einzuf�gende Liste _List ist anschlie�end leer.
	Es darf keine Schleife und kein new benutzt werden.
	*/
	/*
		Es wird ein Objekt �bergeben in dem Knoten vorhanden sein k�nnen.
		Diese Knoten (koplette Kette) werden an das Ende der Liste (this) angehangen ohne sie zu kopieren!
	*/
	//if (_List.list_size != 0)
	//{
	//	this->list_size = this->list_size + _List.list_size;

	//	head_tail->prev->next = _List.head_tail->next;
	//	_List.head_tail->next->prev = head_tail->prev;
	//	head_tail->prev = _List.head_tail->prev;
	//	_List.head_tail->prev->next = head_tail;

	//	_List.head_tail->next = _List.head_tail;
	//	_List.head_tail->prev = _List.head_tail;
	//	_List.list_size = 0;
	//}
	List<T>*ptr = &_List;
	this->insertBack(ptr);
}
template <typename T>
void List<T>::insertBack(List<T> * _List)
{
	// Einf�gen einer vorhandenen Liste am Ende
	/*
	Die einzuf�genden Knoten werden �bernommen (nicht kopiert)
	Die einzuf�gende Liste _List ist anschlie�end leer.
	Es darf keine Schleife und kein new benutzt werden.
	*/
	/*
		Es wird ein Objekt �bergeben in dem Knoten vorhanden sein k�nnen.
		Diese Knoten (koplette Kette) werden an das Ende der Liste (this) angehangen ohne sie zu kopieren!
	*/
	if (_List->list_size != 0)
	{
		this->list_size = this->list_size + _List->list_size;

		head_tail->prev->next = _List->head_tail->next;
		_List->head_tail->next->prev = head_tail->prev;
		head_tail->prev = _List->head_tail->prev;
		_List->head_tail->prev->next = head_tail;

		_List->head_tail->next = _List->head_tail;
		_List->head_tail->prev = _List->head_tail;
		_List->list_size = 0;
	}
}
template <typename T>
bool List<T>::getFront(T & key)
{
	// entnehmen des Knotens am Anfang der Liste
	// der Wert wird als Parameter zur�ckgegeben
	// der Knoten wird entnommen
/*
	Der Wert des vorderen Schl�sselknotens wird r�ckgegeben und der Knoten gel�scht.
	Die Methode del(key) darf nicht zum l�schen benutzt werden.
*/
	if (head_tail->next != head_tail)
	{
		key = head_tail->next->key;

		head_tail->next = head_tail->next->next;
		delete head_tail->next->prev;
		head_tail->next->prev = head_tail;
		list_size--;
		return true;
	}
	else
	{
		return false;
	}
}
template <typename T>
bool List<T>::getBack(T & key)
{	// entnehmen des Knotens am Ende der Liste
	// der Wert wird als Parameter zur�ckgegeben
	// der Knoten wird entnommen
/*
	Der Wert des letzten Schl�sselknotens wird r�ckgegeben und der Knoten gel�scht.
	Die Methode del(key) darf nicht zum l�schen benutzt werden.
*/
	if (head_tail->prev != head_tail)
	{
		key = head_tail->prev->key;
		head_tail->prev = head_tail->prev->prev;
		delete head_tail->prev->next;
		head_tail->prev->next = head_tail;
		list_size--;
		return true;
	}
	else
	{
		return false;
	}
}
template <typename T>
bool List<T>::del(T key)
{
	// L�schen eines gegebenen Knotens
/*
	L�schen des Knotens mit dem Schl�ssel key
*/
	Node<T>* tmp_node = head_tail->next;
	while (tmp_node != head_tail)
	{
		if (tmp_node->key == key)
		{
			tmp_node->prev->next = tmp_node->next;
			tmp_node->next->prev = tmp_node->prev;
			delete tmp_node;
			list_size--;
			return true;
		}
		tmp_node = tmp_node->next;
	}

		return false;
}
template <typename T>
bool List<T>::search(T key)
{
	// suchen eines Knotens
/*
	suchen ob ein Knoten mit dem Schl�ssel key existiert.
*/
	Node<T>* tmp_node = head_tail->next;
	while (tmp_node != head_tail)
	{
		if (tmp_node->key == key)
		{

			return true;
		}
		tmp_node = tmp_node->next;
	}

		return false;

}
template <typename T>
bool List<T>::swap(T key1, T key2)
{
	// Vertauschen von zwei Knoten
	// Dabei werden die Zeiger der Knoten und deren Nachbarn ver�ndert.
/*
	Vertauschen von zwei Knoten mit dem key1 und dem key2
	Es d�rfen nicht nur einfach die Schl�ssel in den Knoten getauscht werden!
	Die Knoten sind in der Kette umzuh�ngen.
*/
	Node<T>* tmp1 = head_tail->next;
	Node<T>* tmp2 = head_tail->next;

	while (tmp1 != head_tail && tmp2 != head_tail)
	{
		if (tmp1->key != key1)
		{
			tmp1 = tmp1->next;
		}
		if (tmp2->key != key2)
		{
			tmp2 = tmp2->next;
		}
		if (tmp1->key == key1 && tmp2->key == key2)
		{
			break;
		}
	}
	if (tmp1 == head_tail || tmp2 == head_tail)
	{
		return false;
	}

	//Knoten liegen nebeneinander
	if (tmp1->next == tmp2)
	{
		tmp1->next = tmp2->next;
		tmp1->next->prev = tmp1;
		tmp2->prev = tmp1->prev;
		tmp2->prev->next = tmp2;
		tmp2->next = tmp1;
		tmp1->prev = tmp2;

		return true;
	}
	else if (tmp2->next == tmp1)
	{
		tmp2->next = tmp1->next;
		tmp2->next->prev = tmp2;
		tmp1->prev = tmp2->prev;
		tmp1->prev->next = tmp1;
		tmp1->next = tmp2;
		tmp2->prev = tmp1;

		return true;
	}
	//Knoten liegen nicht nebeneinander
	else
	{
		Node<T>* tmp2_swap_next = tmp2->next;
		Node<T>* tmp2_swap_prev = tmp2->prev;

		tmp2->next = tmp1->next;
		tmp2->prev = tmp1->prev;
		tmp2->next->prev = tmp2;
		tmp2->prev->next = tmp2;

		tmp1->next = tmp2_swap_next;
		tmp1->prev = tmp2_swap_prev;
		tmp2_swap_next->prev = tmp1;
		tmp2_swap_prev->next = tmp1;
		return true;
	}
}
template <typename T>
int List<T>::size(void)
{
	// R�ckgabe der Knoten in der Liste mit O(1)
/*
	Anzahl der Knoten in der Liste zur�ckgeben.
*/
	return list_size;
}
template <typename T>
bool List<T>::test(void)
{
	// Testmethode: die Methode durchl�uft die Liste vom Anfang bis zum Ende und zur�ck
	// Es werden dabei die Anzahl der Knoten gez�hlt.
	// Stimmt die Anzahl der Knoten �berein liefert die Methode true
	Node<T> * tmp = head_tail->next;
	int i_next = 0, i_prev = 0;
	while (tmp != head_tail) {
		tmp = tmp->next;
		if (i_next > list_size) return false;
		i_next++;
	}
	if (i_next != list_size) return false;
	tmp = head_tail->prev;
	while (tmp != head_tail) {
		tmp = tmp->prev;
		if (i_prev > list_size) return false;
		i_prev++;
	}
	return i_prev == i_next;
}
template <typename T>
List<T> & List<T>::operator = (const List<T> & _List)
{
	// in dem Objekt _List sind die Knotenwerte enthalten, die Kopiert werden sollen.
	// Kopiert wird in das Objekt "this"
	if (this == &_List) return *this;		//  !! keine Aktion notwendig
	list_form = _List.list_form;
	Node<T> * tmp_node;
	if (list_size)
	{
		Node<T> * tmp_del;
		tmp_node = head_tail->next;
		while (tmp_node != head_tail)		// Alle eventuell vorhandenen Knoten in this l�schen
		{
			tmp_del = tmp_node;
			tmp_node = tmp_node->next;
			delete tmp_del;
		}
		list_size = 0;
		head_tail->next = head_tail;
		head_tail->prev = head_tail;
	}
	tmp_node = _List.head_tail->next;		// Die Listen-Knotenwerte werden kopiert
	while (tmp_node != _List.head_tail)
	{
		insertBack(tmp_node->key);
		tmp_node = tmp_node->next;
	}
	if (_List.temp) delete & _List;			// ist die �bergebene Liste eine tempor�re Liste? -> aus Operator +
	return *this;
}
template <typename T>
List<T> & List<T>::operator = (const List<T> * _List)
{
	// in dem Objekt _List sind die Knotenwerte enthalten, die Kopiert werden sollen.
	// Kopiert wird in das Objekt "this"
	if (this == _List) return *this;		//  !! keine Aktion notwendig
	list_form = _List->list_form;
	Node<T> * tmp_node;
	if (list_size)
	{
		Node<T> * tmp_del;
		tmp_node = head_tail->next;
		while (tmp_node != head_tail)		// Alle eventuell vorhandenen Knoten in this l�schen
		{
			tmp_del = tmp_node;
			tmp_node = tmp_node->next;
			delete tmp_del;
		}
		list_size = 0;
		head_tail->next = head_tail;
		head_tail->prev = head_tail;
	}
	tmp_node = _List->head_tail->next;
	while (tmp_node != _List->head_tail)	// Die Listen-Knotenwerte werden kopiert
	{
		insertBack(tmp_node->key);
		tmp_node = tmp_node->next;
	}
	if (_List->temp) delete _List;			// ist die �bergebene Liste eine tempor�re Liste? -> aus Operator +
	return *this;
}
template <typename T>
List<T> & List<T>::operator + (const List<T> & List_Append)
{
	// Die Methode +
	// Es werden zwei Listen aneinander gehangen.
	// Dabei werden beide Ursprungslisten nicht ver�ndert. Es entsteht eine neue Ergebnisliste.
	Node<T> * tmp_node;
	List<T> * tmp;
	if (temp) {										// this ist eine tempor�re Liste und kann ver�ndert werden
		tmp = this;
	}
	else {
		tmp = new List<T>(this);						// this ist keine tempor�re Liste -> Kopie erzeugen
		tmp->temp = true;							// Merker setzten, dass es sich um eine tempor�re Liste handelt
	}
	if (List_Append.list_size) {					// anh�ngen der �bergebenen Liste an tmp
		tmp_node = List_Append.head_tail->next;
		while (tmp_node != List_Append.head_tail) {
			tmp->insertBack(tmp_node->key);
			tmp_node = tmp_node->next;
		}
	}
	if (List_Append.temp) delete & List_Append;		// wurde eine tempor�re Liste �bergeben, dann wird diese gel�scht						
	return *tmp;
}
template <typename T>
List<T> & List<T>::operator + (const List<T> * List_Append)
{
	// Die Methode +
	// Es werden zwei Listen aneinander gehangen.
	// Dabei werden beide Ursprungslisten nicht ver�ndert. Es entsteht eine neue Ergebnisliste.
	Node<T> * tmp_node;
	List<T> * tmp;
	if (temp) {										// this ist eine tempor�re Liste und kann ver�ndert werden
		tmp = this;
	}
	else {
		tmp = new List<T>(this);						// this ist keine tempor�re Liste -> Kopie erzeugen
		tmp->temp = true;							// Merker setzten, dass es sich um eine tempor�re Liste handelt
	}
	if (List_Append->list_size) {					// anh�ngen der �bergebenen Liste an tmp
		tmp_node = List_Append->head_tail->next;
		while (tmp_node != List_Append->head_tail) {
			tmp->insertBack(tmp_node->key);
			tmp_node = tmp_node->next;
		}
	}
	if (List_Append->temp) delete List_Append;		// wurde eine tempor�re Liste �bergeben, dann wird diese gel�scht					
	return *tmp;
}
template <typename T>
void List<T>::format(const std::string & start, const std::string & zwischen, const std::string & ende)
{
	// Setzen des Formates f�r die Ausgabesteuerung der Liste bei cout
	// das Format wird f�r den �berladenen Operator << verwendet
	list_form.start = start;
	list_form.zwischen = zwischen;
	list_form.ende = ende;
}
template <typename T>
std::ostream & operator<<(std::ostream  & stream, List<T> const & Liste)
{
	// Ausgabe der Liste mit cout
	stream << Liste.list_form.start;
	for (Node<T> * tmp = Liste.head_tail->next; tmp != Liste.head_tail; tmp = tmp->next)
		stream << tmp->key << (tmp->next == Liste.head_tail ? Liste.list_form.ende : Liste.list_form.zwischen);
	if (Liste.temp) delete & Liste;			// wurde eine tempor�re Liste �bergeben, dann wird diese gel�scht
	return stream;
}
template <typename T>
std::ostream & operator << (std::ostream & stream, List<T> const * Liste)
{
	// Ausgabe der Liste mit cout
	stream << Liste->list_form.start;
	for (Node<T> * tmp = Liste->head_tail->next; tmp != Liste->head_tail; tmp = tmp->next)
		stream << tmp->key << (tmp->next == Liste->head_tail ? Liste->list_form.ende : Liste->list_form.zwischen);
	if (Liste->temp) delete Liste;			// wurde eine tempor�re Liste �bergeben, dann wird diese gel�scht
	return stream;
}

#endif
