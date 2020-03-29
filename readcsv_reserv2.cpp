/* Чтение данных из файла формата .CSV */
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream> 
#include <cmath>

using namespace std;

const int LENGHT_OF_POLYNOM = 50; // Максимальное количество одночленов в полиноме

struct multipolynom
{
	string* vars; // Имена переменных
	double factor[LENGHT_OF_POLYNOM]; // Коэффициенты при мономах
	double values[LENGHT_OF_POLYNOM]; // Значения переменных
	int* monom[LENGHT_OF_POLYNOM]; // Степени переменных в мономе
	int num_of_vars; // Количество переменных
	int num_of_terms; // Количество одночленов
};

void read_var_names(string filename, multipolynom &a)
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
	a.num_of_vars = i_name;
	
	a.vars = new string[a.num_of_vars];
	for (i = 0; i < a.num_of_vars; i++)
	{
		a.vars[i] = new char[strlen(var_name[i])];
		a.vars[i] = var_name[i];
	};
};

void read_values(string filename, multipolynom &a)
{// Чтение значений переменных из второй строки файла
	string s;
	string tmp_value = "";
	int i = 0;
	int i_monom = 0;
	
	ifstream fin(filename); // Открыли файл для чтения
	fin >> s; // Пропускаем строку с именами переменных
	fin >> s; // Сохраняем строку со значениями переменных
	fin.close(); // Закрыли файл
	
	// Ищем первое вхождение в s символа ";" (точка с запятой) и отбрасываем эту часть
	while (s[i] != 0 && s[i] != ';' )
		i++;
	i++; // Пропускаем символ-разделитель ";"
	
	while (s[i] != ';' && s[i] != 0)
	{// Цикл по осташейся части строки
		while (s[i] != ';' && s[i] != 0)
			{// Читаем очередное значение переменной из строки
				tmp_value += s[i];
				i++;
			};
			if (s[i] != 0)
				i++;
			// Преобразуем строку в вещественное значение и сохраняем ее в массиве коэфифциентов
			// Если строка со значением коэффициента пустая, то коэффициент равен 0
			if(tmp_value.size() == 0)
					a.values[i_monom] = 0;
				else
					a.values[i_monom] = stod(tmp_value);
			//cout << "Число = " << a.values[i_monom] << endl;
			tmp_value = "";
			i_monom++;
	};
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

void create_polynom(string filename, multipolynom &a)
{// Создание полимона из файла
	read_var_names(filename,a);
	read_powers(filename, a);
	read_values(filename, a);
};

void show_polynom(multipolynom &a)
{ // Вывод полинома на экран
	cout << "\t";
	for (int i = 0; i < a.num_of_vars; i++)
		cout << a.vars[i] << "\t";
	cout << endl;
	
	for (int i = 0; i < a.num_of_terms; i++)
	{
		cout << a.factor[i] << "\t";
		for (int j = 0; j < a.num_of_vars; j++)
			cout << a.monom[i][j] << "\t";
		cout << endl;
	};
	
	cout << endl;
	cout << "Значения переменных:\n";
	for (int j = 0; j < a.num_of_vars; j++)
			cout << a.vars[j] << " = " << a.values[j] << "\n";
};

double evaluate_polynom(multipolynom &a)
{// Вычисление значения полинома
	float current_monom = 1.0;
	float result = 0.0;
	int i, j;
	for (i = 0; i < a.num_of_terms; i++)
	{
		for (j = 0; j < a.num_of_vars; j++)
			current_monom *= pow(a.values[j], (double)a.monom[i][j]);
		current_monom *= a.factor[i];
		result += current_monom;
		current_monom = 1.0;
	};
	return result;
};

int main()
{
	multipolynom a;
	string filename = "poly1.csv";
	
	create_polynom(filename,a);
	//show_polynom(a);
	cout << "Значение многочлена при данном наборе переменных равно: " << evaluate_polynom(a) << endl;
}
	
