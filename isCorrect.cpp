#include"isCorrect.h"


bool isCorrectName(std::string name)
{
	bool flag = true;
	if (name.front() >= 'A' && name.front() <= 'Z')
	{
		for (size_t i = 1; i < name.size(); i++)
		{
			if (name[i] >= 'a' && name[i] <= 'z') flag = true;
			else flag = false; break;
		}
		return flag;
	}
	else return false;
}

bool isCorrectGender(std::string gender)
{
	return (gender.compare("male") == 0 || gender.compare("female") == 0);
}

bool isCorrectEra(std::string era)
{
	return (era.compare("Triassic") == 0 || era.compare("Cretaceous") == 0 || era.compare("Jura") == 0);
}

bool isCorrectOrder(std::string order)
{
	return (order.compare("herbivorous") == 0 || order.compare("carnivorous") == 0 || 
		    order.compare("flying") == 0 || order.compare("aqueous") == 0);
}

bool isCorrectSpecies(std::string species)
{
	return (species.compare("Plesiosaur") == 0 || species.compare("Brontosaurus") == 0 
		    || species.compare("Tyrannosaur") == 0 || species.compare("Pterosaur") ==0);
}

bool isCorrectFood(std::string food)
{
	return (food.compare("grass") == 0 || food.compare("meat") == 0 || food.compare("fish") == 0);
}


bool isCorrectAnimal(const Dinosaurs& other)
{
	return isCorrectName(other.getName()) && isCorrectGender(other.getGender()) && isCorrectEra(other.getEra())
		&& isCorrectOrder(other.getOrder()) && isCorrectSpecies(other.getSpecies()) && isCorrectFood(other.getFood());
}


bool isCorrectSize(std::string size)
{
	return (size.compare("small") == 0 || size.compare("medium") == 0 || size.compare("large") == 0);
}

bool isCorrectClimate(std::string climate)
{
	return (climate.compare("dry") == 0 || climate.compare("air") == 0
		|| climate.compare("water") == 0);
}

bool isCorrectCageAnimal(const Cage& other, std::vector<Dinosaurs>animals)
{
	if (other.getSize() == "small")
	{
		return (animals.size() == 0);
	}
	else if (other.getSize() == "medium")
	{
		return(animals.size() >= 0 && animals.size() < 3);
	}
	else if (other.getSize() == "large")
	{
		return(animals.size() >= 0 && animals.size() < 10);
	}
	else return false;
}

bool isCorrectClimateAnimal(const Cage& other, const Dinosaurs& animal)
{
	if (other.getClimate() == "dry")
	{
		return (animal.getSpecies() == "Brontosaurus" || animal.getSpecies() == "Tyrannosaur");
	}
	else if (other.getClimate() == "air")
	{
		return (animal.getSpecies() == "Pterosaur");
	}
	else if (other.getClimate() == "water")
	{
		return (animal.getSpecies() == "Plesiosaur");
	}
	else return false;
}