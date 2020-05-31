#include "Edge.h"

Edge::~Edge()
{
	if(&src)
		delete &src;
	if(&dest)
		delete &dest;
}

Top* Edge::GetSrc()
{
	return src;
}

Top* Edge::GetDest()
{
	return dest;
}

Edge::Edge(Top* _src, Top* _dest)
{
	src = _src;
	dest = _dest;
}