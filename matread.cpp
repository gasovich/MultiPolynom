#include <iostream>
#include <fstream> 
#include <sstream>
#include <cstdlib>
#include <cstring>


int main(int argc, char* argv[])
{
	using namespace std;
	
	struct buffer
	{
		double x;
		buffer* next;
	} *a, *begin;

	int n_col = 0;
	int n_row = 0;
	int i = 0, j = 0;
	string s;
	double **matrix;
	
	ifstream fin(argv[1]); // Открыли файл для чтения
	
	a = new buffer;
	begin = a;
	
	while (true)
	{
		getline(fin, s);
		if (fin.eof()) break;
		istringstream st(s);
		while (true) 
		{
			st >> a->x;
			if (!st) break;
			a->next = new buffer;
			a = a->next;
			j++;
			if (i == 0)
				n_col = j;
		};
		j = 0;
		i++;
		if (i > n_row)
			n_row = i;
	};
	fin.close();
	
	matrix = new double*[n_row];
	for (i = 0; i < n_row; i++)
		matrix[i] = new double[n_col];
		
	a = begin;
	for (i = 0; i < n_row; i++)
	{
		for (j = 0; j < n_col; j++)
		{
			matrix[i][j] = a->x;
			a = a->next;
		};
	};
		
	cout << "<--- Матрица --->" << endl;
	for (i = 0; i < n_row; i++)
	{
		for (j = 0; j < n_col; j++)
			cout << matrix[i][j] << "\t";
		cout << endl;
	};
	
	for (i = 0; i < n_row; i++)
		delete []matrix[i];
	delete []matrix;
}
