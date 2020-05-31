#pragma once
#include <iostream>
#include <time.h>
#include <fstream>

#include "List.h"

using namespace std;

struct Matrix
{
	short arr[100][100];

	Matrix()
	{
		for (int i = 0; i < 100; i++)
			for (int j = 0; j < 100; j++)
				arr[i][j] = 0;
			
	}

	void Init()
	{
		srand(time(NULL));

		for (int i = 0; i < 100; i++)
			for (int j = 0; j < 100; j++)
			{
				int rnd = rand() % 10;
				if (rnd % 2 == 0 || rnd % 3 == 0 || rnd % 5 == 0 || rnd % 7 == 0) rnd = 0;
				else rnd = rand() % 10;
				arr[i][j] = rnd;
			}
	}

	void WriteMat()
	{
		for (int i = 0; i < 100; i++)
		{
			for (int j = 0; j < 100; j++)
			{
				cout << arr[i][j] << ",";
			}
			cout << endl;
		}
	}
};

void ReadMatrixAndWrite();
void Write();
void FirstStyle();
void SecondStyle();
void AddMatrix();
void MultiplyMatrix();
void LightFile();
