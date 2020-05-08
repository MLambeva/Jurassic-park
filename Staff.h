#ifndef STAFF_H
#define STAFF_H
#include<string>
#include<iostream>
#include "isCorrect.h"
#include "Dinosaurs.h"
#include"Cage.h"

class Employee
{
private:
	std::string name;
	std::string orderOfDinosaurs;//����� ����� �������� �� �������� ��� ���������

public:
	Employee() = default;
	void appointment(std::istream& in, const Cage& other);

};


#endif
