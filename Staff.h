#ifndef STAFF_H
#define STAFF_H
#include<string>
#include "isCorrect.h"

class Employee
{
private:
	std::string name;//Име и фамилия.
	std::string orderOfDinosaurs;//Всеки човек отговаря за различен вид динозавър.

public:
	Employee() = default;
	void appointment(std::istream& in, const Cage& other);//Назначаване на служител.

	friend std::ostream& operator << (std::ostream& out, const Employee& other);//Извеждане на информацията за служителя.

	void write(std::ofstream& out);//Записване на информация за служител в бинарен файл.
	void read(std::ifstream& in);//Четене на информация за служител от бинарен файл.
};

#endif
