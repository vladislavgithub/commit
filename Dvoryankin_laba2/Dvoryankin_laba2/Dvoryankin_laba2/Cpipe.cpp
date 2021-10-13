#include "Cpipe.h"
#include "Utility.h"

using namespace std;

int Cpipe::CountP = 0;
Cpipe::Cpipe()
{
	identificator = CountP++;
}
std::unordered_map<int, Cpipe> Cpipe::EditOnePipe(std::unordered_map<int, Cpipe>& pipes)
{
	cout << "������� id ������� �� ������ ��������: ";
	int k;
	cin >> k;
	cout << "0.����� � ������ \n1. ����� �� � ������\n�������� - ";
	int choice = Utility::proverka(0, 1);
	pipes[k].priznak = choice;
	cout << endl;
	return pipes;

}
void Cpipe::EditAllPipes(std::unordered_map<int, Cpipe>& pipes)
{
	cout << "0. ����� � ������\n1. ����� �� � ������\n�������� - ";
	int choice = Utility::proverka(0, 1);
	cout << endl;
	for (auto& i : pipes)
	{
		i.second.priznak = choice;
	}
}



void Cpipe::send()
{
	std::cout << "\n������� ������� ( � ��) - ";
	diametr = Utility::proverka<double>(0, 10000);
	std::cout << "������� ����� (� � ) - ";
	dlina = Utility::proverka<double>(0, 10000);
	std::cout << endl;
}
std::string Cpipe::checkRepair()
{
	return (priznak) ? "�� � ������ \n\n" : "� ������ \n\n";
}







