#include<iostream>
#include<cassert>
#include<fstream>
#include "Staff.h"
#include "Cage.h"
#include"isCorrect.h"


void Employee::appointment(std::istream& in, const Cage& other)//Назначаване на служител
{
	std::string name;
	std::cout << "You must appoint new employee!\n";
	do {
		std::cout << "Name of employee:";
		std::getline(in, name);
	//2 имена, започващи с главни латински букви, последвани от малки латински букви и разделени с интервал
	} while (!isCorrect::isCorrectStaffName(name));
	std::string orderOfDinosaurs;
	do {
		std::cout << "Order(herbivorous/carnivorous/flying/aqueous):";
		std::getline(in, orderOfDinosaurs);
	//Всеки служител може да се грижи за определен разред динозаври, който трябва да съвпада с разреда на самия динозавър 
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

void Employee::write(std::ofstream& out)//Записване на информация за служител в бинарен файл.
{
	/*Понеже всички член данни от класа Служители са стрингове, то начинът, по който записваме, е еднакъв, т.е.
	1)В новосъздадена променлива запазваме размера на стринга.
	2)Записваме във файла размера.
	3)Записваме информацията от самия стринг.*/
	int nameSize = this->name.size();
	out.write((char*)(&nameSize), sizeof(nameSize));
	out.write(this->name.c_str(), sizeof(char) * nameSize);

	int orderSize = this->orderOfDinosaurs.size();
	out.write((char*)(&orderSize), sizeof(orderSize));
	out.write(this->orderOfDinosaurs.c_str(), sizeof(char) * orderSize);
}

void Employee::read(std::ifstream& in)//Четене на информация за служител от бинарен файл.
{
	/*Понеже всички член данни от класа Служители са стрингове, то начинът по който четем е еднакъв, т.е.
	1)Прочитаме дължината на стринга.
	2)Заделяме динамично памет, като имаме предвид да има място и за затапващия символ.
	3)Присвояваме стойността на динамично заделената променлива на стринга.
	4)Освобождаваме заделената памет.*/
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
