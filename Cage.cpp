#include<iostream>
#include<cassert>
#include<fstream>
#include"Cage.h"
#include"HelperFunctions.h"

Cage::Cage(const std::string& size, const std::string& climate)
{
	assert(HelperFunctions::isCorrectSize(size));
	this->size = size;
	assert(HelperFunctions::isCorrectClimate(climate));
	this->climate = climate;
}

std::string Cage::getSize() const
{
	return this->size;
}

std::string Cage::getClimate() const
{
	return this->climate;
}

size_t Cage::getCountEmp() const
{
	return this->countEmp;
}

std::vector<Dinosaur> Cage::getAnimals() const
{
	return this->animals;
}

std::string Cage::getEra() const
{
	return this->era;
}

void Cage::setAnimal(const Dinosaur& other)
{
	this->animals.push_back(other);
}

void Cage::setCountEmp(const size_t& countEmp)
{
	this->countEmp = countEmp;
}

void Cage::buildCageForExistedAnimal(std::istream& in, const Dinosaur& animal)
{//Създаване на клетка в зависимост от вида на животното, което ще е вътре
	std::string size;
	do {
		std::cout << "Size(small/medium/large):";
		std::getline(in, size);
	} while (!HelperFunctions::isCorrectSize(size));

	std::string climate;
	do {
		std::cout << "Climate(dry/air/water):";
		std::getline(in, climate);
	} while (!(HelperFunctions::isCorrectClimate(climate) && HelperFunctions::isCorrectClimateAnimal(climate, animal)));
	//Ако животното е или Бронтозавър, или Тиранозавър, то климатът трябва да е сухоземен.
    //Ако животното е Плезиозавър, то климатът трябва да е воден.
	//Ако животното е Птицезавър, то климатът трябва да е въздушен.
	if (in)
	{
		this->size = size;
		this->climate = climate;
		this->countEmp = 0;
		std::cout << "You build new cage " << size << " size and " << climate
			<< " climate with " << this->countEmp << " employee inside!\n";
	}
}

void Cage::buildCage(std::istream& in)//Създаване на клетка, в която няма животни и персонал, чрез посочване на размер и климат
{
	std::string size;
	do {
		std::cout << "Size(small/medium/large):";
		std::getline(in, size);
	} while (!HelperFunctions::isCorrectSize(size));
	
	std::string climate;
	do {
		std::cout << "Climate(dry/air/water):";
		std::getline(in, climate);
	} while (!HelperFunctions::isCorrectClimate(climate));
	
	if (in)
	{
		this->size = size;
		this->climate = climate;
		this->countEmp = 0;
		std::cout << "You build new cage " << size << " size and " << climate 
			      << " climate with " << this->countEmp << " employee inside!\n";
	}
}

void Cage::removeAnimalAndStaffFromCage(size_t index)//Премахване на животно и персонал по дадено число
{/*Премахването на животно е съпроводено с премахване на персонал като се има предвид, че
   за 1 животно са необходими 2 човека, за 2ж. - 4ч., за 3ж. - 5ч., за 4ж. - 6ч. и така до 10ж. - 12ч.*/
	if (this->animals.size() == 1 || this->animals.size() == 2)
	{
		this->countEmp -= 2;
	}
	else if (this->animals.size() >= 3 && this->animals.size() <= 10)
	{
		this->countEmp--;
	}
	this->animals.erase(this->animals.begin() + (index - 1));//Премахване на животно, което се намира на позиция index
}

std::ostream& operator << (std::ostream& out, const Cage& other)
{//Извеждане на информация за дадена клетка
	out << "Size: " << other.size << "; Climate: " << other.climate << "; Employee:" << other.countEmp << " " << other.era << '\n';
	for (size_t i = 0; i < other.animals.size(); i++)
	{
		out << "Animal " << i + 1 << ")" << other.animals[i] << '\n';
	}
	std::cout << "\n============================================================\n";

	return out;
}

void Cage::write(std::ofstream& out)//Записване на информация за клетка в бинарен файл
{
	/*
	Понеже повечето член данни от класа Клетка са стрингове, то начинът, по който записваме, е еднакъв, т.е.
	1)В новосъздадена променлива запазваме размера на стринга.
	2)Записваме във файла размера.
	3)Записваме информацията от самия стринг.
	*/
	int sizeSize = this->size.size();
	out.write((char*)(&sizeSize), sizeof(sizeSize));
	out.write(this->size.c_str(), sizeof(char) * sizeSize);

	int climateSize = this->climate.size();
	out.write((char*)(&climateSize), sizeof(climateSize));
	out.write(this->climate.c_str(), sizeof(char) * climateSize);

	//Записване на броя служители във файла.
	out.write((char*)(&this->countEmp), sizeof(this->countEmp));

	int eraSize = this->era.size();
	out.write((char*)(&eraSize), sizeof(eraSize));
	out.write(era.c_str(), sizeof(char) * eraSize);

	/*Член-данната "animals" е вектор от животни, затова първо записваме броя животни, а след това чрез цикъл записваме и данните
	за самите животни,чрез функцията "write" от "class Dinosaur", като си осигуряваме, че ако няма животни, то няма да се запише никаква информация за тях.*/
	int animalsSize = this->animals.size();
	out.write((char*)(&animalsSize), sizeof(animalsSize));
	for (int i = 0; i < animalsSize; i++)
	{
		animals[i].write(out);
	}
}

void Cage::read(std::ifstream& in)//Четене на информация за клетка от бинарен файл
{
	/*Понеже повечето член данни от класа Клетка са стрингове, то начинът, по който четем, е еднакъв, т.е.
	1)Прочитаме дължината на стринга.
	2)Заделяме динамично памет, като имаме предвид да има място и за затапващия символ.
	3)Присвояваме стойността на динамично заделената променлива на стринга.
	4)Освобождаваме заделената памет.
	*/
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

	//Четем броя служители от файла.
	in.read((char*)(&this->countEmp), sizeof(this->countEmp));

	int eraSize;
	in.read((char*)(&eraSize), sizeof(eraSize));
	char* era = new char[eraSize + 1];
	era[eraSize] = '\0';
	this->era = era;
	delete[] era;

	/*Член-данната "animals" е вектор от животни, затова първо прочитаме броя животни, а след това чрез цикъл четем и данните
	за самите животни чрез функцията "read" от "class Dinosaur" като дабавяме прочетеното във вектора "animals".*/
	int animalsSize;
	in.read((char*)(&animalsSize), sizeof(animalsSize));
	for (int i = 0; i < animalsSize; i++)
	{
		Dinosaur reader;
		reader.read(in);
		this->animals.push_back(reader);
	}
}