#include<iostream>
#include<fstream>
#include"Dinosaurs.h"
#include"Cage.h"
#include"isCorrect.h"
#include"Warehouse.h"

void storeInBin(std::vector<Cage> cages, Warehouse& warehouse)
{
	std::ofstream outputFile("JurassicPark.bin", std::ios::out | std::ios::binary);//Отваряме файл в бинарен режим за запис.
	if (!outputFile.is_open())//Проверяваме дали е отворен.
	{
		std::cout << "Error! The file cannot be opened!\n";
		return;
	}
	for (size_t i = 0; i < cages.size(); i++)
	{
		cages[i].write(outputFile);//Записваме информацията за всяка клетка.
	}
	warehouse.write(outputFile);//Записваме информацията за склада.

	outputFile.close();//Затваряме файла.
}

void readFromBin(std::vector<Cage>& cages, Warehouse& warehouse)
{
	std::ifstream inputFile("JurassicPark.bin", std::ios::in | std::ios::binary | std::ios::ate);
	//Отваряме файл в бинарен режим за четене като сме си подсигурили, че указателят се намира в края на файла.
	if (!inputFile.is_open())//Проверяваме дали е отворен.
	{
		std::cout << "Error! The file cannot be opened!\n";
		return;
	}
	std::streampos len = inputFile.tellg() - (std::streampos)12;
	//Запазваме дължината на информацията, която трябва да прочетем за клетката, а тя е равна на (общата дължина)-(3*sizeof(int)); 
	inputFile.seekg(0, std::ios::beg);//Преместваме указателя да сочи началото на файла.
	while (inputFile.tellg() != len)
	{
		//Чрез цикъл си подсигуряваме, че ще четем, докато достигнем запазената дължина на клетката чрез "len";
		Cage newCage;//Създаваме си нов празен обект.
		newCage.read(inputFile);//Четем информацията за клетката.
		cages.push_back(newCage);//Добавяме клетката към масива от клетки.
	}
	warehouse.read(inputFile);//Четем информацията за склада.

	inputFile.close();//Затваряме файла.
}

bool isEmpty()
{
	//Връща истина ако файлът не се отваря или е празен и чрез това си подсигуряваме, че трябва да се създадат някакви произволни клетки.
	std::ifstream inputFile("JurassicPark.bin", std::ios::in | std::ios::binary | std::ios::ate);
	std::streampos len = inputFile.tellg();
	if (!inputFile.is_open() || len == 0) return true;
	else return false;
}

