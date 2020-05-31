#pragma once
#include "OOP_Menu.h"
#include "Matrix.h"

class Init
{
private:
	Menu lab3;
public:

	Init()
	{
		lab3.AddMenuItem("Read matrix and write", ReadMatrixAndWrite);
		lab3.AddMenuItem("Write matrix to file", Write);
		lab3.AddMenuItem("Write matrix in first style", FirstStyle);
		lab3.AddMenuItem("Write matrix in second stle", SecondStyle);
		lab3.AddMenuItem("Add two matrix", AddMatrix);
		lab3.AddMenuItem("Multiply two matrix", MultiplyMatrix);
		lab3.AddMenuItem("Write matrix to Light file", LightFile);
	}

	void Show_Lab()
	{
		lab3.ShowMenu();
	}
};