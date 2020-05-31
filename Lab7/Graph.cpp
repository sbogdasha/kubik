#include "Graph.h"

Graph::Graph(FILE* fp)
{
	if (ReadGraph(fp))
		cout << "Correct read Graph. ";
	else
		cout << "Incorrect read Graph. ";

	ConnectivityComponents.clear();
	adjacencyMatrix = nullptr;
	*used = new bool[MAXSIZE];
	ClearUsed(used);
}

Graph::Graph(string newTopsAlph, vector<Top*> newAdjGraphList)
{
	TopsAlphabet = newTopsAlph;

	SizeGraph = TopsAlphabet.length();

	adjGraphList = newAdjGraphList;
	adjacencyMatrix = nullptr;
	ConnectivityComponents.clear();
	*used = new bool[MAXSIZE];
	ClearUsed(used);
}

Graph::~Graph()
{
	adjGraphList.clear();
	ConnectivityComponents.clear();
	delete &TopsAlphabet;

	for (int i = 0; i < SizeGraph; i++)
		delete[] adjacencyMatrix[i];
	delete[]adjacencyMatrix;
}

void Graph::FillMinSpanningTree()
{
	ClearUsed(used);
	FillAdjacencyMatrix();
	vector<int> min_e(SizeGraph, INF), sel_e(SizeGraph, -1);
	min_e[0] = 0;
	cout << "Mininal Spanning Tree: \n";
	for (int i = 0; i < SizeGraph; ++i) {
		int v = -1;
		for (int j = 0; j < SizeGraph; ++j)
			if (!used[j] && (v == -1 || min_e[j] < min_e[v]))
				v = j;
		if (min_e[v] == INF) {
			cout << "No Mininal Spanning Tree!";
			exit(0);
		}
		
		used[v] = true;
		if (sel_e[v] != -1)
		{
			cout << TopsAlphabet[v] << " " << TopsAlphabet[sel_e[v]] << endl;
			
		}
		for (int to = 0; to < SizeGraph; ++to)
			if (adjacencyMatrix[v][to] < min_e[to]) {
				min_e[to] = adjacencyMatrix[v][to];
				sel_e[to] = v;
			}
	}	
}

void Graph::printGraph()
{
	cout << "Alphabet: " << TopsAlphabet << " ";	

	for (int i = 0; i < SizeGraph; i++)
	{
		// друк поточної вершини
		adjGraphList[i]->printTop();		
	}
}

//детермінант методм Гауса
double Graph::Determinant()
{	
	double det = 1;
	FillAdjacencyMatrix();
	for (int i = 0; i < SizeGraph; ++i) {
		int k = i;
		for (int j = i + 1; j < SizeGraph; ++j)
			if (abs(adjacencyMatrix[j][i]) > abs(adjacencyMatrix[k][i]))
				k = j;
		if (abs(adjacencyMatrix[k][i]) < EPS) {
			det = 0;
			break;
		}
		swap(adjacencyMatrix[i], adjacencyMatrix[k]);
		if (i != k)
			det = -det;
		det *= adjacencyMatrix[i][i];
		for (int j = i + 1; j < SizeGraph; ++j)
			adjacencyMatrix[i][j] /= adjacencyMatrix[i][i];
		for (int j = 0; j < SizeGraph; ++j)
			if (j != i && abs(adjacencyMatrix[j][i]) > EPS)
				for (int k = i + 1; k < SizeGraph; ++k)
					adjacencyMatrix[j][k] -= adjacencyMatrix[i][k] * adjacencyMatrix[j][i];
	}
	return det;	
}

//пошук компонент зв'язності. Результат кількість компонент зв'язності
//5
int Graph::FindConnectivityComps()
{		
	//у випадку, якщо компоненти зв'язності ще не знайдено - шукаємо їх
		if (ConnectivityComponents.size() == 0)
		{
			//ініціалізація інформації про перевірені вершини
			ClearUsed(used);

			//для усіх незадіяних вершин шукаємо компоненти зв'язності
			for (int i = 0; i < SizeGraph; ++i)
				if (!used[i]) {
					vector<Top*> comp;// = new vector<int>;
					comp.clear();
					DfsForConnectivityComps(i, &comp);
					ConnectivityComponents.push_back(comp);
				}
		};
		return ConnectivityComponents.size();
	
}

void Graph::ClearUsed(bool u[MAXSIZE])
{
	for (int i = 0; i < SizeGraph; ++i)
		u[i] = false;
}