int main()
{
	if (isEmpty())
	{
		/*Зоопаркът започва с няколко клетки без животни в тях, 
		затова ако все още няма съществуващ файл, или той е празен,
		записваме информация за произволни клетки.*/
		Warehouse startWarehouse(300, 300, 300);
		Cage first("small", "dry", 0);
		Cage second("medium", "water", 0);
		Cage third("large", "air", 0);
		std::vector<Cage>startCages = { first, second, third };
		storeInBin(startCages, startWarehouse);
	}

	Warehouse warehouse;//Обект, в който ще запазваме данните за склада при четене от файла.
	std::vector<Cage> cages = { };//Променлива, в която ще запазваме данните за клетките при четене от файла.
	std::vector<Dinosaurs> dinosaurs = { };//Променлива, в която ще запазваме данните за динозаврите при четене от файла.

	std::vector<size_t> saveRightCage = { };//Запазваме номер на клетка, в която може да бъде настанен динозавъра.
	
	Dinosaurs saverDino;//Помощен обект при създаване на динозавър.
	Cage saverCage;//Помощен обект при създаване на клетка.

	size_t action;//Номер на действие, което програмата да изпълни.

	readFromBin(cages, warehouse);//Четене от файла и запазване на данните за клетките и склада.

	Dinosaurs helper;//Помощен обект, който е празен.
	for(size_t i = 0; i < cages.size(); i++)//Цикъл, обхождащ всички клетки.
	{
		for (size_t j = 0; j < cages[i].getAnimals().size(); j++)//Цикъл, обхождащ всички животни в дадена клетка.
		{
			if (cages[i].getAnimals()[j] != helper)
			{
				dinosaurs.push_back(cages[i].getAnimals()[j]);//В която клетка има динозаври, се добавят към масива от динозаври.
			}
		}
	}
	/*Цикъл, който продължава, докато потребителят не натисне да се изпълни действие 6, 
	т.е. да се финализира Джурасик парка и да се запазят данните в бинарния файл.*/
	do
	{
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
			/*При всяко завъртане на цикъла  и избиране на действие 1, масивът трябва да е празен, 
			за да се запазят правилните номера за клетките, в които е възможно настаняване на животното.*/
			saverDino.createAnimal(std::cin);//Създаваме животно.
			dinosaurs.push_back(saverDino);//Добавяме животното към масива от динозаври.
			for (size_t i = 0; i < cages.size(); i++)//Цикъл, обхождащ всички клетки.
			{
				if (isCorrect::isCorrectCageAnimal(cages[i], cages[i].getAnimals()) && 
					isCorrect::isCorrectClimateAnimal(cages[i].getClimate(), saverDino))
					//Проверка дали има място в дадена клетка и дали климатът е подходящ за животното.
				{
					if (cages[i].getAnimals().size() != 0)
					{/*Ако в клетката има животни, то проверяваме дали разредът и ерата на животното, което искаме да настаним,
					 съвпада с ерата и разреда на първото животно в клетката*/
						if (cages[i].getAnimals()[0].getOrder() == saverDino.getOrder()
							&& cages[i].getAnimals()[0].getEra() == saverDino.getEra())
						{
							std::cout << "You can choose " << i + 1 << " cage! It has got "
								<< cages[i].getAnimals().size() << " animals inside!\n";
							saveRightCage.push_back(i);
							//Добавяме номера на клетката, в който може да бъде настанен динозавърът, ако изпълнява условията.
						}
					}
					else//Ако в клетката няма животни.
					{
						std::cout << "Cage " << i + 1 << " is empty!\n";
						saveRightCage.push_back(i);
						//Добавяме номера на клетката, в който може да бъде настанен динозавърът.
					}
				}
			}
			//Проверяваме дали има клетки, в които има възможност за настаняване.
			if (saveRightCage.size() != 0)
			{
				size_t number;//Помощна променлива, чрез която въвеждаме номера на клетката, в която искаме да настаним животното.
				std::cout << "You can choose from " << saveRightCage.size() << " cages!\n";
				std::cout << "The available cages are:\n";
				for (size_t t = 0; t < saveRightCage.size(); t++)
				{
					//Извеждаме информация за достъпните клетки.
					std::cout << "Cage " << saveRightCage[t] + 1 << ": " << cages[saveRightCage[t]];
				}
				do {
					std::cout << "Please choose a cage`number where you want to put the dinosaur:\n-> ";
					std::cin >> number;//Избираме номер на клетка, докато въведем коректен номер, т.е. да е от масива.
					std::cin.ignore();
				} while (!isCorrect::isCorrectData(number, saveRightCage));
				cages[number - 1].setAnimal(saverDino);//Добавяме животното в клетката с избрания номер.
				do {
					//Увеличаваме броя на служителите според броя на животните в клетката, т.е. 1ж. - 2 ч., 2ж. - 4 ч., 3ж. - 5 ч.--->10ж. - 12 ч.
					cages[number - 1].setCountEmp(cages[number - 1].getCountEmp() + 1);
				} while (!isCorrect::isCorrectCageEmployee(cages[number - 1]));
			}
			else//Ако няма клетки, отговарящи на условията, то строим нова клетка.
			{
				std::cout << "You should build new cage!\n";
				saverCage.buildCageForExistedAnimal(std::cin, saverDino);
				//Строим клетка, която трябва да има подходящ климат за животното.
				cages.push_back(saverCage);
				//Добавяме клетката към масива.
				cages.back().setAnimal(saverDino);
				//Слагаме животното в клетката, която сме построили.
				do {
					//Увеличаваме броя на служителите според броя на животните в клетката, т.е. 1ж. - 2 ч., 2ж. - 4 ч., 3ж. - 5 ч.--->10ж. - 12 ч.
					cages.back().setCountEmp(cages.back().getCountEmp() + 1);
				} while (!isCorrect::isCorrectCageEmployee(cages.back()));
			}
		}
		else if (action == 2)//2)Build new cage.
		{
			saverCage.buildCage(std::cin);//Строим клетка, в която няма да има животни и служители.
			cages.push_back(saverCage);//Добавяме клетката към масива.
		}

		else if (action == 3)//3)Remove available animal && remove count of staff.
		{
			if (dinosaurs.size() == 0)
			{
				std::cout << "No animals available!";
			}
			else
			{
				size_t k;//Помощна променлива, указваща кое животно да бъде премахнато.
				std::cout << "The available animals are " << dinosaurs.size() << '\n';
				for (size_t i = 0; i < dinosaurs.size(); i++)
				{
					//Извеждане на всички животни в зоопарка.
					std::cout << i + 1 << ")" << dinosaurs[i] << std::endl;
				}
				std::cout << "Please, select which animal to be removed:\n";
				do {
					//Избираме кое животно да бъде премахнато.
					std::cout << "->";
					std::cin >> k;
					std::cin.ignore();
				} while (!(k >= 1 && k <= dinosaurs.size()));
				for (size_t i = 0; i < cages.size(); i++)//Цикъл, обхождащ всички клетки.
				{
					for (size_t j = 0; j < cages[i].getAnimals().size(); j++)//Цикъл, обхождащ всички животни в дадена клетка.
					{
						if (dinosaurs[k - 1] == cages[i].getAnimals()[j])
						{
							//Сравняваме животното с номер "k" на кое животно отговаря от дадена клетка.
							//Ако открием такова, го премахваме, както и намаляме персонала.
							cages[i].removeAnimalAndStaffFromCage(j + 1); break;
						}
					}
				}
				dinosaurs.erase(dinosaurs.begin() + (k - 1));//Изтриваме динозавъра на позиция "k" от масива.
				std::cout << "An animal was removed successfully!\n";
			}
		}
		else if (action == 4)//4)Feed dinosaurs.
		{
		//Проверяваме дали има динозаври.
			if (dinosaurs.size() != 0)
			{
				for (size_t i = 0; i < dinosaurs.size(); i++)//Обхождаме масива от всички динозаври.
				{
					//Всеки динозавър се храни с различно количество храна.
					if (dinosaurs[i].getSpecies() == "Plesiosaur")//Плезиозавър - 15кг риба.
					{
						//Проверка дали има достатъчно храна в склада.
						if (warehouse.getQuantityFish() > 15)//Ако има, храним.
						{
							warehouse.setQuantityFish(warehouse.getQuantityFish() - 15);//Намаляме количеството риба в склада с 15кг.
							std::cout << "You fed dinosaur: " << dinosaurs[i] << " with 15kg fish\n";
						}
						else//Ако няма, зареждаме склада с риба.
						{
							std::cout << "There is not enough fish in warehouse!\nPlease, load the warehouse with fish!\n";
							warehouse.loadWarehouseWithFish();
						}
					}
					else if (dinosaurs[i].getSpecies() == "Brontosaurus")//Бронтозавър - 20кг трева.
					{
						//Проверка дали има достатъчно храна в склада.
						if (warehouse.getQuantityMeat() > 20)//Ако има, храним.
						{
							warehouse.setQuantityGrass(warehouse.getQuantityGrass() - 20);//Намаляме количеството трева в склада с 20кг.
							std::cout << "You fed dinosaur: " << dinosaurs[i] << " with 20kg grass\n";
						}
						else // Ако няма, зареждаме склада с трева.
						{
							std::cout << "There is not enough grass in warehouse!\nPlease, load the warehouse with grass!\n";
							warehouse.loadWarehouseWithGrass();
						}
					}
					else if (dinosaurs[i].getSpecies() == "Tyrannosaur")//Тиранозавър - 50кг месо.
					{
						//Проверка дали има достатъчно храна в склада.
						if (warehouse.getQuantityMeat() > 50)//Ако има, храним.
						{
							warehouse.setQuantityMeat(warehouse.getQuantityMeat() - 50);//Намаляме количеството месо в склада с 50кг.
							std::cout << "You fed dinosaur: " << dinosaurs[i] << " with 50kg meat\n";
						}
						else// Ако няма, зареждаме склада с месо.
						{
							std::cout << "There is not enough meat in warehouse!\nPlease, load the warehouse with meat!\n";
							warehouse.loadWarehouseWithMeat();
						}
					}
					else if (dinosaurs[i].getSpecies() == "Pterosaur")//Птицезавър - 35кг месо. 
					{
						//Проверка дали има достатъчно храна в склада.
						if (warehouse.getQuantityMeat() > 35)//Ако има, храним.
						{
							warehouse.setQuantityMeat(warehouse.getQuantityMeat() - 35);//Намаляме количеството месо в склада с 35кг.
							std::cout << "You fed dinosaur: " << dinosaurs[i] << " with 35kg meat\n";
						}
						else// Ако няма, зареждаме склада с месо.
						{
							std::cout << "There is not enough meat in warehouse!\nPlease, load the warehouse with meat!\n";
							warehouse.loadWarehouseWithMeat();
						}
					}
				}
			}
			else//Ако няма животни, извеждаме съобщение.
			{
				std::cout << "There aren`t any animals in the park!\n";
			}
		}
		else if (action == 5)//5)Load the warehouse with food.
		{
			warehouse.loadWarehouse();//Зареждаме склада с трите вида храна.
			std::cout << "In the warehouse there are " << warehouse.getQuantityGrass() << "kg grass, "
				<< warehouse.getQuantityMeat() << "kg meat, "
				<< warehouse.getQuantityFish() << "kg fish.\n";
		}

	} while (action != 6);
	if (action == 6)//6)Finalize your Jurassic Park!
	{
		for (size_t i = 0; i < cages.size(); i++)
		{
			std::cout << "Cage:" << i + 1 << "--->" << cages[i];
		}
		std::cout << "\nWarehouse: " << warehouse;
		storeInBin(cages, warehouse);//Записваме информацията в бинарния файл.
	}

	return 0;
}