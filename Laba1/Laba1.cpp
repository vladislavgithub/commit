#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <Windows.h>
#include <ctime>
#include <iomanip>
#include <fstream>

using namespace std;

//  Структура Трубы
struct Truba
{
	int id;
	double length;
	double diameter;
	bool isrepair;
};

// Структура КС
struct CS
{
	int id;
	string name;
	int countWorkShops;
	int countWorkShopsInOperation;
	double effectiveness;
};

// Вывод ошибки
void ErrorOut(string str)
{
	cout << str << endl;
};

// Проверка ввода числа double
bool CheckInputDigit(string number)
{
	int counter = 0;
	if (size(number) == 0 || !isdigit(number[0]))
		return false;
	for (size_t i = 0; i < size(number); i++)
	{
		if (!isdigit(number[i]))
			if (number[i] != ',')
				return false;
			else
				counter++;
	}
	return counter <= 1;
};

// Проверка ввода числа int
bool CheckInputDigit(string number, bool thisInt)
{
	if (size(number) == 0 || !isdigit(number[0]))
		return false;
	for (size_t i = 0; i < size(number); i++)
	{
		if (!isdigit(number[i]))
			return false;
	}
	return true;
};


// Проверка, не состоит ли строка только из пробелов
bool CheckCountSpace(string str)
{
	int i = 0;
	while (i != size(str))
	{
		if (str[i] != ' ')
			return true;
		++i;
	}
	return false;
};

// Запрос на ввод названия КС
string GetNameCS(string textRequest, string textError)
{
	string nameCS;
	while (true)
	{
		cout << textRequest;
		cin.seekg(cin.eof());
		getline(cin, nameCS);
		if (nameCS != "" && CheckCountSpace(nameCS) && size(nameCS) <= 30)
			return nameCS;
		else
		{
			ErrorOut(textError);
		}
	}
};


// Запрос на ввод значений типа double в диапозоне от minValue до maxValue
double GetValue(string textRequest, string textError, double minValue, double maxValue)
{
	string value;
	while (true)
	{

		cout << textRequest;
		cin.seekg(cin.eof());
		getline(cin, value);
		if (CheckInputDigit(value))
		{
			try
			{
				double resultValue = stod(value);
				if (resultValue >= minValue && resultValue <= maxValue)
					return resultValue;
				else
					ErrorOut(textError);
			}
			catch (const exception& e)
			{
				cout << e.what() << endl;
				ErrorOut(textError);
			}
		}
		else
		{
			ErrorOut(textError);
		}
	}
};

// Запрос на ввод типа int от minValue до maxValue
int GetValue(string textRequest, string textError, int minValue, int maxValue, bool thisInt)
{
	string value;
	while (true)
	{
		cout << textRequest;
		cin.seekg(cin.eof());
		getline(cin, value);
		if (CheckInputDigit(value, true))
		{
			try
			{
				int resultValue = stoi(value);
				if (resultValue >= minValue && resultValue <= maxValue)
					return resultValue;
				else
					ErrorOut(textError);
			}
			catch (exception)
			{
				ErrorOut(textError);
			}
		}
		else
		{
			ErrorOut(textError);
		}
	}
};


// Запрос на ввод значений: "ИСТИНА" или "ЛОЖЬ"
bool GetBool(string textRequest, string textError)
{
	char stateRepair;
	cout << textRequest;
	while (true)
	{
		stateRepair = _getch();
		if (stateRepair == 'y')
		{
			return true;
		}
		else if (stateRepair == 'n')
		{
			return false;
		}
		else
		{
			ErrorOut(textError);
		}
	}
};

// Прроверка на нажатие esc
void CheckPressEscape(string textRequest, string textError)
{
	while (true)
	{
		cout << textRequest;
		char escCommand;
		escCommand = _getch();
		if (escCommand == '\x1b')
			break;
		else
			ErrorOut(textError);
	}
};

