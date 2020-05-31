#include "Dictionary.h"
#include <time.h>


void InputDataCh(char arr[64])
{
	string temp = "";
	do
	{
		while (temp == "") getline(cin, temp);
		if (cin.fail() || temp.size() > 33)
		{
			cin.clear();

			temp = "";
			cout << "Fail input! Try again!" << endl;
		}
		else break;
	} while (true);

	for (int i = 0; i < temp.size(); i++) arr[i] = temp[i];
}

void Add(Tree& dict)
{
	srand(time(NULL));
	char eng[64], ukr[64];
	char q;
	while (true)
	{
		for (int i = 0; i < 64; i++)
		{
			eng[i] = '\0';
			ukr[i] = '\0';
		}
		cout << "Input Eng: " << endl;
		InputDataCh(eng);
		if (dict.SearchW(dict.GetRoot(), eng))	
			cout << "Word is exist!" << endl;
		else
		{
			cout << "Input Ukr: " << endl;
			InputDataCh(ukr);
			Element element(eng, ukr, 0);
			dict.Insert(element);
		}
		cout << "If you wanna stop adding, press 1: " << endl;
		cin >> q;
		if (q == '1')
			break;
		else
			system("cls");
	}
}

void Print(Tree& dict)
{
	dict.Print(dict.GetRoot());
}

void Read(Tree& dict)
{
	char eng[64];
	cout << "Input Eng: " << endl;
	InputDataCh(eng);
	dict.Search(dict.GetRoot(), eng);
}

void NewDict(Tree& dict)
{
	List newIndTree;
	Tree newTree;
	Element compare;
	

	dict.GetElementByOrder(dict.GetRoot(), newIndTree);

	for (int i = 0; i < newIndTree.GetCount(); i++)
	{
		if (compare != newIndTree.GetElem(i + 1)->data)
		{
			compare = newIndTree.GetElem(i + 1)->data;
			newTree.Insert(compare);
		}
	}

	cout << "Old Tree: " << endl;
	dict.Print(dict.GetRoot());
	cout << endl << "New Tree: " << endl;
	newTree.Print(newTree.GetRoot());
}
