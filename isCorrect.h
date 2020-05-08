#ifndef isCORRECT_H
#define isCORRECT_H
#include<string>
#include<vector>
#include<cassert>
#include"Dinosaurs.h"
#include"Cage.h"


bool isCorrectName(std::string name);
bool isCorrectGender(std::string gender);
bool isCorrectEra(std::string era);
bool isCorrectOrder(std::string order);
bool isCorrectSpecies(std::string species);
bool isCorrectFood(std::string food);

bool isCorrectAnimal(const Dinosaurs& other);

bool isCorrectSize(std::string size);
bool isCorrectClimate(std::string climate);
bool isCorrectCageEmployee(const Cage& other);
bool isCorrectCageAnimal(const Cage& other, std::vector<Dinosaurs> animals);
bool isCorrectClimateAnimal(const std::string& climate, const Dinosaurs& animal);

bool isCorrectData(size_t number, std::vector<size_t>helper);

#endif 