#pragma once
#include <vector>

#include "Top.h"
#include "Edge.h"
using namespace std;

const int MAXSIZE = 50;
const double EPS = 1E-9;
const int INF = 1000000000;

class Graph
{
public:
    Graph(FILE* fp);
    Graph(string newTopsAlph, vector<Top*> newAdjGraphList);
    ~Graph();
    
    //1
    //злиття двох вершин з іменами _t1 _t2 в _t3. Результат новий граф
    Graph* PullOfTops(char _t1, char _t2, char _t3);

    //2
    //діаметр графа
    int Diameter();

    //3
    //хроматичне число 


    //4
    //Детермінант матриці
    double Determinant();

    //5
    //знаходження компонент зв_язності
    int FindConnectivityComps();

    //6
    bool HamiltonCycle(int curr);

    //10
    //мінімальне остівне дерево (алгоритм Пріма)
    void FillMinSpanningTree();
    
    //друк графа
    void printGraph();
    
    //друк компонент зв'язності
    void PrintConnectivityComponent();

    //додати вершину
    void AddTop(char _name);

    //друк матриці суміжності
    void PrintAdjacencyMatrix();

    void PrintHamiltonCycle();
    

private:
    //кількість вершин
    int SizeGraph;
    
    //алфавіт
    string TopsAlphabet;
    
    // список суміжності
    vector<Top*> adjGraphList;

    //матриця суміжності
    double** adjacencyMatrix;

    //компоненти зв'язності
    vector<vector<Top*>> ConnectivityComponents;
    int diameter = 0;
    bool used[MAXSIZE];
    
    //6
    //відвідані вершини
    vector <Top*> PathHamilton;
    //номер ходу на якому відвідується вершина
    int c[MAXSIZE]; 
    //початкова вершина для пошуку цикла Гамільтона
    Top* v0; 
    

    //очищення списку задіяних вершин
    void  ClearUsed(bool u[MAXSIZE]);
    
    //обхід графа (для компонент зв_язнасті)
    void DfsForConnectivityComps(int v, vector<Top*>* comp);

    //сформувати матрицю суміжності за списком суміжності

    //прочитати граф з файлу 
    bool ReadGraph(FILE* fp);

    //клонування графа
    Graph *CloneGraph();

    //формування матриці суміжності
    void FillAdjacencyMatrix();

    int MIN(int a, int b);

};
 
