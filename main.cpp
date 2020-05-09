#include"Dinosaurs.h"
#include"Cage.h"
#include"isCorrect.h"
#include"Warehouse.h"
#include"Staff.h"

void storeInBin(std::vector<Cage> c, Warehouse& w)
{
	std::ofstream outputFile("JurassicPark.bin", std::ios::out | std::ios::binary);
	if (!outputFile.is_open())
	{
		std::cout << "Error! The file cannot be opened!\n";
		return;
	}
	for (size_t i = 0; i < c.size(); i++)
	{
		c[i].write(outputFile);
	}
	w.write(outputFile);

	outputFile.close();
}

void readFromBin(std::vector<Cage>& c, Warehouse& w)
{
	std::ifstream inputFile("JurassicPark.bin", std::ios::in | std::ios::binary | std::ios::ate);
	if (!inputFile.is_open())
	{
		std::cout << "Error! The file cannot be opened!\n";
		return;
	}
	std::streampos len = inputFile.tellg() - (std::streampos)12;
	inputFile.seekg(0, std::ios::beg);
	while (inputFile.tellg() != len)
	{
		Cage newCage;
		newCage.read(inputFile);
		c.push_back(newCage);
	}
	w.read(inputFile);

	inputFile.close();
}

int main()
{
	Warehouse warehouse(300, 300, 300);
	//Cage first("small", "dry", 0);
	//Cage second("medium", "water", 0);
	//Cage third("large", "air", 0);
	//std::vector<Cage> cages1 = { first, second, third};
	std::vector<Cage> cages = { };
	//storeInBin(cages1, warehouse);
	readFromBin(cages, warehouse);
	
	std::vector<size_t> saveRightCage = { };
	std::vector<Dinosaurs> dinosaurs = { };
	std::vector<Employee> staff = { };
	Dinosaurs saverDino;
	Cage saverCage;
	size_t action;
	do
	{
		saveRightCage.clear();
		std::cout << "\nWhat do you want to do?\n"
			<< "1)Accept new animal.\n"
			<< "2)Build new cage.\n"
			<< "3)Remove available animal.\n"
			<< "4)Feed dinosaurs.\n"
			<< "5)Load the warehouse with food.\n"
			<< "6)Finalize your Jurassic Park!\n";

		do {
			std::cout << "->";
			std::cin >> action;
			std::cin.ignore();
		} while (!(action >= 1 && action <= 6));

		if (action == 1)//1)Accept new animal.
		{
			saveRightCage.clear();
			saverDino.createAnimal(std::cin);
			dinosaurs.push_back(saverDino);
			for (size_t i = 0; i < cages.size(); i++)
			{
				if (isCorrect::isCorrectCageAnimal(cages[i], cages[i].getAnimals()) && isCorrect::isCorrectClimateAnimal(cages[i].getClimate(), saverDino))
				{
					if (cages[i].getAnimals().size() != 0)
					{
						if (cages[i].getAnimals()[0].getOrder() == saverDino.getOrder()
							&& cages[i].getAnimals()[0].getEra() == saverDino.getEra())
						{
							std::cout << "You can choose " << i + 1 << " cage! It has got "
								<< cages[i].getAnimals().size() << " animals inside!\n";
							saveRightCage.push_back(i);
						}
					}
					else
					{
						std::cout << "Cage " << i + 1 << " is empty!\n";
						saveRightCage.push_back(i);
					}
				}
			}
			if (saveRightCage.size() != 0)
			{
				size_t number;
				std::cout << "You can choose from " << saveRightCage.size() << " cages!\n";
				std::cout << "The available cages are:\n";
				for (size_t t = 0; t < saveRightCage.size(); t++)
				{
					std::cout << "Cage " << saveRightCage[t] + 1 << ": " << cages[saveRightCage[t]];
				}
				do {
					std::cout << "Please choose a cage`number where you want to put the dinosaur:\n-> ";
					std::cin >> number;
					std::cin.ignore();
				} while (!isCorrect::isCorrectData(number, saveRightCage));
				cages[number - 1].setAnimal(saverDino);
				do {
					Employee helper;
					helper.appointment(std::cin, cages[number - 1]);//1ж. - 2 човека, 2ж. - 4 човека, 3ж. - 5 човека
					cages[number - 1].setCountEmp(cages[number - 1].getCountEmp() + 1);
					staff.push_back(helper);
				} while (!isCorrect::isCorrectCageEmployee(cages[number - 1]));
			}
			else
			{
				std::cout << "You should build new cage!\n";
				saverCage.buildCageForExistedAnimal(std::cin, saverDino);
				cages.push_back(saverCage);
				cages.back().setAnimal(saverDino);
				do {
					Employee helper;
					helper.appointment(std::cin, cages.back());//1ж. - 2 човека, 2ж. - 4 човека, 3ж. - 5 човека
					cages.back().setCountEmp(cages.back().getCountEmp() + 1);
					staff.push_back(helper);
				} while (!isCorrect::isCorrectCageEmployee(cages.back()));
			}
		}
		else if (action == 2)//2)Build new cage.
		{
			saverCage.buildCage(std::cin);
			cages.push_back(saverCage);
		}

		else if (action == 3)//3)Remove available animal.&& Remove staff
		{
			if (dinosaurs.size() == 0)
			{
				std::cout << "No animals available!";
			}
			else
			{
				size_t k;
				std::cout << "The available animals are " << dinosaurs.size() << '\n';
				for (size_t i = 0; i < dinosaurs.size(); i++)
				{
					std::cout << i + 1 << ")" << dinosaurs[i] << std::endl;
				}
				std::cout << "Please, select which animal to be removed:\n";
				do {
					std::cout << "->";
					std::cin >> k;
					std::cin.ignore();
				} while (!(k >= 1 && k <= dinosaurs.size()));
				for (size_t i = 0; i < cages.size(); i++)
				{
					for (size_t j = 0; j < cages[i].getAnimals().size(); j++)
					{
						if (dinosaurs[k - 1] == cages[i].getAnimals()[j])
						{
							cages[i].removeAnimalFromCage(j + 1); break;
						}
					}
				}
				dinosaurs.erase(dinosaurs.begin() + (k - 1));
				std::cout << "An animal was removed successfully!\n";
			}
		}
		else if (action == 4)
		{///Друг вариант е за да има със сигурност достатъчно храна за всички, да проверяваме от всеки вид 
		//колко животни има и да проверяваме дали е достатъчна храната.
			if (dinosaurs.size() != 0)
			{
				for (size_t i = 0; i < dinosaurs.size(); i++)
				{
					if (dinosaurs[i].getSpecies() == "Plesiosaur")
					{
						if (warehouse.getQuantityFish() > 15)
						{
							warehouse.setQuantityFish(warehouse.getQuantityFish() - 15);//15kg fish
							std::cout << "You fed dinosaur: " << dinosaurs[i] << " with 15kg fish\n";
						}
						else
						{
							std::cout << "There is not enough fish in warehouse!\nPlease, load the warehouse with fish!\n";
							warehouse.loadWarehouseWithFish();
						}
					}
					else if (dinosaurs[i].getSpecies() == "Brontosaurus")
					{
						if (warehouse.getQuantityMeat() > 20)
						{
							warehouse.setQuantityGrass(warehouse.getQuantityGrass() - 20);//20 kg grass
							std::cout << "You fed dinosaur: " << dinosaurs[i] << " with 20kg grass\n";
						}
						else
						{
							std::cout << "There is not enough grass in warehouse!\nPlease, load the warehouse with grass!\n";
							warehouse.loadWarehouseWithGrass();
						}
					}
					else if (dinosaurs[i].getSpecies() == "Tyrannosaur")
					{
						if (warehouse.getQuantityMeat() > 50)
						{
							warehouse.setQuantityMeat(warehouse.getQuantityMeat() - 50);//50 kg meat
							std::cout << "You fed dinosaur: " << dinosaurs[i] << " with 50kg meat\n";
						}
						else
						{
							std::cout << "There is not enough meat in warehouse!\nPlease, load the warehouse with meat!\n";
							warehouse.loadWarehouseWithMeat();
						}
					}
					else if (dinosaurs[i].getSpecies() == "Pterosaur")
					{
						if (warehouse.getQuantityMeat() > 35)
						{
							warehouse.setQuantityMeat(warehouse.getQuantityMeat() - 35);//35 kg meat
							std::cout << "You fed dinosaur: " << dinosaurs[i] << " with 35kg meat\n";
						}
						else
						{
							std::cout << "There is not enough meat in warehouse!\nPlease, load the warehouse with meat!\n";
							warehouse.loadWarehouseWithMeat();
						}
					}
				}
			}
			else
			{
				std::cout << "There aren`t any animals in the park!\n";
			}
		}
		else if (action == 5)//5)Load the warehouse with food.
		{
			warehouse.loadWarehouse();
			std::cout << "In the warehouse there are " << warehouse.getQuantityGrass() << "kg grass, "
				<< warehouse.getQuantityMeat() << "kg meat, "
				<< warehouse.getQuantityFish() << "kg fish.\n";
		}

	} while (action != 6);
	if (action == 6)
	{
		for (size_t i = 0; i < cages.size(); i++)
		{
			std::cout << "Cage:" << i + 1 << "--->" << cages[i];
		}
		std::cout << "\nWarehouse: " << warehouse;
		storeInBin(cages, warehouse);
	}
	
	return 0;
}