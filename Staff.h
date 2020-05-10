#ifndef STAFF_H
#define STAFF_H
#include<string>
#include "isCorrect.h"

class Employee
{
private:
	std::string name;//��� � �������.
	std::string orderOfDinosaurs;//����� ����� �������� �� �������� ��� ���������.

public:
	Employee() = default;
	void appointment(std::istream& in, const Cage& other);//����������� �� ��������.

	friend std::ostream& operator << (std::ostream& out, const Employee& other);//��������� �� ������������ �� ���������.

	void write(std::ofstream& out);//��������� �� ���������� �� �������� � ������� ����.
	void read(std::ifstream& in);//������ �� ���������� �� �������� �� ������� ����.
};

#endif
