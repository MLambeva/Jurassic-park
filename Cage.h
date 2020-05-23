#ifndef CAGE_H
#define CAGE_H
#include<string>
#include<vector>
#include"Dinosaur.h"

class Cage
{
private:
	std::string size;
	std::string climate;
	int countEmp = 0;//брой работници в клетката
	std::string era;
	std::vector<Dinosaur> animals;
public:
	Cage() = default;
	Cage(const std::string& size, const std::string& climate);
	
	std::string getSize() const;
	std::string getClimate() const;
	size_t getCountEmp() const;
	std::vector<Dinosaur> getAnimals() const;
	std::string getEra() const;

	void setAnimal(const Dinosaur& other);
	void setCountEmp(const size_t& countEmp);

	void buildCageForExistedAnimal(std::istream& in, const Dinosaur& animal);
	//Създаване на клетка в зависимост от вида на животното, което ще е вътре.
	void buildCage(std::istream& in);
	//Създаване на клетка, в която няма животни и персонал, чрез посочване на размер и климат.
	void removeAnimalAndStaffFromCage(size_t index);//Премахване на животно и персонал по дадено число.
	friend std::ostream& operator << (std::ostream& out, const Cage& other);
	//Извеждане на информация за дадена клетка.

	void write(std::ofstream& out);
	//Записване на информация за клетка в бинарен файл.
	void read(std::ifstream& in);
	//Четене на информация за клетка от бинарен файл.
};


#endif
