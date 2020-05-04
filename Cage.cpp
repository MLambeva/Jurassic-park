#include"Cage.h"
#include"Dinosaurs.h"
#include"isCorrect.h"
#include<cassert>

Cage::Cage(std::string size, std::string climate)
{
	assert(isCorrectSize(size));
	this->size = size;
	assert(isCorrectClimate(climate));
	this->climate = climate;
}

//Cage::Cage(std::string size, std::string climate, std::vector<Dinosaurs> animals, std::string era)
//{
//	assert(isCorrectSize(size));
//	this->size = size;
//	assert(isCorrectClimate(climate));
//	this->climate = climate;
//	assert(isCorrectEra(era));
//	this->era = era;
//	//assert(isCorrectCageAnimal(size, animals));
//	for (size_t i = 0; i < animals.size(); i++)
//	{
//		assert(isCorrectAnimal(animals[i]));
//	}
//	this->animals = animals;
//	
//	std::string orderInCage = animals[0].getOrder();
//	for (size_t i = 0; i < animals.size(); i++)
//	{
//		assert(animals[i].getEra() == era && animals[i].getOrder() == orderInCage);
//	}
//}

std::string Cage::getSize() const
{
	return this->size;
}

std::string Cage::getClimate() const
{
	return this->climate;
}

std::vector<Dinosaurs> Cage::getAnimals() const
{
	return this->animals;
}

std::string Cage::getEra() const
{
	return this->era;
}

void Cage::setAnimal(const Dinosaurs& other)
{
	this->animals.push_back(other);
}

std::ostream& operator << (std::ostream& out, const Cage& other)
{
	out << other.size << " " << other.climate << " " << other.era << '\n';
	for (size_t i = 0; i < other.animals.size(); i++)
	{
		out << "Animal " << i+1 << ")" << other.animals[i] ;
	}

	return out;
}

void Cage::buildCage(std::istream& in)
{
	std::string size;
	do {
		std::cout << "Size:";
		in >> size;
	} while (!isCorrectSize(size));
	
	std::string climate;
	do {
		std::cout << "Climate:";
		in >> climate;
	} while (!isCorrectClimate(climate));
	
	if (in)
	{
		this->size = size;
		this->climate = climate;
		
		std::cout << "You build new cage " << size << " size and " << climate << " climate!\n";
	}
}