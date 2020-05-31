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

	void storeInBin();//��������� � ������� ����.
	void readFromBin();//����� �� ������� ����.
	bool isEmpty();//��������� ���� � ������� �������� ����� �� ������ � ���� ��� ������� � �����.
	void loadCages();
	void print() const;

public:
	JurassicPark() = default;
	JurassicPark(std::vector<Cage> cages, Warehouse warehouse);
		
	void loadPark();
	
};






#endif
