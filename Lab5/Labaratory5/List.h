#pragma once
#include "Element.h"

struct Elem
{
	Element data;
	Elem* next, * prev;
};

class List
{
	Elem* Head, * Tail;

	int Count;
public:

	List();

	List(const List&);

	~List();

	int GetCount();

	Elem* GetElem(int);

	void DelAll();

	void Del(int pos = 0);

	void Insert(int pos, Element data);

	void AddTail(Element n);

	void AddHead(Element n);

	List& operator = (const List&);

};
inline List::List()
{

	Head = Tail = NULL;
	Count = 0;
}
inline List::List(const List& L)
{
	Head = Tail = NULL;
	Count = 0;

	Elem* temp = L.Head;

	while (temp != 0)
	{

		AddTail(temp->data);
		temp = temp->next;
	}
}
inline List::~List()
{

	DelAll();
}
inline void List::AddHead(Element n)
{

	Elem* temp = new Elem;

	temp->prev = 0;

	temp->data = n;

	temp->next = Head;

	if (Head != 0)
		Head->prev = temp;



	if (Count == 0)
		Head = Tail = temp;
	else

		Head = temp;
	Count++;
}
inline void List::AddTail(Element n)
{

	Elem* temp = new Elem;

	temp->next = 0;

	temp->data = n;

	temp->prev = Tail;

	if (Tail != 0)
		Tail->next = temp;


	if (Count == 0)
		Head = Tail = temp;
	else
		Tail = temp;

	Count++;
}

inline void List::Insert(int pos, Element data)
{
	if (pos == 0)
	{
		cout << "Input position: ";
		cin >> pos;
	}

	if (pos < 1 || pos > Count + 1)
	{

		cout << "Incorrect position !!!\n";
		return;
	}

	if (pos == Count + 1)
	{
		AddTail(data);
		return;
	}
	else if (pos == 1)
	{
		AddHead(data);
		return;
	}


	int i = 1;

	Elem* Ins = Head;
	while (i < pos)
	{
		Ins = Ins->next;
		i++;
	}


	Elem* PrevIns = Ins->prev;

	Elem* temp = new Elem;

	temp->data = data;

	if (PrevIns != 0 && Count != 1)
		PrevIns->next = temp;
	temp->next = Ins;
	temp->prev = PrevIns;
	Ins->prev = temp;
	Count++;
}
inline void List::Del(int pos)
{


	if (pos == 0)
	{
		cout << "Input position: ";
		cin >> pos;
	}

	if (pos < 1 || pos > Count)
	{

		cout << "Incorrect position !!!\n";
		return;
	}

	int i = 1;
	Elem* Del = Head;
	while (i < pos)
	{


		Del = Del->next;
		i++;
	}


	Elem* PrevDel = Del->prev;

	Elem* AfterDel = Del->next;

	if (PrevDel != 0 && Count != 1)

		PrevDel->next = AfterDel;

	if (AfterDel != 0 && Count != 1)
		AfterDel->prev = PrevDel;

	if (pos == 1)
		Head = AfterDel;
	if (pos == Count)
		Tail = PrevDel;

	delete Del;
	Count--;
}

inline void List::DelAll()
{

	while (Count != 0)
		Del(1);
}
inline int List::GetCount()
{
	return Count;
}
inline Elem* List::GetElem(int pos)
{
	Elem* temp = Head;

	if (pos < 1 || pos > Count)
	{

		cout << "Incorrect position !!!\n";
		return 0;
	}
	int i = 1;

	while (i < pos && temp != 0)
	{
		temp = temp->next;
		i++;
	}
	if (temp == 0)
		return 0;
	else
		return temp;
}
inline List& List::operator = (const List& L)
{

	if (this == &L)
		return *this;

	this->~List();
	Elem* temp = L.Head;

	while (temp != 0)
	{
		AddTail(temp->data);
		temp = temp->next;
	}
	return *this;
}
