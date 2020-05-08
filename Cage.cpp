#include"Cage.h"
#include"Dinosaurs.h"
#include"isCorrect.h"
#include<cassert>

Cage::Cage(const std::string& size, const std::string& climate, size_t countEmp)
{
	assert(isCorrectSize(size));
	this->size = size;
	assert(isCorrectClimate(climate));
	this->climate = climate;

	this->countEmp = countEmp;
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

size_t Cage::getCountEmp() const
{
	return this->countEmp;
}

void Cage::setAnimal(const Dinosaurs& other)
{
	this->animals.push_back(other);
}

void Cage::setCountEmp(const size_t& countEmp)
{
	this->countEmp = countEmp;
}

std::ostream& operator << (std::ostream& out, const Cage& other)
{
	out << other.size << " " << other.climate << " " << other.era << " Employee:" << other.countEmp << '\n';
	for (size_t i = 0; i < other.animals.size(); i++)
	{
		out << "Animal " << i+1 << ")" << other.animals[i] ;
	}
	
	return out;
}

void Cage::buildCageForExistedAnimal(std::istream& in, const Dinosaurs& animal)//Зависи от вида на животното, което ще е вътре
{
	std::string size;
	do {
		std::cout << "Size(small/medium/large):";
		in >> size;
	} while (!isCorrectSize(size));

	std::string climate;
	do {
		std::cout << "Climate(dry/air/water):";
		in >> climate;
	} while (!(isCorrectClimate(climate) && isCorrectClimateAnimal(climate, animal)));

	if (in)
	{
		this->size = size;
		this->climate = climate;
		this->countEmp = 0;
		std::cout << "You build new cage " << size << " size and " << climate
			<< " climate! with " << this->countEmp << " employee\n";
	}
}

void Cage::buildCage(std::istream& in)
{
	std::string size;
	do {
		std::cout << "Size(small/medium/large):";
		in >> size;
	} while (!isCorrectSize(size));
	
	std::string climate;
	do {
		std::cout << "Climate(dry/air/water):";
		in >> climate;
	} while (!isCorrectClimate(climate));
	
	if (in)
	{
		this->size = size;
		this->climate = climate;
		this->countEmp = 0;
		std::cout << "You build new cage " << size << " size and " << climate 
			      << " climate!" << this->countEmp << "Employee\n";
	}
}

void Cage::removeAnimalFromCage(size_t index)
{
	if (this->animals.size() == 1 || this->animals.size() == 2)
	{
		this->countEmp -= 2;
	}
	else if (this->animals.size() >= 3 && this->animals.size() <= 10)
	{
		this->countEmp--;
	}
	this->animals.erase(this->animals.begin() + (index - 1));
}