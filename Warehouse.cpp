#include<iostream>
#include<string>
#include<fstream>
#include<cassert>
#include"Warehouse.h"
#include"isCorrect.h"

Warehouse::Warehouse(int quantityGrass, int quantityMeat, int quantityFish)
{
	this->quantityGrass = quantityGrass;
	this->quantityMeat = quantityMeat;
	this->quantityFish = quantityFish;
}

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

void Warehouse::loadWarehouseWithGrass()//Зареждане на склада с трева
{
	int loadGrass;
	std::cout << "What quantity grass do you want to load?\n->";
	std::cin >> loadGrass;
	this->quantityGrass += loadGrass;
}

void Warehouse::loadWarehouseWithMeat()//Зареждане на склада с месо
{
	int loadMeat;
	std::cout << "What quantity meat do you want to load?\n->";
	std::cin >> loadMeat;
	this->quantityMeat += loadMeat;
}

void Warehouse::loadWarehouseWithFish()//Зареждане на склада с риба
{
	int loadFish;
	std::cout << "What quantity fish do you want to load?\n->";
	std::cin >> loadFish;
	this->quantityFish += loadFish;
}

void Warehouse::loadWarehouse()//Зареждане на склада с трева, месо и риба
{
	(*this).loadWarehouseWithGrass();
	(*this).loadWarehouseWithMeat();
	(*this).loadWarehouseWithFish();
}

std::ostream& operator<<(std::ostream& out, const Warehouse& other)
{
	assert(isCorrect::isCorrectQuantityInWarehouse(other));
	out << other.quantityGrass << " " << other.quantityMeat << " " << other.quantityFish << '\n';
	return out;
}

void Warehouse::write(std::ofstream& out)//Записване на информация за склада в бинарен файл
{
	out.write((char*)(&this->quantityGrass), sizeof(int));
	out.write((char*)(&this->quantityMeat), sizeof(int));
	out.write((char*)(&this->quantityFish), sizeof(int));
}

void Warehouse::read(std::ifstream& in)//Четене на информация за склада от бинарен файл
{
	in.read((char*)(&this->quantityGrass), sizeof(this->quantityGrass));
	in.read((char*)(&this->quantityMeat), sizeof(this->quantityMeat));
	in.read((char*)(&this->quantityFish), sizeof(this->quantityFish));
}