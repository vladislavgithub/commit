#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <Windows.h>
#include <ctime>
#include <iomanip>
#include <fstream>

using namespace std;

//  ��������� �����
struct Truba
{
	int id;
	double length;
	double diameter;
	bool isrepair;
};

// ��������� ��
struct CS
{
	int id;
	string name;
	int countWorkShops;
	int countWorkShopsInOperation;
	double effectiveness;
};

// ����� ������
void ErrorOut(string str)
{
	cout << str << endl;
};

// �������� ����� ����� double
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

// �������� ����� ����� int
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


// ��������, �� ������� �� ������ ������ �� ��������
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

// ������ �� ���� �������� ��
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


// ������ �� ���� �������� ���� double � ��������� �� minValue �� maxValue
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

// ������ �� ���� ���� int �� minValue �� maxValue
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


// ������ �� ���� ��������: "������" ��� "����"
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

// ��������� �� ������� esc
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

// �������� ����� �����
Truba CreatePipe(int id)
{
	Truba result;
	result.id = id;
	result.length = GetValue("������� ����� �����,���������:���������, �������� �� 10 �� 100 �� : ",
		"������!!! ��� ���,�������!.\n����� ����� ����� � ��������� �� 10 �� 100 ��, ������� ����!!!", 10, 100);
	result.diameter = GetValue("������� ������� �����, ����������� ����������, �������� �� 500 �� 1420 �� : ",
		"������!!! ��� ���,�������!.\n������� ����� ����� � ��������� �� 500 �� 1420 ��, ������� ����!!!" �� 500 �� 1420 ��, ��������� ����!!!", 500, 1420);
	result.isrepair = GetBool("������� ��������� �� ����� � �������, ���� ��, �� ������� \"y\" �� ����������, ���� �� ���, �������� �� \"n\": ",
		"\n����������� �������! ��������� ���� �� ��������� ���� ��������, �������� �� \"y\", ���� ��, �� \"n\", ���� ���: ");
	return result;
};

// �������� ����� ������������� �������
CS CreateCompressorStation(int id)
{
	CS result;
	result.id = id;
	result.name = GetNameCS("������� �������� �� ): ",
		"������!!! �������� �� ����� �������� ������ �� �������� ��� ������ ������ � ����� ����� ������ ��� 40 �������� ");
	result.countWorkShops = GetValue("������� ���������� ����� ��: ",
		"������!!! ���������� ����� ��� ����� �����, ��� ����������� ��������, � ���� ����, ����� � ����� ����� ������ ���� ������ 20.", 0, 20, true);
	result.countWorkShopsInOperation = GetValue("������� ���������� ����� � ������: ",
		"������!!! ���������� ����� ��� ����� �����, ��� ����������� ��������, ����� ����, �����, � ����� ����� �� ������ ��������� ����� ���������� �����.", 0, result.countWorkShops, true);
	result.effectiveness = GetValue("������� �������� ������������� �� � %: ",
		"������!!! �� ����� ���-�� ����������.\n������������� �� ����� ���� ���� ����� ������, ���� ������ � ��������� ������, ������� � �������� �� 0 �� 100.\n��������� ����!!!", 0, 100);
	return result;
};


// ����� ������� ����������� ���������� ���
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
// ����� ������� ����
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


// ����� ������� ������������� �������
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


// �������������� ����
void ChangePipe(vector <Truba>& vectorPipes)
{
	size_t localId;
	bool query;
	cout << "����� ��������� ����: " << size(vectorPipes) << endl;
	if (size(vectorPipes) == 0)
	{
		ErrorOut("�� �� �������� �� ����� �����, �������������� ����������!");
		CheckPressEscape("\n\n����� ����� � ����, ������� ESC: ", "\n������� �� ����������, ������� ESC �� ����������, ���� ������ ��������� � ����!");
		return;
	}
	while (true)
	{
		localId = GetValue("\n������� ����� (id) �����, ������� �� �� ������ ������������� (id �� ������ ��������� ����� ���������� ����): ",
			"�� ����� ������������ ��������, id ����� �� ������ ��������� ����� ���������� ����, � ����� �� �������� ����������� ������!!!", 1, size(vectorPipes));

		cout << "����������� ��������� �����: "
			<< (vectorPipes[localId - 1].isrepair ? "� �������" : "�� � �������")
			<< endl;

		vectorPipes[localId - 1].isrepair = GetBool("������� ����� ��������� ��� �����, ���� ��� � �������, �� ������� \"y\" �� ����������, ���� �� ���, �������� �� \"n\": ",
			"\n����������� �������! ��������� ���� �� ��������� ���� ��������, �������� �� \"y\", ���� ��, �� \"n\", ���� ���: ");
		query = GetBool("\n\n������ �� �� ���������� ������������� �����, ���� ��, �� �������� \"y\", ���� �� ���, �� ������� �� \"n\": ",
			"\n����������� �������! ��������� ���� �� ��������� ���� ��������, �������� �� \"y\", ���� ��, �� \"n\", ���� ���: ");
		if (!query)
			break;
	}
};


// �������������� ������������� �������
void ChangeCS(vector <CS>& vectorCompressorStations)
{
	cout << "����� ��������� ������������� �������: " << size(vectorCompressorStations) << endl;
	if (size(vectorCompressorStations) == 0)
	{
		ErrorOut("�� �� �������� �� ����� ������������� �������, �������������� ����������!");
		CheckPressEscape("\n\n����� ����� � ����, ������� ESC: ", "\n������� �� ����������, ������� ESC �� ����������, ���� ������ ��������� � ����!");
		return;
	}
	while (true)
	{
		size_t localId = GetValue("\n������� ����� (id) ������������� �������, ������� �� �� ������ ������������� (id �� ������ ��������� ����� ���������� ������������� �������): ",
			"�� ����� ������������ ��������, id ����� �� ������ ��������� ����� ���������� ������������� �������, � ����� �� �������� ����������� ������!!!",
			1, size(vectorCompressorStations));
		cout << "���������� ����� � ������ ������������� �������: " << vectorCompressorStations[localId - 1].countWorkShops << endl;
		cout << "���������� ����� � ������ � ������ ������������� �������: " << vectorCompressorStations[localId - 1].countWorkShopsInOperation << endl;
		vectorCompressorStations[localId - 1].countWorkShopsInOperation = GetValue("������� ����� ���������� ����� � ������ (��� �� ������ ��������� ����� ���������� �����): ",
			"������!!! ���������� ����� ��� ����� �����, ��� ����������� ��������, ����� ����, �����, � ����� ����� �� ������ ��������� ����� ���������� �����.",
			0, vectorCompressorStations[localId - 1].countWorkShops, true);
		bool query = GetBool("\n\n������ �� �� ���������� ������������� ������������ �������, ���� ��, �� �������� \"y\", ���� �� ���, �� ������� �� \"n\": ",
			"\n����������� �������! ��������� ���� �� ��������� ���� ��������, �������� �� \"y\", ���� ��, �� \"n\", ���� ���: ");
		if (query != true)
			break;
	}
};


// ���������� ������ � ����
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
		ErrorOut("\n������!!! ���� �� ���������� ���� �� ������, ���� �� �� ����������!");
		Sleep(3000);
	}
};


// �������� ������ �� �����
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
			ErrorOut("\n������ ��������� ������ �� ������� �����, ������� ����� ��������� ��� ������!!!");
			Sleep(3000);
		}
	}
	else
	{
		ErrorOut("\n������!!! ���� �� ���������� ���� �� ������, ���� �� �� ����������!");
		Sleep(3000);
	}
};



// ����� ����� � ���������
int menu() {
	system("CLS");
	cout
		<< "1. �������� �����" << endl
		<< "2. �������� ��" << endl
		<< "3. �������� ���� ��������" << endl
		<< "4. ������������� �����" << endl
		<< "5. ������������� ��" << endl
		<< "6. ���������" << endl
		<< "7. ���������" << endl
		<< "0. �����" << endl
		<< "�������� ����� ���� (0-7): ";
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
	int nm; // ����� ����


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
			CheckPressEscape("\n\n\n����� ����� � ����, ������� ESC: ", "\n������� �� ����������, ������� ESC �� ����������, ���� ������ ��������� � ����!");
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
			ErrorOut("\n������������ ���� ������! ������� �� �����, ������� ������������ ������� �� ������");
			Sleep(3000);
			break;
		}


	} while (nm != 0);
	return 0;
};