// Создание новой трубы
Truba CreatePipe(int id)
{
	Truba result;
	result.id = id;
	result.length = GetValue("Введите длину трубы,измерения:километры, диапазон от 10 до 100 км : ",
		"Ошибка!!! Как так,дорогой!.\nДлина трубы лежит в диапазоне от 10 до 100 км, повтори ввод!!!", 10, 100);
	result.diameter = GetValue("Введите диаметр трубы, размерность миллиметры, диапазон от 500 до 1420 мм : ",
		"Ошибка!!! Как так,дорогой!.\nДиаметр трубы лежит в диапазоне от 500 до 1420 км, повтори ввод!!!" от 500 до 1420 мм, повторите ввод!!!", 500, 1420);
	result.isrepair = GetBool("Укажите находится ли труба в ремонте, если да, то нажмите \"y\" на клавиатуре, если же нет, кликните по \"n\": ",
		"\nНеизвестная команда! Повторите ввод по указанным выше правилам, кликните по \"y\", если да, по \"n\", если нет: ");
	return result;
};

// Создание новой компрессорной станции
CS CreateCompressorStation(int id)
{
	CS result;
	result.id = id;
	result.name = GetNameCS("Введите название КС ): ",
		"Ошибка!!! Название не может состоять только из пробелов или пустой строки и иметь длину больше чем 40 символов ");
	result.countWorkShops = GetValue("Введите количество цехов КС: ",
		"Ошибка!!! Количество цехов это целое число, без посторонних символов, в виде букв, точек и также число должно быть меньше 20.", 0, 20, true);
	result.countWorkShopsInOperation = GetValue("Введите количество цехов в работе: ",
		"Ошибка!!! Количество цехов это целое число, без посторонних символов, ввиде букв, точек, а также число не должно превышать общее количество цехов.", 0, result.countWorkShops, true);
	result.effectiveness = GetValue("Введите значение эффективности КС в %: ",
		"Ошибка!!! Вы ввели что-то непонятное.\nЭффективность КС может быть либо целым числом, либо числом с плавающей точкой, лежащим в пределах от 0 до 100.\nПовторите ввод!!!", 0, 100);
	return result;
};


// Вывод символа определённое количество раз
void PrintChar(char ch, size_t count)
{
	/*for (size_t i = 0; i < count; i++)
	{
		cout << ch;
	}
	cout << endl;*/

	cout << string(count, ch) << endl;
};

//##
// Вывод таблицы труб
void PrintTablePipes(const vector <Truba>& vectorPipes)
{
	PrintChar('-', 131);
	cout << "|" << setw(20) << "ID" << setw(30) << "LENGTH" << setw(30) << "DIAMETER" << setw(30) << "REPAIR" << setw(20) << "|" << endl;
	PrintChar('-', 131);
	for (const auto& p : vectorPipes)
	{
		cout << "|" << setw(20) << p.id << setw(30) << p.length << setw(30) << p.diameter << setw(30) << (p.isrepair == true ? "true" : "false") << setw(20) << "|" << endl;
	}
	PrintChar('-', 131);
};


// Вывод таблицы Компрессорных станций
void PrintTableCS(const vector <CS>& vectorCompressorStations)
{
	PrintChar('-', 172);
	cout << "|" << setw(20) << "ID" << setw(31) << "NAME" << setw(30) << "CountWorkShops" << setw(40) << "CountWorkShopsInOperation" << setw(30) << "EFFECTIVENESS" << setw(20) << "|" << endl;
	PrintChar('-', 172);
	for (const auto& cs : vectorCompressorStations)
	{
		cout << "|" << setw(20) << cs.id << setw(31) << cs.name << setw(30) << cs.countWorkShops << setw(40) << cs.countWorkShopsInOperation << setw(30) << cs.effectiveness << setw(20) << "|" << endl;
	}
	PrintChar('-', 172);
};


// Редактирование Труб
void ChangePipe(vector <Truba>& vectorPipes)
{
	size_t localId;
	bool query;
	cout << "Всего добавлено труб: " << size(vectorPipes) << endl;
	if (size(vectorPipes) == 0)
	{
		ErrorOut("Вы не добавили ни одной трубы, редактирование недоступно!");
		CheckPressEscape("\n\nЧтобы выйти в меню, нажмите ESC: ", "\nКоманда не распознана, нажмите ESC на клавиатуре, если хотите вернуться в меню!");
		return;
	}
	while (true)
	{
		localId = GetValue("\nВведите номер (id) трубы, которую вы бы хотели редактировать (id не должен превышать общее количество труб): ",
			"Вы ввели недопустимое значение, id трубы не должен превышать общее количество труб, а также он является натуральным числом!!!", 1, size(vectorPipes));

		cout << "Изначальное состояние трубы: "
			<< (vectorPipes[localId - 1].isrepair ? "в ремонте" : "не в ремонте")
			<< endl;

		vectorPipes[localId - 1].isrepair = GetBool("Укажите новое состояние для трубы, если она в ремонте, то нажмите \"y\" на клавиатуре, если же нет, кликните по \"n\": ",
			"\nНеизвестная команда! Повторите ввод по указанным выше правилам, кликните по \"y\", если да, по \"n\", если нет: ");
		query = GetBool("\n\nХотите ли вы продолжить редактировать трубы, если да, то кликните \"y\", если же нет, то нажмите на \"n\": ",
			"\nНеизвестная команда! Повторите ввод по указанным выше правилам, кликните по \"y\", если да, по \"n\", если нет: ");
		if (!query)
			break;
	}
};


// Редактирование Компрессорных станций
void ChangeCS(vector <CS>& vectorCompressorStations)
{
	cout << "Всего добавлено компрессорных станций: " << size(vectorCompressorStations) << endl;
	if (size(vectorCompressorStations) == 0)
	{
		ErrorOut("Вы не добавили ни одной компрессорной станции, редактирование недоступно!");
		CheckPressEscape("\n\nЧтобы выйти в меню, нажмите ESC: ", "\nКоманда не распознана, нажмите ESC на клавиатуре, если хотите вернуться в меню!");
		return;
	}
	while (true)
	{
		size_t localId = GetValue("\nВведите номер (id) компрессорной станции, которую вы бы хотели редактировать (id не должен превышать общее количество компрессорных станций): ",
			"Вы ввели недопустимое значение, id трубы не должен превышать общее количество компрессорных станций, а также он является натуральным числом!!!",
			1, size(vectorCompressorStations));
		cout << "Количество цехов у данной компрессорной станции: " << vectorCompressorStations[localId - 1].countWorkShops << endl;
		cout << "Количество цехов в работе у данной компрессорной станции: " << vectorCompressorStations[localId - 1].countWorkShopsInOperation << endl;
		vectorCompressorStations[localId - 1].countWorkShopsInOperation = GetValue("Введите новое количество цехов в работе (оно не должно превышать общее количество цехов): ",
			"Ошибка!!! Количество цехов это целое число, без посторонних символов, ввиде букв, точек, а также число не должно превышать общее количество цехов.",
			0, vectorCompressorStations[localId - 1].countWorkShops, true);
		bool query = GetBool("\n\nХотите ли вы продолжить редактировать компрессоные станции, если да, то кликните \"y\", если же нет, то нажмите на \"n\": ",
			"\nНеизвестная команда! Повторите ввод по указанным выше правилам, кликните по \"y\", если да, по \"n\", если нет: ");
		if (query != true)
			break;
	}
};


// Сохранение данных в файл
void SaveData(vector <Truba>& vectorPipes, vector <CS>& vectorCompressorStations)
{
	ofstream fout;
	fout.open("save.txt");
	size_t percent = 0;
	if (fout.is_open())
	{
		for (size_t i = 0; i < size(vectorPipes); i++)
		{
			fout << vectorPipes[i].length << endl
				<< vectorPipes[i].diameter << endl
				<< vectorPipes[i].isrepair << endl;
		}
		fout << ' ' << endl;
		for (size_t i = 0; i < size(vectorCompressorStations); i++)
		{
			fout << vectorCompressorStations[i].name << endl
				<< vectorCompressorStations[i].countWorkShops << endl
				<< vectorCompressorStations[i].countWorkShopsInOperation << endl
				<< vectorCompressorStations[i].effectiveness << endl;
		}
		fout.close();

	}
	else
	{
		ErrorOut("\nОШИБКА!!! Файл по указанному пути не найден, либо он не существует!");
		Sleep(3000);
	}
};


// Загрузка данных из файла
void UploadData(vector <Truba>& vectorPipes, vector <CS>& vectorCompressorStations)
{
	ifstream fin;
	fin.open("save.txt");
	size_t percent = 0;
	if (fin.is_open())
	{
		if (fin.peek() != -1)
		{
			while (fin.peek() != ' ')
			{
				Truba newPipe;
				newPipe.id = size(vectorPipes);
				fin >> newPipe.length;
				fin >> newPipe.diameter;
				fin >> newPipe.isrepair;
				vectorPipes.push_back(newPipe);
				fin.ignore(1000, '\n');
			}
			fin.ignore(1000, '\n');
			while (fin.peek() != -1)
			{
				CS newCompressorStation;
				newCompressorStation.id = size(vectorCompressorStations);
				getline(fin, newCompressorStation.name);
				fin >> newCompressorStation.countWorkShops;
				fin >> newCompressorStation.countWorkShopsInOperation;
				fin >> newCompressorStation.effectiveness;
				vectorCompressorStations.push_back(newCompressorStation);
				fin.ignore(1000, '\n');
			}
			fin.close();

		}
		else
		{
			ErrorOut("\nНельзя загружать данные из пустого файла, сначала нужно сохранить там данные!!!");
			Sleep(3000);
		}
	}
	else
	{
		ErrorOut("\nОШИБКА!!! Файл по указанному пути не найден, либо он не существует!");
		Sleep(3000);
	}
};



// Точка входа в программу
int menu() {
	system("CLS");
	cout
		<< "1. Добавить трубу" << endl
		<< "2. Добавить КС" << endl
		<< "3. Просмотр всех объектов" << endl
		<< "4. Редактировать трубу" << endl
		<< "5. Редактировать КС" << endl
		<< "6. Сохранить" << endl
		<< "7. Загрузить" << endl
		<< "0. Выход" << endl
		<< "Выберите пункт меню (0-7): ";
	int a;
	cin >> a;
	system("CLS");
	return a;


}

int main()
{
	setlocale(LC_ALL, "RUS");
	vector <Truba> vectorPipes;
	vector <CS> vectorCompressorStations;
	int nm; // Номер меню


	do
	{
		nm = menu();

		switch (nm)

		{
		case 1:
		{

			Truba NewPipe = CreatePipe(size(vectorPipes) + 1);
			vectorPipes.push_back(NewPipe);
			break;
		}
		case 2:
		{
			CS NewComressorStation = CreateCompressorStation(size(vectorCompressorStations) + 1);
			vectorCompressorStations.push_back(NewComressorStation);
			break;
		}
		case 3:
		{

			PrintTablePipes(vectorPipes);
			PrintTableCS(vectorCompressorStations);
			CheckPressEscape("\n\n\nЧтобы выйти в меню, нажмите ESC: ", "\nКоманда не распознана, нажмите ESC на клавиатуре, если хотите вернуться в меню!");
			break;
		}
		case 4:
		{

			ChangePipe(vectorPipes);
			break;
		}
		case 5:
		{

			ChangeCS(vectorCompressorStations);
			break;
		}
		case 6:
		{

			SaveData(vectorPipes, vectorCompressorStations);
			break;
		}
		case 7:
		{

			UploadData(vectorPipes, vectorCompressorStations);
			break;
		}
		case 0:
		{

			break;
		}
		default:
			ErrorOut("\nНекорректный ввод данных! Нажмите на число, которое соотвествует команде из списка");
			Sleep(3000);
			break;
		}


	} while (nm != 0);
	return 0;
};

