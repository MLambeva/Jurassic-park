#include"Dinosaurs.h"
#include"isCorrect.h"
#include<cassert>

Dinosaurs::Dinosaurs(std::string name, std::string gender, std::string era, 
                     std::string order, std::string species, std::string food)
{
	assert(isCorrectName(name) && isCorrectGender(gender) && isCorrectEra(era) && isCorrectOrder(order)
		&& isCorrectSpecies(species) && isCorrectFood(food));

	this->name = name;
	this->gender = gender;
	this->era = era;
	this->order = order;
	this->species = species;
	this->food = food;
} 

Dinosaurs& Dinosaurs::operator=(const Dinosaurs& other)
{
	this->name = other.name;
	this->gender = other.gender;
	this->era = other.era;
	this->order = other.order;
	this->species = other.species;
	this->food = other.food;

	return *this;
}

std::string Dinosaurs::getName()const
{
	return this->name;
}

std::string Dinosaurs::getGender()const
{
	return this->gender;
}

std::string Dinosaurs::getEra()const
{
	return this->era;
}

std::string Dinosaurs::getOrder()const
{
	return this->order;
}

std::string Dinosaurs::getSpecies()const
{
	return this->species;
}

std::string Dinosaurs::getFood()const
{
	return this->food;
}

std::ostream& operator<<(std::ostream& out, const Dinosaurs& other)
{
	assert(isCorrectAnimal(other));
	out << other.name << " " << other.gender << " " << other.era
		<< " " << other.order << " " << other.species << " " << other.food << '\n';
	return out;
}

std::istream& operator >> (std::istream& in, Dinosaurs& other)
{
	in >> other.name >> other.gender >> other.era >>  other.order >> other.species >> other.food;
	assert(isCorrectAnimal(other));
	
	return in;
}

void Dinosaurs::createAnimal(std::istream& in)
{
	std::string name;
	do {
		std::cout << "Name:";
		in >> name;
	} while (!isCorrectName(name));

	std::string gender;
	do {
		std::cout << "Gender:";
		in >> gender;
	} while (!isCorrectGender(gender));

	std::string era;
	do {
		std::cout << "Era:";
		in >> era;
	} while (!isCorrectEra(era));

	std::string order;
	do {
		std::cout << "Order:";
		in >> order;
	} while (!isCorrectOrder(order));

	//std::string species;
	//do {
	//	std::cout << "Species:";
	//	in >> species;
	//} while (!isCorrectSpecies(species));
	//
	//std::string food;
	//std::string correctFood;
	//if (order == "herbivorous") correctFood = "grass";
	//else if (order == "carnivorous") correctFood = "meat";
	//else if (order == "flying") correctFood = "meat";
	//else if (order == "aqueous") correctFood = "fish";
	//do {
	//	std::cout << "Food:";
	//	in >> food;
	//} while (!(isCorrectFood(food) && (correctFood == food)));

	if (in)
	{
		this->name = name;
		this->gender = gender;
		this->era = era;
		this->order = order;
		if (this->order == "herbivorous")
		{
			this->species = "Brontosaurus";
			std::cout << "species:Brontosaurus\n";
			this->food = "grass";
			std::cout << "food:grass\n";
		}
		else if (this->order == "carnivorous")
		{
			this->species = "Tyrannosaur";
			std::cout << "species:Tyrannosaur\n";
			this->food = "meat";
			std::cout << "food:meat\n";
		}
		else if (this->order == "flying")
		{
			this->species = "Pterosaur";
			std::cout << "species:Pterosaur\n";
			this->food = "meat";
			std::cout << "food:meat\n";
		}
		else if (this->order == "aqueous")
		{
			this->species = "Plesiosaur";
			std::cout << "species:Plesiosaur\n";
			this->food = "fish";
			std::cout << "food:fish\n";
		}
		//this->species = species;
		//this->food = food;
	}
}


void Dinosaurs::print()const
{
	assert(isCorrectAnimal(*this));
	//assert(isCorrectName(this->name) && isCorrectGender(this->gender) && isCorrectEra(this->era)
	//	&& isCorrectOrder(this->order) && isCorrectSpecies(this->species) && isCorrectFood(this->food));
	std::cout << this->name << " " << this->gender << " " << this->era
		<< " " << this->order << " " << this->species << " " << this->food;
}