void Graph::DfsForConnectivityComps(int v, vector<Top*> *comp)
{
	used[v] = true;	
	comp->push_back(adjGraphList[v]);	

	for (size_t i = 0; i < (adjGraphList[v]->Size()); ++i) {
		Top* to = adjGraphList[v]->GetAdjTopByNum(i);
		int j = TopsAlphabet.find(to->GetName());
		if ((j >= 0) && (j <= SizeGraph))
		{
			if (!used[j])
				DfsForConnectivityComps(j, comp);
		}
	}
}


//зчитування графа з файла
bool Graph::ReadGraph(FILE* fp)
{	
	char first, second;
	char c[200];
	int pos1, pos2;
	if (fp = fopen("graph.txt", "r"))
	{
		//зчитуємо алфавіт
		fscanf(fp, "%s\n", &c);
		TopsAlphabet = c;

SizeGraph = TopsAlphabet.length();
adjGraphList.resize(SizeGraph);

if (SizeGraph > 0)
{
	for (int i = 0; i < SizeGraph; i++)
	{
		//створюємо вершини
		Top* t = new Top(TopsAlphabet[i]);
		adjGraphList[i] = t;
	};

	while (fscanf(fp, "%c-%c\n", &first, &second) != EOF)
	{
		pos1 = TopsAlphabet.find(first);
		pos2 = TopsAlphabet.find(second);
		if ((pos1 >= 0) && (pos2 >= 0))					
		{			
			adjGraphList[pos1]->AddEdge(adjGraphList[pos1], adjGraphList[pos2]);

			//якщо граф неорієнтований, то додати в обидві сторони
			/*
			adjGraphList[pos2].AddEdge(&adjGraphList[pos2], &adjGraphList[pos1]);
			*/
		}
		else
		{
			fclose(fp);
			return false;
		}
	}
}
else
{
	fclose(fp);
	return false;
}
fclose(fp);
return true;
	}

	return false;
}

Graph* Graph::CloneGraph()
{
	string* newAlphabet = new string(TopsAlphabet);

	vector<Top*>* newAdjGraphLis = new vector<Top*>;
	newAdjGraphLis->resize(TopsAlphabet.size());
	//ініцілізація вектора вершинами
	for (int i = 0; i < SizeGraph; i++)
	{
		//створюємо вершини
		Top* t = new Top((*newAlphabet)[i]);
		(*newAdjGraphLis)[i] = t;
	};

	//за усіма вершинами клонуємо вектори суміжності
	for (int i = 0; i < SizeGraph; i++)
	{
		Top* t = adjGraphList[i];

		for (int j = 0; j < t->Size(); j++)
		{
			char c = t->GetAdjTopByNum(j)->GetName();
			Top* tn = (*newAdjGraphLis)[TopsAlphabet.find(c)];
			
			(*newAdjGraphLis)[i]->AddEdge((*newAdjGraphLis)[i], tn);
		}
	}

	Graph* gr = new Graph(*newAlphabet, *newAdjGraphLis);
	return gr;
}

//заповнення матриці суміжності int** adjacencyMatrix;
void Graph::FillAdjacencyMatrix()
{
	//у випадку, якщо матрицю суміжності ще не знайдено
	if (adjacencyMatrix == nullptr)
	{
		//виділили пам_ять під матрицю потрібного розміру
		adjacencyMatrix = new double* [SizeGraph];

		//створення елементів та заповнення матриці "0"
		for (int i = 0; i < SizeGraph; i++)
		{
			adjacencyMatrix[i] = new double[SizeGraph];
			for (int j = 0; j < SizeGraph; j++)
			{
				adjacencyMatrix[i][j] = 0.0;
			}
		}
	}
	else
	{
		for (int i = 0; i < SizeGraph; i++)
		{
			adjacencyMatrix[i] = new double[SizeGraph];
			for (int j = 0; j < SizeGraph; j++)
			{
				adjacencyMatrix[i][j] = 0.0;
			}
		}
	};

		//заповнення "1" за ребрами у векторі суміжності
		for (int i = 0; i < SizeGraph; i++)
		{
			Top *t = adjGraphList[i];
			//за усіма зв_язкими вершини i
			for (int j = 0; j < t->Size(); j++)
			{				
				char c = t->GetAdjTopByNum(j)->GetName();
				int k = TopsAlphabet.find(c);
				adjacencyMatrix[i][k]++;
			}
		}				
}

int Graph::MIN(int a, int b)
{
	return (a > b ? b : a);
}

void Graph::PrintAdjacencyMatrix()
{
	if (adjacencyMatrix == nullptr)
	{
		FillAdjacencyMatrix();
	};
	for (int i = 0; i < SizeGraph; i++)
	{
		for (int j = 0; j < SizeGraph; j++)
		{
			cout << adjacencyMatrix[i][j] << " ";
		}
		cout << "\n";
	}
}

