#include "Tree.h"

bool CompareStrByAlph(char str1[64], char str2[64])
{
	for (int i = 0; i < 64; i++)
	{
		if (strlen(str1) == i || strlen(str2) == i)
			if (strlen(str1) < strlen(str2))
				return true;
			else
				return false;

		if (str1[i] < str2[i])
			return true;
		else if (str1[i] != str2[i])
			return false;
	}

	return false;
}

bool CompareStr(char str1[64], char str2[64])
{
	if (str2[0] == '\0')
		return false;

	for (int i = 0; str1[i] > 0 && str2[i] > 0; i++)
	{
		if (str1[i] != str2[i])
			return false;

		if (str1[i + 1] < 0 && str2[i + 1] > 0 || str2[i + 1] < 0 && str1[i + 1] > 0)
			return false;
	}

	return true;
}
 
void Tree::Print(Element* Node)
{
	if (Node != 0)
	{
		Print(Node->left);
		cout << "Eng: " << Node->eng << endl << "Ukr: " << Node->ukr
			<< endl << "Requests: " << Node->request << endl;
		Print(Node->right);
	}
}

void Tree::GetElementByOrder(Element* Node, List& arrNodes)
{
	if (Node != 0)
	{
		Element tmp = *Node;
		tmp.left = NULL;
		tmp.right = NULL;
		tmp.parent = NULL;
		GetElementByOrder(Node->left, arrNodes);
		int pos = 1;
		bool flag = true;
		if (arrNodes.GetCount() != 0)
		{
			for (int i = 0; i < arrNodes.GetCount(); i++)
			{
				if (Node->request < arrNodes.GetElem(i + 1)->data.request && Node->eng != arrNodes.GetElem(i + 1)->data.eng)
					pos++;
				else
				{
					flag = false;
					arrNodes.Insert(pos, tmp);
					break;
				}
			}
			if (flag)
				arrNodes.AddTail(tmp);
		}
		else
			arrNodes.AddHead(tmp);
		GetElementByOrder(Node->right, arrNodes);
	}
}

Element* Tree::Search(Element* Node, char* key)
{
	while (Node != 0)
	{
		if (CompareStr(key, Node->eng))
			break;
		if (CompareStrByAlph(key, Node->eng))
			Node = Node->left;
		else
			Node = Node->right;
	}

	Node->request++;
	cout << "Eng: " << endl
		<< Node->eng << endl << "Ukr: " << endl
		<< Node->ukr << endl << "Requests: " << endl
		<< Node->request << endl;

	return Node;
}

bool Tree::SearchW(Element* Node, char* key)
{
	while (Node != 0)
	{
		if (CompareStr(key, Node->eng))
			return true;
		if (CompareStrByAlph(key, Node->eng))
			Node = Node->left;
		else
			Node = Node->right;
	}


	return false;
}

Element* Tree::Min(Element* Node)
{
	if (Node != 0)
		while (Node->left != 0)
			Node = Node->left;
	return Node;
}

Element* Tree::Max(Element* Node)
{
	if (Node != 0)
		while (Node->right != 0)
			Node = Node->right;
	return Node;
}

Element* Tree::Next(Element* Node)
{
	Element* temp = 0;
	if (Node != 0)
	{
		if (Node->right != 0)
			return Min(Node->right);
		temp = Node->parent;
		while (temp != 0 && Node == temp->right)
		{
			Node = temp;
			temp = temp->parent;
		}
	}
	return temp;
}

Element* Tree::Previous(Element* Node)
{
	Element* temp = 0;
	if (Node != 0)
	{
		if (Node->left != 0)
			return Max(Node->left);
		temp = Node->parent;
		while (temp != 0 && Node == temp->left)
		{
			Node = temp;
			temp = temp->parent;
		}
	}
	return temp;
}

Element* Tree::GetRoot()
{
	return root;
}

void Tree::Insert(Element Elementent)
{
	count++;
	Element* temp = NULL;
	Element* Node = root;

	if (root->request != -1)
		while (Node != 0)
		{
			temp = Node;
			if (CompareStrByAlph(Elementent.eng, Node->eng) > 0)
				Node = Node->left;
			else
				Node = Node->right;
		}

	Elementent.parent = temp;

	if (temp == 0)
		*root = Elementent;
	else if (CompareStrByAlph(Elementent.eng, temp->eng) > 0)
	{
		temp->left = new Element();
		*temp->left = Elementent;
	}
	else
	{
		temp->right = new Element();
		*temp->right = Elementent;
	}
}

void Tree::Del(Element* Elementent)
{
	if (Elementent != 0)
	{
		count--;
		Element* Node, * temp;

		Elementent->left == 0 || Elementent->right == 0 ?
			temp = Elementent :
			temp = Next(Elementent);

		temp->left != 0 ?
			Node = temp->left :
			Node = temp->right;

		if (Node != 0)
			Node->parent = temp->parent;

		if (temp->parent == 0)
			root = Node;
		else if (temp == temp->parent->left)
			temp->parent->left = Node;
		else
			temp->parent->right = Node;

		if (temp != Elementent)
		{
			strcpy(Elementent->eng, temp->eng);
			strcpy(Elementent->ukr, temp->ukr);
			Elementent->request = temp->request;
		}
		delete temp;
	}
	else while (root != 0)
		Del(root);
}
