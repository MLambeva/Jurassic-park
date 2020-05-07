#include"Dinosaurs.h"
#include"Cage.h"
#include"isCorrect.h"
#include"Warehouse.h"

int main()
{
	Warehouse warehouse(300, 300, 300);
	Cage first("small", "dry");
	Cage second("medium", "water");
	Cage third("large", "air");
	std::vector<Cage> cages = { first, second, third };
	
	std::vector<size_t> helper = { };
	std::vector<Dinosaurs> dino = { };
	Dinosaurs saverDino;
	Cage saverCage;
	size_t action;
	do
	{		
		helper.clear();
		std::cout << "\nWhat do you want to do?\n" 
			      << "1)Accept new animal.\n"
			      << "2)Build new cage.\n"
			      << "3)Remove available animal.\n"
			      << "4)Animal nutrition.\n"
			      << "5)Load the warehouse with food.\n"
			      << "6)Finalize your Jurassic Park!\n";
		
		do {
			std::cout << "->";
			std::cin >> action;
		} while (!(action >= 1 && action <= 6));

		if (action == 1)//1)Accept new animal.
		{
			helper.clear();
			saverDino.createAnimal(std::cin);
			dino.push_back(saverDino);
			for (size_t i = 0; i < cages.size(); i++)
			{
				if (isCorrectCageAnimal(cages[i], cages[i].getAnimals()) && isCorrectClimateAnimal(cages[i], saverDino))
				{
					if (cages[i].getAnimals().size() != 0 )
					{
						if (cages[i].getAnimals()[0].getOrder() == saverDino.getOrder()
							&& cages[i].getAnimals()[0].getEra() == saverDino.getEra())
						{
							std::cout << "You can choose " << i + 1 << " cage! It has got "
								<< cages[i].getAnimals().size() << " animals inside!\n";
							helper.push_back(i);
						}
					}
					else
					{
						std::cout << "Cage " << i + 1 << " is empty!\n";
						helper.push_back(i);
					}
				}
			}
			if (helper.size() != 0)
			{
			size_t number;
			std::cout << "You can choose from " << helper.size() << " cages!\n";
			std::cout << "The available cages are:\n";
			for (size_t t = 0; t < helper.size(); t++)
			{
				std::cout << "Cage " << helper[t] + 1 << ": " << cages[helper[t]] ;
			}	
				do {
					std::cout << "Please choose a cage`number where you want to put the dinosaur:\n-> ";
					std::cin >> number;
				} while (!(number >= 1 && number <= cages.size()));
				cages[number - 1].setAnimal(saverDino);
				//std::cout << cages[number - 1];
			}
			else
			{
				std::cout << "You should build new cage!\n";
				saverCage.buildCage(std::cin);
				cages.push_back(saverCage);
				cages.back().setAnimal(saverDino);

			}
		}
		else if (action == 2)//2)Build new cage.
		{
			saverCage.buildCage(std::cin);
			cages.push_back(saverCage);
		}

		else if (action == 3)//3)Remove available animal.
		{
			if (dino.size() == 0)
			{
				std::cout << "No animals available!";
			}
			else
			{
				size_t k;
				std::cout << "The available animals are " << dino.size() << '\n';
				for (size_t i = 0; i < dino.size(); i++)
				{
					std::cout << i + 1 << ")" << dino[i] << std::endl;
				}
				std::cout << "Please, select which animal to be removed:\n";
				do {
					std::cout << "->";
					std::cin >> k;
				} while (!(k >= 1 && k <= dino.size()));
				dino.erase(dino.begin() + (k - 1));
				std::cout << "An animal was removed successfully!\n";
			}
		}
		else if (action == 4)
		{///Друг вариант е за да има със сигурност достатъчно храна за всички, да проверяваме от всеки вид 
		//колко животни има и да проверяваме дали е достатъчна храната.
			if (dino.size() != 0)
			{
				for (size_t i = 0; i < dino.size(); i++)
				{
					if (dino[i].getSpecies() == "Plesiosaur")
					{
						if (warehouse.getQuantityFish() > 15)
						{
							warehouse.setQuantityFish(warehouse.getQuantityFish() - 15);//15kg fish
							std::cout << "You fed dinosaur: " << dino[i] << " with 15kg fish\n";
						}
						else
						{
							std::cout << "There is not enough fish in warehouse!\nPlease, load the warehouse with fish!\n";
							warehouse.loadWarehouseWithFish();
						}
					}
					else if (dino[i].getSpecies() == "Brontosaurus")
					{
						if (warehouse.getQuantityMeat() > 20)
						{
							warehouse.setQuantityGrass(warehouse.getQuantityGrass() - 20);//20 kg grass
							std::cout << "You fed dinosaur: " << dino[i] << " with 20kg grass\n";
						}
						else
						{
							std::cout << "There is not enough grass in warehouse!\nPlease, load the warehouse with grass!\n";
							warehouse.loadWarehouseWithGrass();
						}
					}
					else if (dino[i].getSpecies() == "Tyrannosaur")
					{
						if (warehouse.getQuantityMeat() > 50)
						{
							warehouse.setQuantityMeat(warehouse.getQuantityMeat() - 50);//50 kg meat
							std::cout << "You fed dinosaur: " << dino[i] << " with 50kg meat\n";
						}
						else
						{
							std::cout << "There is not enough meat in warehouse!\nPlease, load the warehouse with meat!\n";
							warehouse.loadWarehouseWithMeat();
						}
					}
					else if (dino[i].getSpecies() == "Pterosaur")
					{
						if (warehouse.getQuantityMeat() > 35)
						{
							warehouse.setQuantityMeat(warehouse.getQuantityMeat() - 35);//35 kg meat
							std::cout << "You fed dinosaur: " << dino[i] << " with 35kg meat\n";
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
			std::cout << "Cage:" << i+1 << "--->" << cages[i];
		}
	}

	return 0;
}