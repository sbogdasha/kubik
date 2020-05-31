#pragma once
#include <iostream>
#include <vector>
#include <string>

#include "Tree.h"

using namespace std;

class MenuItem
{
public:
	string title;

	void (*proc)(Tree& dict) = 0;

	MenuItem(string aTitle, void (*procLink)(Tree& dict)) : title(aTitle), proc(procLink) {}
	MenuItem() { title = ""; }

};

class Menu : public MenuItem
{
private:
	string menuTitle;
	vector<MenuItem> menuItems;

	void GetMenuView();
public:

	// Constructors
	Menu()
	{
		menuTitle = "Main menu";
	}
	Menu(string menuTitle)
	{
		this->menuTitle = menuTitle;
	}

	// Interface method
	void AddMenuItem(string itemTitle, void (*procLink)(Tree& dict));
	void ShowMenu(Tree &dict);
};

