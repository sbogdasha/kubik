#pragma once
#include <iostream>

using namespace std;

class Element
{
public:
	char eng[64] = { "\0" }, ukr[64] = { "\0" };
	int request = 0;

	Element* left, * right, * parent;

	Element()
	{
		request = -1;
		left = NULL;
		right = NULL;
		parent = NULL;
	}


	Element(char eng[64], char ukr[64], int req)
	{
		strcpy(this->eng, eng);
		strcpy(this->ukr, ukr);
		request = req;
		left = NULL;
		right = NULL;
		parent = NULL;
	}

	~Element()
	{

	}

	void operator = (const Element& el)
	{
		for (int i = 0; i < 64 && (el.eng[i] != '\0' || el.ukr[i] != '\0'); i++)
		{
			eng[i] = el.eng[i];
			ukr[i] = el.ukr[i];
		}
		request = el.request;
		left = el.left;
		right = el.right;
		parent = el.parent;
	}

	bool operator != (const Element& el)
	{
		for (int i = 0; i < 64 && (el.eng[i] != '\0' || el.ukr[i] != '\0'); i++)
		{
			if (eng[i] != el.eng[i] && ukr[i] != el.ukr[i])
				return true;
		}
		if (request = el.request)
			return true;
		
		return false;
	}

	bool operator ! ()
	{
		for (int i = 0; i < 64; i++)
		{
			if (eng[i] != '\0' && ukr[i] != '\0')
				return true;
		}
	
		return false;
	}
};
