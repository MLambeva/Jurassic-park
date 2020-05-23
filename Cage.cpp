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
{//��������� �� ������ � ���������� �� ���� �� ���������, ����� �� � �����
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
	//��� ��������� � ��� �����������, ��� �����������, �� �������� ������ �� � ���������.
    //��� ��������� � �����������, �� �������� ������ �� � �����.
	//��� ��������� � ����������, �� �������� ������ �� � ��������.
	if (in)
	{
		this->size = size;
		this->climate = climate;
		this->countEmp = 0;
		std::cout << "You build new cage " << size << " size and " << climate
			<< " climate with " << this->countEmp << " employee inside!\n";
	}
}

void Cage::buildCage(std::istream& in)//��������� �� ������, � ����� ���� ������� � ��������, ���� ��������� �� ������ � ������
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

void Cage::removeAnimalAndStaffFromCage(size_t index)//���������� �� ������� � �������� �� ������ �����
{/*������������ �� ������� � ����������� � ���������� �� �������� ���� �� ��� �������, ��
   �� 1 ������� �� ���������� 2 ������, �� 2�. - 4�., �� 3�. - 5�., �� 4�. - 6�. � ���� �� 10�. - 12�.*/
	if (this->animals.size() == 1 || this->animals.size() == 2)
	{
		this->countEmp -= 2;
	}
	else if (this->animals.size() >= 3 && this->animals.size() <= 10)
	{
		this->countEmp--;
	}
	this->animals.erase(this->animals.begin() + (index - 1));//���������� �� �������, ����� �� ������ �� ������� index
}

std::ostream& operator << (std::ostream& out, const Cage& other)
{//��������� �� ���������� �� ������ ������
	out << "Size: " << other.size << "; Climate: " << other.climate << "; Employee:" << other.countEmp << " " << other.era << '\n';
	for (size_t i = 0; i < other.animals.size(); i++)
	{
		out << "Animal " << i + 1 << ")" << other.animals[i] << '\n';
	}
	std::cout << "\n============================================================\n";

	return out;
}

void Cage::write(std::ofstream& out)//��������� �� ���������� �� ������ � ������� ����
{
	/*
	������ �������� ���� ����� �� ����� ������ �� ���������, �� �������, �� ����� ���������, � �������, �.�.
	1)� ������������� ���������� ��������� ������� �� �������.
	2)��������� ��� ����� �������.
	3)��������� ������������ �� ����� ������.
	*/
	int sizeSize = this->size.size();
	out.write((char*)(&sizeSize), sizeof(sizeSize));
	out.write(this->size.c_str(), sizeof(char) * sizeSize);

	int climateSize = this->climate.size();
	out.write((char*)(&climateSize), sizeof(climateSize));
	out.write(this->climate.c_str(), sizeof(char) * climateSize);

	//��������� �� ���� ��������� ��� �����.
	out.write((char*)(&this->countEmp), sizeof(this->countEmp));

	int eraSize = this->era.size();
	out.write((char*)(&eraSize), sizeof(eraSize));
	out.write(era.c_str(), sizeof(char) * eraSize);

	/*����-������� "animals" � ������ �� �������, ������ ����� ��������� ���� �������, � ���� ���� ���� ����� ��������� � �������
	�� ������ �������,���� ��������� "write" �� "class Dinosaur", ���� �� �����������, �� ��� ���� �������, �� ���� �� �� ������ ������� ���������� �� ���.*/
	int animalsSize = this->animals.size();
	out.write((char*)(&animalsSize), sizeof(animalsSize));
	for (int i = 0; i < animalsSize; i++)
	{
		animals[i].write(out);
	}
}

void Cage::read(std::ifstream& in)//������ �� ���������� �� ������ �� ������� ����
{
	/*������ �������� ���� ����� �� ����� ������ �� ���������, �� �������, �� ����� �����, � �������, �.�.
	1)��������� ��������� �� �������.
	2)�������� ��������� �����, ���� ����� ������� �� ��� ����� � �� ���������� ������.
	3)����������� ���������� �� ��������� ���������� ���������� �� �������.
	4)������������� ���������� �����.
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

	//����� ���� ��������� �� �����.
	in.read((char*)(&this->countEmp), sizeof(this->countEmp));

	int eraSize;
	in.read((char*)(&eraSize), sizeof(eraSize));
	char* era = new char[eraSize + 1];
	era[eraSize] = '\0';
	this->era = era;
	delete[] era;

	/*����-������� "animals" � ������ �� �������, ������ ����� ��������� ���� �������, � ���� ���� ���� ����� ����� � �������
	�� ������ ������� ���� ��������� "read" �� "class Dinosaur" ���� �������� ����������� ��� ������� "animals".*/
	int animalsSize;
	in.read((char*)(&animalsSize), sizeof(animalsSize));
	for (int i = 0; i < animalsSize; i++)
	{
		Dinosaur reader;
		reader.read(in);
		this->animals.push_back(reader);
	}
}