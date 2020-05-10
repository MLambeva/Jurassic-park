#ifndef isCORRECT_H
#define isCORRECT_H
#include<string>
#include<vector>
#include"Dinosaurs.h"
#include"Cage.h"
#include"Warehouse.h"

class isCorrect
{
public:
	static bool isLetter(char x);
	//��������� ���� �������� � ����� �������� �����.
	
	static bool isCorrectName(std::string name);
	//��������� ���� �������� � �������� ����� �� ����������.
	static bool isCorrectGender(std::string gender);
	//��������� ���� �������� � ������� ����.
	static bool isCorrectEra(std::string era);
	//��������� ���� �������� � �������� �����.
	static bool isCorrectOrder(std::string order);
	//��������� ���� �������� � ������� �������� �� ����������.
	static bool isCorrectSpecies(std::string species);
	//��������� ���� �������� � ������� ����� �� ����������.
	static bool isCorrectFood(std::string food);
	//��������� ���� �������� � �������� ������� �� ����������.
	
	static bool isCorrectAnimal(const Dinosaurs& other);
	//��������� ���� �������� � ������� ����������.
	
	static bool isCorrectSize(std::string size);
	//��������� ���� �������� � ������� �������� �� ��������.
	static bool isCorrectClimate(std::string climate);
	//��������� ���� �������� � ������� �������� �� ��������.

	static bool isCorrectCageEmployee(const Cage& other);
	//��������� ���� � �������� ������������� ������� � �������� � ���� �� ����������� � ��������.
	static bool isCorrectCageAnimal(const Cage& other, std::vector<Dinosaurs> animals);
	//��������� ���� � �������� ������������� ������ �� �������� � ���� �� ��������� � ��������.
	static bool isCorrectClimateAnimal(const std::string& climate, const Dinosaurs& animal);
	//��������� ���� � �������� ������������� ������ �� �������� � ��� �� ��������� � ��������.
	
	static bool isCorrectData(size_t number, std::vector<size_t>helper);
	//��������� �� ������ �����, ���� ���� ����� �� ����� � ������ �� �����.

	static bool isCorrectStaffName(std::string name);
	//��������� ���� �������� �� �������� ������� �� ������ �� ���������.

	static bool isCorrectQuantityInWarehouse(const Warehouse& other);
	//��������� ���� � �������� ������������ ����� � ������.
};

#endif 