#include"isCorrect.h"

bool isCorrect::isLetter(char x)//Проверява дали символът е малка латинска буква.
{
	return x >= 'a' && x <= 'z';
}

bool isCorrect::isCorrectName(std::string name)//Проверява дали коректно е въведено името на динозавъра.
{
	//1 име, започващо с главна латинска буква, последвана от малки латински букви.
	bool flag = true;
	if (name[0] >= 'A' && name[0] <= 'Z')
	{
		for (size_t i = 1; i < name.size(); i++)
		{
			if (isLetter(name[i])) flag = true;
			else { flag = false; break; }
		}
		return flag;
	}
	else return false;
}

bool isCorrect::isCorrectGender(std::string gender)//Проверява дали коректно е въведен пола.
{
	return (gender.compare("male") == 0 || gender.compare("female") == 0);
}

bool isCorrect::isCorrectEra(std::string era)//Проверява дали коректно е въведена ерата.
{
	return (era.compare("Triassic") == 0 || era.compare("Cretaceous") == 0 || era.compare("Jura") == 0);
}

bool isCorrect::isCorrectOrder(std::string order)//Проверява дали коректно е въведен разредът на динозавъра.
{
	return (order.compare("herbivorous") == 0 || order.compare("carnivorous") == 0 || 
		    order.compare("flying") == 0 || order.compare("aqueous") == 0);
}

bool isCorrect::isCorrectSpecies(std::string species)//Проверява дали коректно е въведен видът на динозавъра.
{
	return (species.compare("Plesiosaur") == 0 || species.compare("Brontosaurus") == 0 
		    || species.compare("Tyrannosaur") == 0 || species.compare("Pterosaur") ==0);
}

bool isCorrect::isCorrectFood(std::string food)//Проверява дали коректно е въведена храната на динозавъра.
{
	return (food.compare("grass") == 0 || food.compare("meat") == 0 || food.compare("fish") == 0);
}

bool isCorrect::isCorrectAnimal(const Dinosaurs& other)//Проверява дали коректно е въведен диназавъра.
{
	return isCorrectName(other.getName()) && isCorrectGender(other.getGender()) && isCorrectEra(other.getEra())
		&& isCorrectOrder(other.getOrder()) && isCorrectSpecies(other.getSpecies()) && isCorrectFood(other.getFood());
}

bool isCorrect::isCorrectSize(std::string size)//Проверява дали коректно е въведен размерът на клетката.
{
	return (size.compare("small") == 0 || size.compare("medium") == 0 || size.compare("large") == 0);
}

bool isCorrect::isCorrectClimate(std::string climate)//Проверява дали коректно е въведен климатът на клетката.
{
	return (climate.compare("dry") == 0 || climate.compare("air") == 0
		|| climate.compare("water") == 0);
}

bool isCorrect::isCorrectCageEmployee(const Cage& other)
{
	/*Проверява дали е коректно съотношението животни в клетката и брой на служителите в клетката като се има предвид, че
	за 1 животно са необходими 2 човека, за 2ж. - 4ч., за 3ж. - 5ч., за 4ж. - 6ч. и така до 10ж. - 12ч.*/
	if (other.getAnimals().size() == 0)
	{
		return other.getCountEmp() == 0;
	}
	else if (other.getAnimals().size() == 1)
	{
		return other.getCountEmp() == 2;
	}
	else if (other.getAnimals().size() >= 2 && other.getAnimals().size() <= 10)
	{
		return (other.getCountEmp() == other.getAnimals().size() + 2);
	}
	else return false;
}

bool isCorrect::isCorrectCageAnimal(const Cage& other, std::vector<Dinosaurs>animals)
{
	/*Проверява дали е коректно съотношението размер на клетката и брой на животните в клетката като се има предвид, че
	в малка клетка може да има най-много едно животно, в средна - най-много три, а в голяма - най-много 10.*/
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

bool isCorrect::isCorrectClimateAnimal(const std::string& climate, const Dinosaurs& animal)
{
	/*Проверява дали е коректно съотношението климат на клетката и вид на животните в клетката като се има предвид, че
	ако климатът е сухоземен, то в тази клетка могат да живеят 2 вида - Бронтозавър и Тиранозавър,
	ако климатът е въздушен, то в тази клетка може да живее само Птицезавър,
	ако климятът е воден, то в тази клетка може да живее само Плезиозавър.*/
	if (climate == "dry")
	{
		return (animal.getSpecies() == "Brontosaurus" || animal.getSpecies() == "Tyrannosaur");
	}
	else if (climate == "air")
	{
		return (animal.getSpecies() == "Pterosaur");
	}
	else if (climate == "water")
	{
		return (animal.getSpecies() == "Plesiosaur");
	}
	else return false;
}

bool isCorrect::isCorrectData(size_t number, std::vector<size_t>helper)
{
	/*Проверява по дадено число, дали това число се среща в масива от числа.
	Използва се в "main.cpp", за избиране на коректна клетка от множество от клетки.*/
	bool flag = false;
	for (size_t i = 0; i < helper.size(); i++)
	{
		if (helper[i] == (number - 1)) flag = true;//number е номерът на клетката, (number-1) е позицията в масива.
	}
	return flag;
}

bool isCorrect::isCorrectQuantityInWarehouse(const Warehouse& other)
{
	//Проверява дали е коректно количеството храна в склада.
	return (other.getQuantityGrass() >= 0 && other.getQuantityMeat() >= 0 && other.getQuantityFish() >= 0);
}