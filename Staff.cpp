#include<iostream>
#include<cassert>
#include<fstream>
#include "Staff.h"
#include "Cage.h"
#include"isCorrect.h"


void Employee::appointment(std::istream& in, const Cage& other)//����������� �� ��������
{
	std::string name;
	std::cout << "You must appoint new employee!\n";
	do {
		std::cout << "Name of employee:";
		std::getline(in, name);
	//2 �����, ��������� � ������ �������� �����, ���������� �� ����� �������� ����� � ��������� � ��������
	} while (!isCorrect::isCorrectStaffName(name));
	std::string orderOfDinosaurs;
	do {
		std::cout << "Order(herbivorous/carnivorous/flying/aqueous):";
		std::getline(in, orderOfDinosaurs);
	//����� �������� ���� �� �� ����� �� ��������� ������ ���������, ����� ������ �� ������� � ������� �� ����� ��������� 
	} while (!(isCorrect::isCorrectOrder(orderOfDinosaurs) && other.getAnimals()[0].getOrder() == orderOfDinosaurs));

	if (in)
	{
		this->name = name;
		this->orderOfDinosaurs = orderOfDinosaurs;
		
		std::cout << "You appoint new employee!\n";
	}
}

std::ostream& operator << (std::ostream& out, const Employee& other)
{
	assert(isCorrect::isCorrectStaffName(other.name) && isCorrect::isCorrectOrder(other.orderOfDinosaurs));
	out << "Name of employee:" << other.name << "; Specialist in order:" << other.orderOfDinosaurs;

	return out;
}

void Employee::write(std::ofstream& out)//��������� �� ���������� �� �������� � ������� ����.
{
	/*������ ������ ���� ����� �� ����� ��������� �� ���������, �� �������, �� ����� ���������, � �������, �.�.
	1)� ������������� ���������� ��������� ������� �� �������.
	2)��������� ��� ����� �������.
	3)��������� ������������ �� ����� ������.*/
	int nameSize = this->name.size();
	out.write((char*)(&nameSize), sizeof(nameSize));
	out.write(this->name.c_str(), sizeof(char) * nameSize);

	int orderSize = this->orderOfDinosaurs.size();
	out.write((char*)(&orderSize), sizeof(orderSize));
	out.write(this->orderOfDinosaurs.c_str(), sizeof(char) * orderSize);
}

void Employee::read(std::ifstream& in)//������ �� ���������� �� �������� �� ������� ����.
{
	/*������ ������ ���� ����� �� ����� ��������� �� ���������, �� ������� �� ����� ����� � �������, �.�.
	1)��������� ��������� �� �������.
	2)�������� ��������� �����, ���� ����� ������� �� ��� ����� � �� ���������� ������.
	3)����������� ���������� �� ��������� ���������� ���������� �� �������.
	4)������������� ���������� �����.*/
	int nameSize;
	in.read((char*)(&nameSize), sizeof(nameSize));
	char* name = new char[nameSize + 1];
	in.read(name, sizeof(char) * nameSize);
	name[nameSize] = '\0';
	this->name = name;
	delete[] name;

	int orderSize;
	in.read((char*)(&orderSize), sizeof(orderSize));
	char* order = new char[orderSize + 1];
	in.read(order, sizeof(char) * orderSize);
	order[orderSize] = '\0';
	this->orderOfDinosaurs = order;
	delete[] order;
}
