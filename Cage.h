#ifndef CAGE_H
#define CAGE_H
#include<string>
#include<vector>
#include"Dinosaur.h"

class Cage
{
private:
	std::string size;
	std::string climate;
	int countEmp = 0;//���� ��������� � ��������
	std::string era;
	std::vector<Dinosaur> animals;
public:
	Cage() = default;
	Cage(const std::string& size, const std::string& climate);
	
	std::string getSize() const;
	std::string getClimate() const;
	size_t getCountEmp() const;
	std::vector<Dinosaur> getAnimals() const;
	std::string getEra() const;

	void setAnimal(const Dinosaur& other);
	void setCountEmp(const size_t& countEmp);

	void buildCageForExistedAnimal(std::istream& in, const Dinosaur& animal);
	//��������� �� ������ � ���������� �� ���� �� ���������, ����� �� � �����.
	void buildCage(std::istream& in);
	//��������� �� ������, � ����� ���� ������� � ��������, ���� ��������� �� ������ � ������.
	void removeAnimalAndStaffFromCage(size_t index);//���������� �� ������� � �������� �� ������ �����.
	friend std::ostream& operator << (std::ostream& out, const Cage& other);
	//��������� �� ���������� �� ������ ������.

	void write(std::ofstream& out);
	//��������� �� ���������� �� ������ � ������� ����.
	void read(std::ifstream& in);
	//������ �� ���������� �� ������ �� ������� ����.
};


#endif
