#include<iostream>
#include<fstream>
#include<cassert>
#include"Dinosaurs.h"
#include"isCorrect.h"

bool Dinosaurs::operator==(const Dinosaurs& other)const
{
	return (this->name == other.name && this->gender == other.gender && this->era == other.era && 
		    this->order == other.order && this->species == other.species && this->food == other.food);
}

bool Dinosaurs::operator!=(const Dinosaurs& other)const
{
	return !((*this) == other);
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

std::ostream& operator<<(std::ostream& out, const Dinosaurs& other)//Извеждане на информация за дадена клетка.
{
	assert(isCorrect::isCorrectAnimal(other));
	/*Проверява дали е коректно зададено животното, т.е. дали е с правилно име, пол, ера, разред, вид и храна
	  Ако е правилно, то извежда информация за него. */
	out << other.name << " " << other.gender << " " << other.era
		<< " " << other.order << " " << other.species << " " << other.food ;
	return out;
}

void Dinosaurs::createAnimal(std::istream& in)//Създаване на динозавър по име, пол, ера и разред
{
	std::string name;
	do {
		std::cout << "Name:";
		std::getline(in, name);
	} while (!isCorrect::isCorrectName(name));//Едно име, започващо с главна латинска буква, последвано от малки латински букви

	std::string gender;
	do {
		std::cout << "Gender(female/male):";
		std::getline(in, gender);
	} while (!isCorrect::isCorrectGender(gender));//female/male

	std::string era;
	do {
		std::cout << "Era(Triassic/Cretaceous/Jura):";
		std::getline(in, era);
	} while (!isCorrect::isCorrectEra(era));//Triassic/Cretaceous/Jura !Първа буква - главна!

	std::string order;
	do {
		std::cout << "Order(herbivorous/carnivorous/flying/aqueous):";
		std::getline(in, order);
	} while (!isCorrect::isCorrectOrder(order));//herbivorous/carnivorous/flying/aqueous

	if (in)
	{
		this->name = name;
		this->gender = gender;
		this->era = era;
		this->order = order;
		if (this->order == "herbivorous")//Ако е тревопасно, то видът му е Бронтозавър, а храната - трева.
		{
			this->species = "Brontosaurus";
			std::cout << "species:Brontosaurus\n";
			this->food = "grass";
			std::cout << "food:grass\n";
		}
		else if (this->order == "carnivorous")//Ако е месоядно, то видът му е Тиранозавър, а храната - месо
		{
			this->species = "Tyrannosaur";
			std::cout << "species:Tyrannosaur\n";
			this->food = "meat";
			std::cout << "food:meat\n";
		}
		else if (this->order == "flying")//Ако е летящо, то видът му е Птицезавър, а храната - месо
		{
			this->species = "Pterosaur";
			std::cout << "species:Pterosaur\n";
			this->food = "meat";
			std::cout << "food:meat\n";
		}
		else if (this->order == "aqueous")//Ако е водно, то видът му е Плезиозавър, а храната - риба
		{
			this->species = "Plesiosaur";
			std::cout << "species:Plesiosaur\n";
			this->food = "fish";
			std::cout << "food:fish\n";
		}
	}
}

void Dinosaurs::write(std::ofstream& out)//Записване на информация за динозаври в бинарен файл
{
	/*Понеже всички член данни от класа Динозаври са стрингове, то начинът, по който записваме, е еднакъв, т.е.
	1)В новосъздадена променлива запазваме размера на стринга.
	2)Записваме във файла размера.
	3)Записваме информацията от самия стринг.*/
	int nameSize = this->name.size();
	out.write((char*)(&nameSize), sizeof(nameSize));
	out.write(this->name.c_str(), sizeof(char) * nameSize);

	int genderSize = this->gender.size();
	out.write((char*)(&genderSize), sizeof(genderSize));
	out.write(this->gender.c_str(), sizeof(char) * genderSize);

	int eraSize = this->era.size();
	out.write((char*)(&eraSize), sizeof(eraSize));
	out.write(this->era.c_str(), sizeof(char) * eraSize);

	int orderSize = this->order.size();
	out.write((char*)(&orderSize), sizeof(orderSize));
	out.write(this->order.c_str(), sizeof(char) * orderSize);

	int speciesSize = this->species.size();
	out.write((char*)(&speciesSize), sizeof(speciesSize));
	out.write(this->species.c_str(), sizeof(char) * speciesSize);

	int foodSize = this->food.size();
	out.write((char*)(&foodSize), sizeof(foodSize));
	out.write(this->food.c_str(), sizeof(char) * foodSize);
}

void Dinosaurs::read(std::ifstream& in)//Четене на информация за динозаври от бинарен файл
{
	/*Понеже всички член данни от класа Динозаври са стрингове, то начинът по който четем е еднакъв, т.е.
	1)Прочитаме дължината на стринга.
	2)Заделяме динамично памет, като имаме предвид да има място и за затапващия символ.
	3)Присвояваме стойността на динамично заделената променлива на стринга.
	4)Освобождаваме заделената памет.*/
	int nameSize;
	in.read((char*)(&nameSize), sizeof(nameSize));
	char* name = new char[nameSize + 1];
	in.read(name, sizeof(char) * nameSize);
	name[nameSize] = '\0';
	this->name = name;
	delete[] name;

	int genderSize;
	in.read((char*)(&genderSize), sizeof(genderSize));
	char* gender = new char[genderSize + 1];
	in.read(gender, sizeof(char) * genderSize);
	gender[genderSize] = '\0';
	this->gender = gender;
	delete[] gender;

	int eraSize;
	in.read((char*)(&eraSize), sizeof(eraSize));
	char* era = new char[eraSize + 1];
	in.read(era, sizeof(char) * eraSize);
	era[eraSize] = '\0';
	this->era = era;
	delete[]era;

	int orderSize;
	in.read((char*)(&orderSize), sizeof(orderSize));
	char* order = new char[orderSize + 1];
	in.read(order, sizeof(char) * orderSize);
	order[orderSize] = '\0';
	this->order = order;
	delete[] order;

	int speciesSize;
	in.read((char*)(&speciesSize), sizeof(speciesSize));
	char* species = new char[speciesSize + 1];
	in.read(species, sizeof(char) * speciesSize);
	species[speciesSize] = '\0';
	this->species = species;
	delete[] species;

	int foodSize;
	in.read((char*)(&foodSize), sizeof(foodSize));
	char* food = new char[foodSize + 1];
	in.read(food, sizeof(char) * foodSize);
	food[foodSize] = '\0';
	this->food = food;
	delete[] food;
}

