#pragma once
#include <iostream>
#include <time.h>

using namespace std;

struct Data
{
	int data = 0, index1 = 0, index2 = 0, index = 0;

	Data(int data, int index1, int index2, int index)
	{
		this->data = data;
		this->index1 = index1;
		this->index2 = index2;
		this->index = index;
	}

	Data()
	{
		data = 0;
		index1 = 0;
		index2 = 0;
		index = 0;
	}
};

struct Elem
{
	Data data;
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

	void AddTail(Data n);

	void AddHead(Data n);

	void Print();

	void Print(int pos);

	List& operator = (const List&);

	List operator + (const List&);

	bool operator == (const List&);
	bool operator != (const List&);
	bool operator <= (const List&);
	bool operator >= (const List&);
	bool operator < (const List&);
	bool operator > (const List&);

	List operator - ();
};

void InputInt(int& n);

