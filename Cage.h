#ifndef CAGE_H
#define CAGE_H
#include<string>
#include<vector>
#include"Dinosaurs.h"

class Cage
{
private:
	std::string size;
	std::string climate;
	std::vector<Dinosaurs> animals;
	std::string era;
public:
	Cage() = default;
	Cage(std::string size, std::string climate);
	Cage(std::string size, std::string climate, std::vector<Dinosaurs> animals, std::string era);

	std::string getSize() const;
	std::string getClimate() const;
	std::vector<Dinosaurs> getAnimals() const;
	std::string getEra() const;

	void setAnimal(const Dinosaurs& other);

	void buildCage(std::istream& in);
	friend std::ostream& operator << (std::ostream& out, const Cage& other);

};


#endif
