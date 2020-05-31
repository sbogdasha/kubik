#include "Matrix.h"

void ReadMatrixAndWrite()
{
	Matrix mat;

	FILE* fp = fopen("matrix", "r");
	if (fp == NULL)
	{
		cout << "File is not exist!" << endl;
		return;
	}

	fseek(fp, 0 * sizeof(Matrix), 0);
	fread(&mat, sizeof(Matrix), 1, fp);
	mat.WriteMat();
	fclose(fp);
}

void Write()
{
	Matrix mat;
	mat.Init();
	FILE* fp = fopen("matrix", "w");
	if (fp == NULL)
	{
		cout << "File is not exist!" << endl;
		return;
	}

	fwrite(&mat, sizeof(Matrix), 1, fp);
	fclose(fp);
}

void FirstStyle()
{
	List list;
	Matrix mat;
	mat.Init();
	mat.WriteMat();
	for (int i = 0; i < 100; i++)
		for (int j = 0; j < 100; j++)
			if (mat.arr[i][j] != 0) list.AddTail(Data(mat.arr[i][j], i, j, 0));
		
	cout << endl << endl << endl;
	list.Print();
}

Matrix SS(List& list)
{
	Matrix mat;
	mat.Init();
	for (int i = 0; i < 100; i++)
		for (int j = 0; j < 100; j++)
			if (mat.arr[i][j] != 0) list.AddTail(Data(mat.arr[i][j], i, j, i / 20));
	return mat;
}
void SecondStyle()
{
	List list;
	Matrix mat = SS(list);
	cout << endl << endl << endl;
	list.Print();
}

void AddMatrix()
{
	Matrix a, b, sum;
	a.Init();
	a.WriteMat();
	cout << endl << endl << endl;
	b.Init();
	b.WriteMat();
	cout << endl << endl << endl;
	for (int i = 0; i < 100; i++)
		for (int j = 0; j < 100; j++)
			sum.arr[i][j] = a.arr[i][j] + b.arr[i][j];
	cout << endl << endl << endl;
	sum.WriteMat();
	cout << endl << endl << endl;
}

void MultiplyMatrix()
{
	Matrix a, b, mult;
	a.Init();
	a.WriteMat();
	cout << endl << endl << endl;
	b.Init();
	b.WriteMat();
	cout << endl << endl << endl;
	for (int i = 0; i < 100; i++)
		for (int j = 0; j < 100; j++)
			for (int k = 0; k < 100; k++)
			{
				mult.arr[i][j] += a.arr[i][k] * b.arr[k][j];
			}
	cout << endl << endl << endl;
	mult.WriteMat();
	cout << endl << endl << endl;
}

void LightFile()
{
	List list;
	Matrix mat = SS(list);
	FILE* fp = fopen("matrix", "w"), *fp2 = fopen("matrixLight", "a+b");
	if (fp == NULL)
	{
		cout << "File is not exist!" << endl;
		return;
	}

	fwrite(&mat, sizeof(Matrix), 1, fp);
	fwrite(&list, sizeof(List), 1, fp2);
	_fcloseall();

	fp = fopen("matrix", "r+b"), fp2 = fopen("matrixLight", "r+b");
	if (fp == NULL || fp2 == NULL)
	{
		cout << "File is not exist!" << endl;
		return;
	}

	fwrite(&mat, sizeof(Matrix), 1, fp);
	fwrite(&list, sizeof(List), 1, fp2);
	mat.WriteMat();
	list.Print();
	_fcloseall();

	ifstream in("matrix", ifstream::ate | ifstream::binary);
	ifstream in2("matrixLight", ifstream::ate | ifstream::binary);

	cout << "Size of matrix: " << in.tellg() << endl << "Size of matrixLight: " << in2.tellg() << endl;
}
