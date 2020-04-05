#include <iostream>
#include <fstream> 
#include <sstream>
#include <cstdlib>
#include <cstring>


int main(int argc, char* argv[])
{// Чтение матрицы из файла .csv с разделителем "пробел" или "табуляция"
	using namespace std;
	
	struct buffer
	{// Односвязный список, куда будет изначально прочитана вся матрица
		double x;
		buffer* next;
	} *a, *begin, *tmp;

	int n_col = 0; // Количество столбцов 
	int n_row = 0; // Количество строк
	int i = 0, j = 0;
	string s;
	double **matrix;
	
	ifstream fin(argv[1]); // Открыли файл для чтения
	
	a = new buffer; // Создаем начало списка
	begin = a; // Запоминаем ссылку на первый элемент списка
	
	while (true)
	{ // Цикл по строкам файла
		getline(fin, s); // Считываем очередную строку
		if (fin.eof()) break; // Выход из цикла по достижении конца файла
		istringstream st(s); // Открываем строковый поток ввода из прочитанной строки
		while (true) 
		{ // Цикл по строке
			st >> a->x; // Читаем очередное занчение элемента матрицы
			if (!st) break; // Выход из цикла по достижении конца строки
			a->next = new buffer; // Создаем новый элемен списка
			a = a->next; // Переводим указатель на вновь созданный элемент
			j++; // Увеличиваем счетчик прочитанных из строки значений
			if (j > n_col) // Если счетчик не достиг числа столбцов, то
				n_col = j; // обновляем счетчик числа столбцов
		};
		j = 0; // Сбрасываем счетчик столбцов
		i++; // Увеличиваем счетчик строк
		if (i > n_row) // Если счетчик строк не достиг максимума, то 
			n_row = i; // обновляем счетчик числа строк
	};
	fin.close(); // Закрываем файловый поток ввода
	
	matrix = new double*[n_row]; // Создаем двумерный массив для хранения матрицы
	for (i = 0; i < n_row; i++) // Создаем строки матрицы
		matrix[i] = new double[n_col];
		
	a = begin; // Возвращаемся в начало списка
	for (i = 0; i < n_row; i++)
	{ // Копируем списко в созданный ранее двумерный массив
		for (j = 0; j < n_col; j++)
		{
			matrix[i][j] = a->x;
			a = a->next;
		};
	};
	// Выводим матрицу на экран
	cout << "<--- Матрица --->" << endl;
	for (i = 0; i < n_row; i++)
	{
		for (j = 0; j < n_col; j++)
			cout << matrix[i][j] << "\t";
		cout << endl;
	};
	
	cout << endl << "Число элементов " << n_col * n_row << endl;
	
	a = begin; // Возвращаемся в начало списка
	for (i = 0; i < n_col * n_row; i++)
	{ // Удаляем весь список значений элементов матрицы
		tmp = a;
		a = a->next;
		delete tmp;
	};
	
	for (i = 0; i < n_row; i++) // Удаляем массив, где хранится матрица
		delete []matrix[i];
	delete []matrix;
}
