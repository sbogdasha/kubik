#pragma once
#include <iostream>
#include <ostream>
#include <stdio.h>
#include <fstream>
#include "MD5.h"
#include "QA.h"

using namespace std;

enum Role
{
	NewUser, Admin, Tree, Unknow
};

inline int GetId();

class Student
{
public:
	int FKid = GetId();
	char name[20] = { " " };
	char login[33] = { " " };
	char password[33] = { " " };
	Role role;
	bool isEntrInfo = false;

	Student()
	{
		FKid = GetId();
		name[0] = '\0';
		login[0] = '\0';
		password[0] = '\0';
		role = Unknow;
		isEntrInfo = false;
	}

	~Student()
	{
	 
	}
	friend ostream& operator<<(ostream& os, const Student& dt);
};

inline ostream& operator<<(ostream& os, const Student& dt)
{
	os << "Name: " << endl;
	for (int i = 0, j = 0; dt.name[i] != '\0'; i++)
	{
		if (dt.name[i] == ' ') j++;
		if (j > 4) break;
		os << dt.name[i];
	}
	return os;
}

class _Q : Student
{
public:
	int id = Student::FKid;
	char type[33];
	int age = 0, x = 0, y = 0;
	bool isDel = false;
	_Q(int age, int x, int y, char type[33], int id)
	{
		this->id = id;
		this->age = age;
		this->x = x;
		this->y = y;
		strcpy(this->type, type);
	}

	_Q() { 
		this->id = 0;
		this->age = 0;
		this->x = 0;
		this->y = 0;
		this->type[0] = '\0';
	}

	~_Q()
	{
	
	}

	friend ostream& operator<<(ostream& os, const _Q& dt);
};

inline ostream& operator<<(ostream& os, const _Q& dt)
{
	os << endl << "Tree: " << endl;
	os << "Type -> ";
	for (int i = 0; dt.type[i] > 0; i++) os << dt.type[i];
	os << "  X: -> " << dt.x << endl << "Y: -> " << dt.y << "  Age -> " << dt.age << endl;
	return os;
}


void Registration();
void Login();

void LoginAdminMenu();
void Create();
void Show();
void Update();
void Delete();

void DeleteUserInfo(char login[33]);
void DeleteMarks(int id);

void LoginUserMenu(Student& obj);
void SetUp(Student& obj);

int InputMark();

int GetId()
{
	ifstream file("count");
	int temp = 0;
	file >> temp;
	file.close();
	return  temp;
}

inline int SetId()
{
	ifstream file("count");
	int temp = 0;
	file >> temp;
	file.close();
	ofstream fw("count");
	fw << (++temp);
	fw.close();
	return temp;
}

int GetPositionUserInfo(char login[33]);
//int GetPositionMarksInfo(int id);

bool TryUpdate(char login[33], char passsword[32], char name[20], Role, bool isEnteredInfo, int id);
bool TryLogin(char login[33], char passsword[32], Role& role, Student& obj);
bool TryFindUser(char login[33], int& position, Student& obj);
bool TryFindUserMD5(char login[33], int& position, Student& obj);
bool TryCreateUser(char login[33], char passsword[33], char name[20], Role, Student& refObj);
bool TrySaveUserData(_Q que);
bool TryFindUserData(int id, _Q& obj);
bool isNameCorrect(char* name);