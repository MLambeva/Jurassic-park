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
	std::string orderOfDinosaurs;//Всеки човек отговаря за различен вид динозавър

public:
	Employee() = default;
	void appointment(std::istream& in, const Cage& other);

};


#endif
