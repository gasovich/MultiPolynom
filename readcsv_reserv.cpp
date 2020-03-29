/* Чтение данных из файла формата .CSV */
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream> 

using namespace std;

const int LENGHT_OF_POLYNOM = 50; // Максимальное количество одночленов в полиноме

struct multipolynom
{
	string* vars; // Имена переменных
	float factor[LENGHT_OF_POLYNOM]; // Коэффициенты при мономах
	float* values;
	int* monom[LENGHT_OF_POLYNOM]; // Степени переменных в мономе
	int num_of_vars; // Количество переменных
	int num_of_terms; // Количество одночленов
};

string* read_var_names(string filename, int &num_of_vars)
{// Чтение имен переменных из первой строки файла
	string s;// Временная строка
	char var_name[50][10]; // Массив с именами переменных
	string* result;
	
	ifstream fin(filename); // Открыли файл для чтения
	fin >> s; // Прочитали первую строку, где содержатся имена переменных
	fin.close(); // Закрыли файл
	
	int i = 0;
	int i_name = 0; // Индекс по массиву var_name - номер текущей переменной
	int first_sym; // Первый символ первого имени переменной
	// Ищем первое вхождение в s символа ";" (точка с запятой) и отбрасываем эту часть
	while (s[i] != 0 && s[i] != ';' )
		i++;
	first_sym = ++i;
	
	// Пока не найден конец строки
	while (s[first_sym] != 0)
	{
		i = 0;
		// Копируем символы из входной строки в массив с именами переменных до появления символа ";"
		while ((s[first_sym] != 0) && (s[first_sym] != ';'))
		{
			var_name[i_name][i] = s[first_sym];
			first_sym++; // счетчик по входной строке
			i++; // счетчик символов в имени переменной
		};
		var_name[i_name][i] = 0; // Вставляем конец строки после очередного имени переменной
		i_name++; // Переходим к новой переменной
		first_sym++; // Пропускаем символ ";"
	};
	num_of_vars = i_name;
	
	result = new string[num_of_vars];
	for (i = 0; i < num_of_vars; i++)
	{
		result[i] = new char[strlen(var_name[i])];
		result[i] = var_name[i];
	};
	return result;
};

void read_values(string filename, multipolynom &a)
{// Чтение значений переменных из второй строки файла
};

void read_powers(string filename, multipolynom &a)
{// Чтение коэффициентов при одночленах и степеней переменных из третьей и последующих строк
	
	string s;
	string tmp_factor;
	string tmp_power;
	int i = 0;
	int j = 0;
	int i_monom = 0;
	int i_factor = 0;

	
	ifstream fin(filename); // Открыли файл для чтения
	fin >> s; // Пропускаем строку с именами переменных
	fin >> s; // Пропускаем строку со значениями переменных
	
	// Цикл по файлу
	while (!fin.eof())
	{
		i = 0; // Сбрасываем счетчик символов по строке s
		fin >> s; // Прочитали следующую строку, где коэффициент монома и степени переменных
		if(fin.eof()) break; // Избегаем двойного чтения последней строки файла
		
		// Цикл по строке
		while (s[i] != ';' && s[i] != 0)
		{// Читаем первый элемент строки, содержащий вещественное число - коэффициент при мономе
			tmp_factor += s[i];
			i++;
		};
		i++;
		
		// Преобразуем строку в вещественное значение и сохраняем ее в массиве коэфифциентов
		// Если строка со значением коэффициента пустая, то коэффициент равен 0
		if(tmp_factor.size() == 0)
				a.factor[i_monom] = 0;
			else
				a.factor[i_monom] = stod(tmp_factor);
		
		tmp_factor = "";
		
		a.monom[i_monom] = new int[a.num_of_vars]; // Создаем новый моном с длиной равной количеству переменных
		for( int k = 0; k < a.num_of_vars; k++) // Теперь идем до конца строки и читаем целые числа - степени переменных
		{
			while (s[i] != ';' && s[i] != 0)
			{
				tmp_power += s[i];
				i++;
			};
			i++;
			if(tmp_power.size() == 0)
				a.monom[i_monom][k] = 0;
			else
				a.monom[i_monom][k] = stoi(tmp_power);
			tmp_power = "";
		};
		i_monom++;
	};
	fin.close(); // Закрыли файл
	a.num_of_terms = i_monom;
};

int main()
{
	int n;
	multipolynom a;
	string filename = "poly1.csv";
	
	a.vars = read_var_names(filename, n);
	a.num_of_vars = n;
	cout << "-------------------------\n";
	cout << n << " переменных:"<< endl;
	for (int i = 0; i < a.num_of_vars; i++)
		cout << a.vars[i] << "  ";
	cout << endl;
	
	cout << "-------------------------\n";
	read_powers(filename, a);
	cout << a.num_of_terms << " одночленов:"<< endl;
	for (int i = 0; i < a.num_of_terms; i++)
	{
		cout << a.factor[i] << "\t";
		for (int j = 0; j < n; j++)
			cout << a.monom[i][j] << "\t";
		cout << endl;
	};
	cout << endl;
}
	
