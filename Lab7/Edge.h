#pragma once
#include "Top.h"
class Edge
{
public:
	Edge(Top* _src, Top* _dest);

	~Edge();

	Top* GetSrc();
	Top* GetDest();
private:
	Top* src;
	Top* dest;
};

