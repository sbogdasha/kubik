#pragma once
#include "OOP_Menu.h"
#include "User.h"

class Init
{
private:
	Menu lab1;
public:

	Init()
	{
		lab1.AddMenuItem("Registration", Registration);
		lab1.AddMenuItem("Login", Login);
	}

	Init(int)
	{
		lab1.AddMenuItem("Create", Create);
		lab1.AddMenuItem("Show", Show);
		lab1.AddMenuItem("Update", Update);
		lab1.AddMenuItem("Delete", Delete);
	}


	void Show_Lab()
	{
		lab1.ShowMenu();
	}
};