void Graph::PrintHamiltonCycle()
{
	int numv0 = 0, curr = 1;
	FillAdjacencyMatrix();
	v0 = adjGraphList[numv0];
	
	for (int i = 0; i < SizeGraph; i++)
	{
		c[i] = -1;
	}
	PathHamilton.push_back(v0);
	c[numv0] = numv0;


	if (HamiltonCycle(curr))
	{
		cout << "Hamilton Cycle: " << endl;
		for (int i = 0; i < PathHamilton.size(); i++)
			cout << PathHamilton[i]->GetName() << " ";
		cout << endl;
	}

	else
		cout << "No Hamilton Cycle " << endl;
}

void Graph::PrintConnectivityComponent()
{
	int count = FindConnectivityComps();
	cout << "Connectivity Components: ";
	for (size_t i = 0; i < ConnectivityComponents.size(); ++i) {
		cout << "Connectivity Component #: " << i + 1 << ": ";

		for (size_t j = 0; j < ConnectivityComponents[i].size(); ++j)
			cout << " " << ConnectivityComponents[i][j]->GetName();
		cout << endl;
	}
}

//1: злиттся двох вершин _t1 та _t2 в _t3
Graph* Graph::PullOfTops(char _t1, char _t2, char _t3)
{
	Graph* newGr =nullptr;
	int i = TopsAlphabet.find(_t1);
	int j = TopsAlphabet.find(_t2);
	int k = TopsAlphabet.find(_t3);
	if ((i >= 0) && (i == j == k)) //зливаємо вершину саму з собою в себе - нічого не відбувається ))
	{
		newGr = CloneGraph();
		return newGr;
	};

	if ((i >= 0) && (j >= 0) && (k < 0)) //існують зливаємі вершини та не існує вершини куди зливають
	{
		if (i == j) //зливаємо вершину саму із собою, але з переіменуванням в _t3
		{
			newGr = CloneGraph();
			(newGr->adjGraphList[i])->Rename(_t3);
		}
		else
		{
			newGr = CloneGraph();
			newGr->AddTop(_t3);

			Top* t1 = newGr->adjGraphList[i];
			Top* t2 = newGr->adjGraphList[j];
			Top* t3 = newGr->adjGraphList[(newGr->SizeGraph-1)];

			//додаємо новій вершини усі вихідні ребра двох попередніх
			for (int l = 0; l < t1->Size(); l++)
			{
				t3->AddEdge(t3, t1->GetAdjTopByNum(l));
			};
			for (int l = 0; l < t2->Size(); l++)
			{
				t3->AddEdge(t3, t2->GetAdjTopByNum(l));
			};
			//переадресовуємо старі вершини на нову замість попередніх
			for (int l = 0; l < newGr->SizeGraph; l++)
			{
				Top* t4 = newGr->adjGraphList[l];
				t4->RedirectAdj(t1, t3);
				t4->RedirectAdj(t2, t3);
			};
			if (i > j)
			{
				newGr->adjGraphList.erase(newGr->adjGraphList.begin() + i);
				newGr->adjGraphList.erase(newGr->adjGraphList.begin() + j);

				newGr->TopsAlphabet.erase(i, 1);
				newGr->TopsAlphabet.erase(j, 1);
			}
			else
				if (j > i)
				{
					newGr->adjGraphList.erase(newGr->adjGraphList.begin() + j);
					newGr->adjGraphList.erase(newGr->adjGraphList.begin() + i);
					
					newGr->TopsAlphabet.erase(j, 1);
					newGr->TopsAlphabet.erase(i, 1);					
				}
				else //i == j
				{
					newGr->adjGraphList.erase(newGr->adjGraphList.begin() + i);
					newGr->TopsAlphabet.erase(i, 1);
				}
		}
	}
	newGr->SizeGraph = newGr->adjGraphList.size();
	return newGr;
}

//діаметр
int Graph::Diameter()
{
	FillAdjacencyMatrix();
	int** edge = new int* [SizeGraph];
	for (int i = 0; i < SizeGraph; i++)
		edge[i] = new int[SizeGraph];
	for (int i = 0; i < SizeGraph; i++)
	{
		for (int j = 0; j < SizeGraph; j++) {
			edge[i][j] = adjacencyMatrix[i][j];
			if (!edge[i][j])
				edge[i][j] = 10000;
		}
	}

	for (int k = 0; k < SizeGraph; k++)
		for (int i = 0; i < SizeGraph; i++)
			for (int j = 0; j < SizeGraph; j++)
				if (i != j)
					edge[i][j] = MIN(edge[i][j], edge[i][k] + edge[k][j]);
	for (int i = 0; i < SizeGraph; i++) {
		for (int j = 0; j < SizeGraph; j++) {
			if (edge[i][j] == 10000)
				edge[i][j] = 0;
		}
	}
	int max = edge[0][1];
	for (int i = 0; i < SizeGraph; i++)
	{
		for (int j = i + 1; j < SizeGraph; j++) {
			if (edge[i][j] > max)
				max = edge[i][j];
		}
	}

	diameter = max;
	delete[] edge;
	return max;
}

