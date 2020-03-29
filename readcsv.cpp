/* Чтение данных из файла формата .CSV */
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream> 
#include <cmath>
#include <vector>

using namespace std;

const int LENGHT_OF_POLYNOM = 50; // Максимальное количество одночленов в полиноме

class multipolynom
{
	vector<string> vars;
	vector<double> factor; // Коэффициенты при мономах
	vector<double> values; // Значения переменных
	int **monom;    // Степени переменных в мономе
	int num_of_vars; // Количество переменных
	int num_of_terms; // Количество одночленов

	void read_var_names(string filename)
	{// Чтение имен переменных из первой строки файла
		string s;// Временная строка
		string var_name = "";
		
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
				var_name += s[first_sym];
				first_sym++; // счетчик по входной строке
				i++; // счетчик символов в имени переменной
			};
			i_name++; // Переходим к новой переменной
			first_sym++; // Пропускаем символ ";"
			this->vars.push_back(var_name); // Добавляем в список переменных новое имя
			var_name = "";
		};
		this->num_of_vars = i_name;
	};
	
	void read_values(string filename)
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
						this->values.push_back(0);
					else
						this->values.push_back(stod(tmp_value));
				tmp_value = "";
				i_monom++;
		};
	};
	
	void read_powers(string filename)
	{// Чтение коэффициентов при одночленах и степеней переменных из третьей и последующих строк
		
		string s;
		string tmp_factor;
		string tmp_power;
		int i = 0;
		int j = 0;
		int i_monom = 0;
		int i_factor = 0;
		int* p = NULL;
		
		ifstream fin(filename); // Открыли файл для чтения
		fin >> s; // Пропускаем строку с именами переменных
		fin >> s; // Пропускаем строку со значениями переменных
		
		this->monom = new int*;
		
		// Цикл по файлу
		while (!fin.eof())
		{
			i = 0; // Сбрасываем счетчик символов по строке s
			fin >> s; // Прочитали следующую строку, где коэффициент монома и степени переменных
			if(fin.eof()) 
				break; // Избегаем двойного чтения последней строки файла
			
			//cout << "xbvzb " << i_monom << endl;
			
			// Цикл по строке
			while (s[i] != ';' && s[i] != 0)
			{// Читаем первый элемент строки, содержащий вещественное число - коэффициент при мономе
				tmp_factor += s[i];
				i++;
			};
			i++;
			
			// Преобразуем строку в вещественное значение и сохраняем ее в массиве коэфифциентов
			// Если строка со значением коэффициента пустая, то коэффициент равен 0
			cout << "Create new factor = " << tmp_factor << "\t i_monom = " << i_monom << endl;
			if(tmp_factor.size() == 0)
					this->factor.push_back(0);
				else
					this->factor.push_back(stod(tmp_factor));
			
			tmp_factor = "";
			
			//cout << "Before allocation >>>\n";
			if (i_monom < this->num_of_vars)
				this->monom[i_monom] = new int[this->num_of_vars]; // Создаем новый моном с длиной равной количеству переменных
			//cout << "After >>>" << i_monom << endl;
			for( int k = 0; k < this->num_of_vars; k++) // Теперь идем до конца строки и читаем целые числа - степени переменных
			{
				while (s[i] != ';' && s[i] != 0)
				{
					tmp_power += s[i];
					//cout << "tmp =" << tmp_power << endl;
					i++;
				};
				i++;
				
				if(tmp_power.size() == 0)
				{
					//cout << "Assign 0\n";
					this->monom[i_monom][k] = 0;
					//cout << "after assigning 0\n";
				}
				else
				{
					//cout << "Assign " << tmp_power << endl;
					this->monom[i_monom][k] = stoi(tmp_power);
					//cout << "after assigning " << tmp_power << endl;
				};
				//cout << "Before reset tmp_power\n";
				tmp_power = "";
				//cout << "After reset tmp_power\n";
			};
			cout << "i_monom before inrement = " << i_monom << endl;
			i_monom++;
			cout << "i_monom after inrement = " << i_monom << endl;
		};
		fin.close(); // Закрыли файл
		this->num_of_terms = i_monom;
	};
	
	public:
	multipolynom(string filename)
	{// Создание полинома из файла
		read_var_names(filename);
		read_powers(filename);
		read_values(filename);
	};
	
	void show_polynom()
	{ // Вывод полинома на экран
		cout << "\t";
		for (int i = 0; i < this->num_of_vars; i++)
			cout << this->vars[i] << "\t";
		cout << endl;
		
		for (int i = 0; i < this->num_of_terms; i++)
		{
			cout << this->factor[i] << "\t";
			for (int j = 0; j < this->num_of_vars; j++)
				cout << this->monom[i][j] << "\t";
			cout << endl;
		};
		
		cout << endl;
		cout << "Значения переменных:\n";
		for (int j = 0; j < this->num_of_vars; j++)
				cout << this->vars[j] << " = " << this->values[j] << "\n";
	};
	
	double evaluate_polynom()
	{// Вычисление значения полинома
	float current_monom = 1.0;
	float result = 0.0;
	int i, j;
	for (i = 0; i < this->num_of_terms; i++)
	{
		for (j = 0; j < this->num_of_vars; j++)
			current_monom *= pow(this->values[j], (double)this->monom[i][j]);
		current_monom *= this->factor[i];
		result += current_monom;
		current_monom = 1.0;
	};
	return result;
	};
};

int main()
{
	string filename = "poly1.csv";
	multipolynom a(filename);
	
	a.show_polynom();
	cout << "Значение многочлена при данном наборе переменных равно: " << a.evaluate_polynom() << endl;
}
	
