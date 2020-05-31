#include "OOP_Menu.h"

void Menu::GetMenuView()
{
	system("cls");

	for (unsigned int i = 0; i < menuTitle.size() + 20; i++) cout << "=";
		
	cout << endl << "\t" << menuTitle << endl;

	for (unsigned int i = 0; i < menuTitle.size() + 20; i++) cout << "=";
		
	cout << endl;

	int ItemNumber = 1;

	for (vector<MenuItem>::iterator it = menuItems.begin() ; it != menuItems.end(); it++, ItemNumber++)
	{
		cout << ItemNumber << " -> " << it->title << endl;
	}

	cout << endl << "Enter 0 to exit" << endl << endl;

}

void Menu::AddMenuItem(string itemTitle, void (*procLink)())
{
	menuItems.push_back(*(new MenuItem(itemTitle, procLink)));
}

void Menu::ShowMenu()
{
	int itemN = 0;
	while (1)
	{
		try
		{
			GetMenuView();

			itemN = 0;
			string temp = "";
			while (temp == "") getline(cin, temp);
			for (int i = 0; i < temp.size(); i++) itemN += ((temp[i] - 48) * pow(10, i));

			if (itemN == 0) return;

			if (itemN > 0 and itemN <= (int)menuItems.size())
			{
				system("cls");
				menuItems[itemN - 1].proc();
				system("pause");
			}
			else throw false;
		}
		catch (bool exception)
		{
			if (exception)
			{
				cout << "Error in menu!" << endl;
			}
			else
			{
				cout << "Incorrect input!" << endl;
			}
			system("pause");
		}
	}
	
	system("cls");
}
