#ifndef DINOSAURS_H
#define DINOSAURS_H
#include<iostream>
#include<string>
#include<fstream>

class Dinosaurs
{
private:
    std::string name;
    std::string gender;
    std::string era;
    std::string order;
    std::string species;
    std::string food;
public:
    Dinosaurs() = default;
    Dinosaurs(std::string name, std::string gender, std::string era, 
              std::string order, std::string species, std::string food);
    
    bool operator==(const Dinosaurs& other)const;

    std::string getName() const;
    std::string getGender() const;
    std::string getEra() const;
    std::string getOrder() const;
    std::string getSpecies() const;
    std::string getFood() const;

    friend std::ostream& operator << (std::ostream& out, const Dinosaurs& other);
    
    void createAnimal(std::istream& in);
    
    void write(std::ofstream& out);
    void read(std::ifstream& in);
    
};


#endif 

