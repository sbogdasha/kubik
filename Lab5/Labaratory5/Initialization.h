#pragma once
#include "OOP_Menu.h"
#include "Dictionary.h" 

class Init
{
private:
	Menu lab5;
public:

	Init()
	{
		lab5.AddMenuItem("Add ", Add);
		lab5.AddMenuItem("Read ", Read);
		lab5.AddMenuItem("Print Dict ", Print);
		lab5.AddMenuItem("Print Old and New ", NewDict);
	}

	void Show_Lab(Tree &dict)
	{
		lab5.ShowMenu(dict);
	}
};