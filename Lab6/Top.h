#pragma once
#include <string>
#include <iostream>
#include <vector>


using namespace std;
class Top
{
	
public:
	Top();
	Top(char _name);
	~Top();
	char GetName();
	bool AddEdge(Top *t1, Top *t2);
	void printTop();
	int Size();
	Top* GetAdjTopByNum(int _num);

	void Rename(char c);
	//?????????????? ??? ??'???? ? t1 ?? t2
	void RedirectAdj(Top* t1, Top* t2);

private:
	char name;

	vector<Top*> adjList;

};

