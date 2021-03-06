#include<iostream>
#include<string>
#include<fstream>
#include<cassert>
#include"Warehouse.h"
#include"HelperFunctions.h"


int Warehouse::getQuantityGrass() const
{
	return this->quantityGrass;
}

int Warehouse::getQuantityMeat() const
{
	return this->quantityMeat;
}

int Warehouse::getQuantityFish() const
{
	return this->quantityFish;
}

void Warehouse::setQuantityGrass(int quantityGrass)
{
	this->quantityGrass = quantityGrass;
}

void Warehouse::setQuantityMeat(int quantityMeat)
{
	this->quantityMeat = quantityMeat;
}

void Warehouse::setQuantityFish(int quantityFish)
{
	this->quantityFish = quantityFish;
}

void Warehouse::loadWarehouseWithGrass()//��������� �� ������ � �����
{
	int loadGrass;
	std::cout << "What quantity grass do you want to load?\n->";
	std::cin >> loadGrass;
	this->quantityGrass += loadGrass;
}

void Warehouse::loadWarehouseWithMeat()//��������� �� ������ � ����
{
	int loadMeat;
	std::cout << "What quantity meat do you want to load?\n->";
	std::cin >> loadMeat;
	this->quantityMeat += loadMeat;
}

void Warehouse::loadWarehouseWithFish()//��������� �� ������ � ����
{
	int loadFish;
	std::cout << "What quantity fish do you want to load?\n->";
	std::cin >> loadFish;
	this->quantityFish += loadFish;
}

void Warehouse::loadWarehouse()//��������� �� ������ � �����, ���� � ����
{
	(*this).loadWarehouseWithGrass();
	(*this).loadWarehouseWithMeat();
	(*this).loadWarehouseWithFish();
}

std::ostream& operator<<(std::ostream& out, const Warehouse& other)
{
	assert(HelperFunctions::isCorrectQuantityInWarehouse(other));
	out << other.quantityGrass << "kg grass, " << other.quantityMeat << "kg meat, " << other.quantityFish << "kg fish.";
	return out;
}

void Warehouse::write(std::ofstream& out)//��������� �� ���������� �� ������ � ������� ����
{
	out.write((char*)(&this->quantityGrass), sizeof(int));
	out.write((char*)(&this->quantityMeat), sizeof(int));
	out.write((char*)(&this->quantityFish), sizeof(int));
}

void Warehouse::read(std::ifstream& in)//������ �� ���������� �� ������ �� ������� ����
{
	in.read((char*)(&this->quantityGrass), sizeof(this->quantityGrass));
	in.read((char*)(&this->quantityMeat), sizeof(this->quantityMeat));
	in.read((char*)(&this->quantityFish), sizeof(this->quantityFish));
}