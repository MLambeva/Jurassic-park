#include"Dinosaurs.h"
#include"Cage.h"
#include"isCorrect.h"

int main()
{
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
		std::cout << "\nWhat do you want to do?\n";
		std::cout << "1)Accept new animal.\n2)Build new cage.\n";
		std::cout << "3)Remove available animal.\n4)Loads the warehouse with food.\n";
		std::cout << "5)Finishing the Jurassic Park!\n";
		std::cout << "Please, write 1, 2, 3, 4 or 5!\n";
		do {
			std::cin >> action;
		} while (!(action >= 1 && action <= 5));

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
					std::cout << "Please choose a cage`number where you want to put the dinosaur: ";
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
				std::cout << "Please, select which animal to be removed: ";
				do {
					std::cin >> k;
				} while (!(k >= 1 && k <= dino.size()));
				dino.erase(dino.begin() + (k - 1));
			}
		}

	} while (action != 5);
	if (action == 5)
	{
		for (size_t i = 0; i < cages.size(); i++)
		{
			std::cout << "Cage:" << i+1 << "--->" << cages[i];
		}
	}

	return 0;
}