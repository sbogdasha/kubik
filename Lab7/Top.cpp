#include "Top.h"

Top::~Top()
{
	delete &name;
//	edges.clear();
	adjList.clear();	
}

char Top::GetName()
{
	return name;
}

//додати ребро з цією вершиною
bool Top::AddEdge(Top* t1, Top* t2)
{	
		
	if ((t1 != NULL) && (t2 != NULL))
	{
		if (t1->name == name)
		{
			adjList.push_back(t2);
		}
		else
			if (t2->name == name)
			{
				adjList.push_back(t1);
			}
	}
	return false;
}



void Top::printTop()
{
	cout << "Top: " << name << " --> ";
	for (size_t i = 0; i < adjList.size(); i++)
		cout << adjList[i]->GetName() << " ";
	cout << endl;
}

int Top::Size()
{
	return adjList.size();
}

Top* Top::GetAdjTopByNum(int _num)
{
	if (_num < adjList.size())
		return adjList[_num];
	else return NULL;
}

void Top::Rename(char c)
{	
	name = c;
}

void Top::RedirectAdj(Top* t1, Top* t2)
{
	for (int i = 0; i < Size(); i++)
	{
		if (adjList[i] == t1) adjList[i] = t2;
	}
}


Top::Top()
{
	name = ' ';
}

Top::Top(char _name)
{	
	name = _name;
}