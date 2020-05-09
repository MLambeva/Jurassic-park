#include"Cage.h"
#include"Dinosaurs.h"
#include"isCorrect.h"
#include<cassert>

Cage::Cage(const std::string& size, const std::string& climate, int countEmp)
{
	assert(isCorrect::isCorrectSize(size));//static
	this->size = size;
	assert(isCorrect::isCorrectClimate(climate));
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
	out << "Size: " << other.size << "; Climate: " << other.climate << "; Employee:" << other.countEmp << " " << other.era << '\n';
	for (size_t i = 0; i < other.animals.size(); i++)
	{
		out << "Animal " << i+1 << ")" << other.animals[i] ;
	}
	std::cout << '\n';
	
	return out;
}

void Cage::buildCageForExistedAnimal(std::istream& in, const Dinosaurs& animal)//Зависи от вида на животното, което ще е вътре
{
	std::string size;
	do {
		std::cout << "Size(small/medium/large):";
		std::getline(in, size);
	} while (!isCorrect::isCorrectSize(size));

	std::string climate;
	do {
		std::cout << "Climate(dry/air/water):";
		std::getline(in, climate);
	} while (!(isCorrect::isCorrectClimate(climate) && isCorrect::isCorrectClimateAnimal(climate, animal)));

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
		std::getline(in, size);
	} while (!isCorrect::isCorrectSize(size));
	
	std::string climate;
	do {
		std::cout << "Climate(dry/air/water):";
		std::getline(in, climate);
	} while (!isCorrect::isCorrectClimate(climate));
	
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

void Cage::write(std::ofstream& out)
{
	int sizeSize = this->size.size();
	out.write((char*)(&sizeSize), sizeof(sizeSize));
	out.write(this->size.c_str(), sizeof(char) * sizeSize);
	int climateSize = this->climate.size();
	out.write((char*)(&climateSize), sizeof(climateSize));
	out.write(this->climate.c_str(), sizeof(char) * climateSize);
	out.write((char*)(&this->countEmp), sizeof(this->countEmp));
	int eraSize = this->era.size();
	out.write((char*)(&eraSize), sizeof(eraSize));
	out.write(era.c_str(), sizeof(char) * eraSize);
	int animalsSize = this->animals.size();
	out.write((char*)(&animalsSize), sizeof(animalsSize));
	for (int i = 0; i < animalsSize; i++)
	{
		animals[i].write(out);
	}
}

void Cage::read(std::ifstream& in)
{
	int sizeSize;
	in.read((char*)(&sizeSize), sizeof(sizeSize));
	char* size = new char[sizeSize + 1];
	in.read(size, sizeof(char) * sizeSize);
	size[sizeSize] = '\0';
	this->size = size;
	delete[] size;
	int climateSize;
	in.read((char*)(&climateSize), sizeof(climateSize));
	char* climate = new char[climateSize + 1];
	in.read(climate, sizeof(char) * climateSize);
	climate[climateSize] = '\0';
	this->climate = climate;
	delete[] climate;
	in.read((char*)(&this->countEmp), sizeof(this->countEmp));
	int eraSize;
	in.read((char*)(&eraSize), sizeof(eraSize));
	char* era = new char[eraSize + 1];
	era[eraSize] = '\0';
	this->era = era;
	delete[] era;
	int animalsSize;
	in.read((char*)(&animalsSize), sizeof(animalsSize));
	
	for (int i = 0; i < animalsSize; i++)
	{
		Dinosaurs reader;
		reader.read(in);
		animals.push_back(reader);
	}
}