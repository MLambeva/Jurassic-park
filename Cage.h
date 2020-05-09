#ifndef CAGE_H
#define CAGE_H
#include<string>
#include<vector>
#include<fstream>
#include"Dinosaurs.h"

class Cage
{
private:
	std::string size;
	std::string climate;
	int countEmp;//брой работници в клетката
	std::string era;
	std::vector<Dinosaurs> animals;
public:
	Cage() = default;
	Cage(const std::string& size, const std::string& climate, int countEmp);
	//Cage(std::string size, std::string climate, std::vector<Dinosaurs> animals, std::string era);

	std::string getSize() const;
	std::string getClimate() const;
	std::vector<Dinosaurs> getAnimals() const;
	std::string getEra() const;
	size_t getCountEmp() const;

	void setAnimal(const Dinosaurs& other);
	void setCountEmp(const size_t& countEmp);

	void buildCageForExistedAnimal(std::istream& in, const Dinosaurs& animal);
	void buildCage(std::istream& in);
	void removeAnimalFromCage(size_t index);
	friend std::ostream& operator << (std::ostream& out, const Cage& other);

	void write(std::ofstream& out);
	void read(std::ifstream& in);
};


#endif
