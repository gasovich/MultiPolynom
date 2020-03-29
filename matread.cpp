#include <iostream>
#include <fstream> 
#include <sstream>
#include <cstdlib>
#include <cstring>

using namespace std;

int main()
{
	int n_col = 0;
	int n_row = 0;
	int** matrix;
	double x;
	string s;
	
	ifstream fin("matrix2.csv"); // Открыли файл для чтения
	getline(fin, s);
	fin.close();
	
	istringstream st(s);
	while (true) 
	{
		st >> x;
		if (!st) break;
		cout << "x = " << x << "\t" << n_col << endl;
		n_col++;
	};
	cout << "Прочитано " << n_col << " значений\n";
}