void Graph::AddTop(char _name)
{
	TopsAlphabet.push_back(_name);
	Top* t = new Top(_name);
	adjGraphList.push_back(t);
	SizeGraph++;
}

bool Graph::HamiltonCycle(int k)
{	
	int q1 = 0;
	for (int v = 0; v < SizeGraph && !q1; v++)
	{		
		int pk = TopsAlphabet.find(PathHamilton[k - 1]->GetName());
		int numv0 = TopsAlphabet.find(v0->GetName());
			
		if (adjacencyMatrix[v][pk] || adjacencyMatrix[pk][v])
		{
			
			if (k == SizeGraph && v == numv0) q1 = 1;
			else if (c[v] == -1)
			{
				c[v] = k; 
				PathHamilton.push_back(adjGraphList[v]);
				q1 = HamiltonCycle(k + 1);
				if (!q1) c[v] = -1;
			}
			else continue;
		}
	}   	
	return q1;
}


void Graph::insertionSort()
{
	int key, j;
	for (int i = 1; i < SizeGraph; i++)
	{
		key = adjGraphList[i]->Size();
		j = i - 1;


		while (j >= 0 && adjGraphList[j]->Size() > key)
		{
			adjGraphList[j + 1] = adjGraphList[j];

			j = j - 1;
		}
		adjGraphList[j + 1] = adjGraphList[i];
		//	arr[j + 1] = key;
	}
}

void Graph::bubbleSort()
{
	for (size_t i = 0; i < SizeGraph - 1; ++i)
		for (size_t j = 0; j < SizeGraph - i - 1; ++j)
			// Last i elements are already in place  			
			if (adjGraphList[j]->Size() > adjGraphList[j + 1]->Size())
				swap(adjGraphList[j], adjGraphList[j+1]);
}



int Graph::shellSort()
{
	// Start with a big gap, then reduce the gap 
	for (int gap = SizeGraph / 2; gap > 0; gap /= 2)
	{
		// Do a gapped insertion sort for this gap size. 
		// The first gap elements a[0..gap-1] are already in gapped order 
		// keep adding one more element until the entire array is 
		// gap sorted  
		for (int i = gap; i < SizeGraph; i += 1)
		{
			// add a[i] to the elements that have been gap sorted 
			// save a[i] in temp and make a hole at position i 
			Top *temp = adjGraphList[i];
			// shift earlier gap-sorted elements up until the correct  
			// location for a[i] is found 
			int j;
			for (j = i; j >= gap && adjGraphList[j - gap]->Size() > temp->Size(); j -= gap)
				adjGraphList[j] = adjGraphList[j - gap];

			//  put temp (the original a[i]) in its correct location 
			adjGraphList[j] = temp;
		}
	}
	return 0;
}

	void Graph::CocktailSort()
	{
		bool swapped = true;
		int start = 0;
		int end = SizeGraph - 1;

		while (swapped) {
			// reset the swapped flag on entering 
			// the loop, because it might be true from 
			// a previous iteration. 
			swapped = false;

			// loop from left to right same as 
			// the bubble sort 
			for (int i = start; i < end; ++i) {
				if (adjGraphList[i]->Size() > adjGraphList[i + 1]->Size()) {
					swap(adjGraphList[i], adjGraphList[i + 1]);
					swapped = true;
				}
			}

			// if nothing moved, then array is sorted. 
			if (!swapped)
				break;

			// otherwise, reset the swapped flag so that it 
			// can be used in the next stage 
			swapped = false;

			// move the end point back by one, because 
			// item at the end is in its rightful spot 
			--end;

			// from right to left, doing the 
			// same comparison as in the previous stage 
			for (int i = end - 1; i >= start; --i) {
				if (adjGraphList[i]->Size() > adjGraphList[i + 1]->Size()) {
					swap(adjGraphList[i], adjGraphList[i + 1]);
					swapped = true;
				}
			}

			// increase the starting point, because 
			// the last stage would have moved the next 
			// smallest number to its rightful spot. 
			++start;
		}
	}

