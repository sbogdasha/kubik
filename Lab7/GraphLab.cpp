// GraphLab.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Graph.h"

int main()
{
    FILE* fp = new FILE();
    Graph *gr = new Graph(fp);
    gr->printGraph();
    gr->FindConnectivityComps();
    gr->PrintConnectivityComponent();
    gr->PrintAdjacencyMatrix();
    cout << "Diameter: " <<gr->Diameter() << endl;
    cout << "Determinant: " << gr->Determinant() << endl;
//    gr->HamiltonCycle(0);
    gr->PrintHamiltonCycle();
    gr->FillMinSpanningTree();
    cout << "Sort" << endl;
   // gr->bubbleSort();
  //  gr->shellSort();
  //  gr->insertionSort();
    gr->CocktailSort();
    gr->printGraph();


    Graph *pullGr = gr->PullOfTops('a', 'b', 'h');
    cout << "PullOfTops('a', 'b', 'h'): ";
    pullGr->printGraph();
    pullGr->PrintAdjacencyMatrix();
    pullGr->PrintHamiltonCycle();
    cout << "Diameter: " << pullGr->Diameter() << endl;
    cout << "Determinant: " << pullGr->Determinant() << endl;
    pullGr->FillMinSpanningTree();
    
}