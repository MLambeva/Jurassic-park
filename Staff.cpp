#include"Staff.h"

void Employee::appointment(std::istream& in, const Cage& other)
{
	std::string name;
	std::cout << "You must appoint new employee!\n";
	do {
		std::cout << "Name of employee:";
		std::getline(in, name);
	} while (!isCorrect::isCorrectStaffName(name));
	std::string orderOfDinosaurs;
	do {
		std::cout << "Order(herbivorous/carnivorous/flying/aqueous):";
		std::getline(in, orderOfDinosaurs);
	} while (!(isCorrect::isCorrectOrder(orderOfDinosaurs) && other.getAnimals()[0].getOrder() == orderOfDinosaurs));

	if (in)
	{
		this->name = name;
		this->orderOfDinosaurs = orderOfDinosaurs;
		
		std::cout << "You appoint new employee!\n";
	}
}