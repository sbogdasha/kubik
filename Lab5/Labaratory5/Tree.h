#pragma once
#include "Element.h"
#include "List.h"



class Tree
{
private:
	Element* root;
public:
	int count = 0;
	Tree()
	{
		root = new Element();
	}

	~Tree()
	{
		Del();
	}

	Element* GetRoot();

	void Print(Element* Node);
	void Insert(Element);
	void Del(Element* Element = 0);

	void GetElementByOrder(Element* Node, List &arrNodes);

	Element* Search(Element* Node, char* key);
	bool SearchW(Element* Node, char* key);
	Element* Min(Element* Node);
	Element* Max(Element* Node);

	Element* Next(Element* Node);
	Element* Previous(Element* Node);

};
