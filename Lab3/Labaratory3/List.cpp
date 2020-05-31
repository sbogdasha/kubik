#include "List.h"

List::List()
{
	Head = Tail = NULL;
	Count = 0;
}
List::List(const List& L)
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
List::~List()
{
	DelAll();
}
void List::AddHead(Data n)
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
void List::AddTail(Data n)
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

void List::Del(int pos)
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
void List::Print(int pos) {

	if (pos < 1 || pos > Count)
	{

		cout << "Incorrect position !!!\n";
		return;
	}
	Elem* temp;


	if (pos <= Count / 2)
	{

		temp = Head;
		int i = 1;
		while (i < pos)
		{

			temp = temp->next;
			i++;
		}
	}
	else
	{

		temp = Tail;
		int i = 1;
		while (i <= Count - pos)
		{

			temp = temp->prev;
			i++;
		}
	}

	cout << pos << " element: ";
	cout << temp->data.data << endl;
}
void List::Print() {
	bool flag = false;
	int a = -1;
	if (Count != 0)
	{
		Elem* temp = Head;
		
		while (temp->next != 0)
		{
			if (temp->data.index != a)
			{
				a = temp->data.index;
				cout << endl << "List num " << (a + 1) << ": " << endl;
			}
			if (temp->next->data.index != a) cout << temp->data.data << " ";
			else cout << temp->data.data << ",";

			temp = temp->next;
		}
		cout << temp->data.data << endl;
	}
}

void List::DelAll()
{

	while (Count != 0)
		Del(1);
}
int List::GetCount()
{
	return Count;
}
Elem* List::GetElem(int pos)
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
List& List::operator = (const List& L)
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

List List::operator + (const List& L)
{


	List Result(*this);

	Elem* temp = L.Head;


	while (temp != 0)
	{
		Result.AddTail(temp->data);
		temp = temp->next;
	}
	return Result;
}
bool List::operator == (const List& L)
{

	if (Count != L.Count)
		return false;
	Elem* t1, * t2;
	t1 = Head;
	t2 = L.Head;

	while (t1 != 0)
	{


		if (t1->data.data != t2->data.data)
			return false;
		t1 = t1->next;
		t2 = t2->next;
	}
	return true;
}

bool List::operator != (const List& L)
{

	return !(*this == L);
}
bool List::operator >= (const List& L)
{

	if (Count > L.Count)
		return true;

	if (*this == L)
		return true;
	return false;
}
bool List::operator <= (const List& L)
{

	if (Count < L.Count)
		return true;

	if (*this == L)
		return true;
	return false;
}
bool List::operator > (const List& L)
{
	if (Count > L.Count)
		return true;
	return false;
}
bool List::operator < (const List& L)
{
	if (Count < L.Count)
		return true;
	return false;
}

List List::operator - ()
{
	List Result;
	Elem* temp = Head;

	while (temp != 0)
	{
		Result.AddHead(temp->data);
		temp = temp->next;
	}
	return Result;
}


extern void InputInt(int& n)
{
	int temp = 0;
	cin >> temp;
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Error! Try again!" << endl;
		cin >> temp;
	}
	n = temp;
}