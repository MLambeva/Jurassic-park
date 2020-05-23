#ifndef DINOSAUR_H
#define DINOSAUR_H
#include<string>

class Dinosaur
{
private:
    std::string name;
    std::string gender;
    std::string era;
    std::string order;
    std::string species;
    std::string food;
public:
    Dinosaur() = default;
    
    bool operator==(const Dinosaur& other)const;
    bool operator!=(const Dinosaur& other)const;

    std::string getName() const;
    std::string getGender() const;
    std::string getEra() const;
    std::string getOrder() const;
    std::string getSpecies() const;
    std::string getFood() const;

    friend std::ostream& operator << (std::ostream& out, const Dinosaur& other);
    //Извеждане на информация за дадена клетка.
    
    void createAnimal(std::istream& in);
    //Създаване на динозавър по име, пол, ера и разред.
    
    void write(std::ofstream& out);
    //Записване на информация на динозаври в бинарен файл.
    void read(std::ifstream& in);
    //Четене на информация за динозаври от бинарен файл.
};

#endif 

