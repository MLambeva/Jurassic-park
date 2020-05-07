#include"Warehouse.h"
#include<iostream>

Warehouse::Warehouse(int quantityGrass, int quantityMeat, int quantityFish)
{
	this->quantityGrass = quantityGrass;
	this->quantityMeat = quantityMeat;
	this->quantityFish = quantityFish;
}

int Warehouse::getQuantityGrass()
{
	return this->quantityGrass;
}

int Warehouse::getQuantityMeat()
{
	return this->quantityMeat;
}

int Warehouse::getQuantityFish()
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

void Warehouse::loadWarehouseWithGrass()
{
	int loadGrass;
	std::cout << "What quantity grass do you want to load?\n->";
	std::cin >> loadGrass;
	this->quantityGrass += loadGrass;
}

void Warehouse::loadWarehouseWithMeat()
{
	int loadMeat;
	std::cout << "What quantity meat do you want to load?\n->";
	std::cin >> loadMeat;
	this->quantityMeat += loadMeat;
}

void Warehouse::loadWarehouseWithFish()
{
	int loadFish;
	std::cout << "What quantity fish do you want to load?\n->";
	std::cin >> loadFish;
	this->quantityFish += loadFish;
}

void Warehouse::loadWarehouse()
{
	(*this).loadWarehouseWithGrass();
	(*this).loadWarehouseWithMeat();
	(*this).loadWarehouseWithFish();
}