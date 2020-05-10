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
	//Проверява дали символът е малка латинска буква.
	
	static bool isCorrectName(std::string name);
	//Проверява дали коректно е въведено името на динозавъра.
	static bool isCorrectGender(std::string gender);
	//Проверява дали коректно е въведен пола.
	static bool isCorrectEra(std::string era);
	//Проверява дали коректно е въведена ерата.
	static bool isCorrectOrder(std::string order);
	//Проверява дали коректно е въведен разредът на динозавъра.
	static bool isCorrectSpecies(std::string species);
	//Проверява дали коректно е въведен видът на динозавъра.
	static bool isCorrectFood(std::string food);
	//Проверява дали коректно е въведена храната на динозавъра.
	
	static bool isCorrectAnimal(const Dinosaurs& other);
	//Проверява дали коректно е въведен диназавъра.
	
	static bool isCorrectSize(std::string size);
	//Проверява дали коректно е въведен размерът на клетката.
	static bool isCorrectClimate(std::string climate);
	//Проверява дали коректно е въведен климатът на клетката.

	static bool isCorrectCageEmployee(const Cage& other);
	//Проверява дали е коректно съотношението животни в клетката и брой на служителите в клетката.
	static bool isCorrectCageAnimal(const Cage& other, std::vector<Dinosaurs> animals);
	//Проверява дали е коректно съотношението размер на клетката и брой на животните в клетката.
	static bool isCorrectClimateAnimal(const std::string& climate, const Dinosaurs& animal);
	//Проверява дали е коректно съотношението климат на клетката и вид на животните в клетката.
	
	static bool isCorrectData(size_t number, std::vector<size_t>helper);
	//Проверява по дадено число, дали това число се среща в масива от числа.

	static bool isCorrectQuantityInWarehouse(const Warehouse& other);
	//Проверява дали е коректно количеството храна в склада.
};

#endif 