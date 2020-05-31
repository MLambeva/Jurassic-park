#ifndef JURRASIC_PARK_H
#define JURASSIC_PARK_H
#include<vector>
#include<fstream>
#include<iostream>
#include<ctime>
#include"Cage.h"
#include"Dinosaur.h"
#include"HelperFunctions.h"
#include"Warehouse.h"

class JurassicPark
{
private:
	std::vector<Cage> cages;
	Warehouse warehouse;

	void storeInBin();//Записваме в бинарен файл.
	void readFromBin();//Четем от бинарен файл.
	bool isEmpty();//Проверява дали е отворен коректно файла за четене и дали има животни в парка.
	void loadCages();
	void print() const;

public:
	JurassicPark() = default;
	JurassicPark(std::vector<Cage> cages, Warehouse warehouse);
		
	void loadPark();
	
};






#endif
