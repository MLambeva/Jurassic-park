#include"JurassicPark.h"

JurassicPark::JurassicPark(std::vector<Cage> cages, Warehouse warehouse)
{
	this->cages = cages;
	this->warehouse = warehouse;
}

void JurassicPark::storeInBin()//Записваме в бинарен файл.
{
	std::ofstream outputFile("JurassicPark.bin", std::ios::out | std::ios::binary);//Отваряме файл в бинарен режим за запис.
	if (!outputFile.is_open())//Проверяваме дали е отворен.
	{
		std::cout << "Error! The file cannot be opened!\n";
		return;
	}
	for (size_t i = 0; i < this->cages.size(); i++)
	{
		this->cages[i].write(outputFile);//Записваме информацията за всяка клетка.
	}
	this->warehouse.write(outputFile);//Записваме информацията за склада.

	outputFile.close();//Затваряме файла.
}

void JurassicPark::readFromBin()//Четем от бинарен файл.
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
		this->cages.push_back(newCage);//Добавяме клетката към масива от клетки.
	}
	this->warehouse.read(inputFile);//Четем информацията за склада.

	inputFile.close();//Затваряме файла.
}

bool JurassicPark::isEmpty()//Проверява дали е отворен коректно файла за четене и дали има животни в парка.
{
	//Връща истина ако файлът не се отваря или е празен и чрез това си подсигуряваме, че трябва да се създадат някакви произволни клетки.
	std::ifstream inputFile("JurassicPark.bin", std::ios::in | std::ios::binary | std::ios::ate);
	std::streampos len = inputFile.tellg();
	if (!inputFile.is_open() || len == 0) return true;
	else return false;
}

void JurassicPark::print() const
{
	for (size_t i = 0; i < this->cages.size(); i++)
	{
		std::cout << "Cage:" << i + 1 << "--->" << this->cages[i];
	}
	std::cout << "Warehouse: " << this->warehouse << '\n';
}

void JurassicPark::loadCages()//При несъществуване на файл или при неналичие на клетки,  се записват в бинарен файл три произволно измислени клетки. 
{
	if (isEmpty())
	{
		/*Зоопаркът започва с няколко клетки без животни в тях,
		затова ако все още няма съществуващ файл, или той е празен,
		записваме информация за произволно генерирани клетки.*/
		std::vector<Cage>startCages;
		Warehouse startWarehouse;
		std::srand(std::time(NULL));
		std::vector<std::string> sizes = { "small", "medium", "large" };
		std::vector<std::string> climate = { "dry", "water", "air" };
		for (size_t i = 0; i < 3; i++)
		{
			startCages.push_back(Cage(sizes[std::rand() % 3], climate[std::rand() % 3]));
		}
		JurassicPark start(startCages, startWarehouse);
		start.storeInBin();
	}
}

void JurassicPark::loadPark()
{
	loadCages();//При несъществуване на файл или при неналичие на клетки,  се записват в бинарен файл три произволно измислени клетки. 

	std::vector<size_t> saveRightCage = { };//Запазваме номер на клетка, в която може да бъде настанен динозавъра.

	std::vector<Dinosaur> dinosaurs;//Променлива, в която ще запазваме данните за динозаврите при четене от файла.
	Dinosaur saverDino;//Помощен обект при създаване на динозавър.
	Cage saverCage;//Помощен обект при създаване на клетка.

	size_t action;//Номер на действие, което програмата да изпълни.

	(*this).readFromBin();//Четене от файла и запазване на данните за клетките и склада.

	Dinosaur helper;//Помощен обект, който е празен.
	for (size_t i = 0; i < this->cages.size(); i++)//Цикъл, обхождащ всички клетки.
	{
		for (size_t j = 0; j < this->cages[i].getAnimals().size(); j++)//Цикъл, обхождащ всички животни в дадена клетка.
		{
			if (this->cages[i].getAnimals()[j] != helper)
			{
				dinosaurs.push_back(this->cages[i].getAnimals()[j]);//В която клетка има динозаври, се добавят към масива от динозаври.
			}
		}
	}
	/*Цикъл, който продължава, докато потребителят не натисне да се изпълни действие 7,
	т.е. да се финализира Джурасик парка и да се запазят данните в бинарния файл.*/
	do
	{
		std::cout << "\nWhat do you want to do?\n"
			<< "1)Accept new animal.\n"
			<< "2)Build new cage.\n"
			<< "3)Remove available animal.\n"
			<< "4)Feed dinosaurs.\n"
			<< "5)Load the warehouse with food.\n"
			<< "6)See information about current Jurassic park.\n"
			<< "7)Finalize your Jurassic Park!\n";

		do {
			std::cout << "->";
			std::cin >> action;
			std::cin.ignore();
		} while (!(action >= 1 && action <= 7));

		if (action == 1)//1)Accept new animal.
		{
			saveRightCage.clear();
			/*При всяко завъртане на цикъла  и избиране на действие 1, масивът трябва да е празен,
			за да се запазят правилните номера за клетките, в които е възможно настаняване на животното.*/
			saverDino.createAnimal(std::cin);//Създаваме животно.
			dinosaurs.push_back(saverDino);//Добавяме животното към масива от динозаври.
			for (size_t i = 0; i < this->cages.size(); i++)//Цикъл, обхождащ всички клетки.
			{
				if (HelperFunctions::isCorrectCageAnimal(this->cages[i], this->cages[i].getAnimals()) &&
					HelperFunctions::isCorrectClimateAnimal(this->cages[i].getClimate(), saverDino))
					//Проверка дали има място в дадена клетка и дали климатът е подходящ за животното.
				{
					if (this->cages[i].getAnimals().size() != 0)
					{/*Ако в клетката има животни, то проверяваме дали разредът и ерата на животното, което искаме да настаним,
					 съвпада с ерата и разреда на първото животно в клетката*/
						if (this->cages[i].getAnimals()[0].getOrder() == saverDino.getOrder()
							&& this->cages[i].getAnimals()[0].getEra() == saverDino.getEra())
						{
							std::cout << "You can choose " << i + 1 << " cage! It has got "
								<< this->cages[i].getAnimals().size() << " animals inside!\n";
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
					std::cout << "Cage " << saveRightCage[t] + 1 << ": " << this->cages[saveRightCage[t]];
				}
				do {
					std::cout << "Please choose a cage`number where you want to put the dinosaur:\n-> ";
					std::cin >> number;//Избираме номер на клетка, докато въведем коректен номер, т.е. да е от масива.
					std::cin.ignore();
				} while (!HelperFunctions::isCorrectData(number, saveRightCage));
				this->cages[number - 1].setAnimal(saverDino);//Добавяме животното в клетката с избрания номер.
				do {
					//Увеличаваме броя на служителите според броя на животните в клетката, т.е. 1ж. - 2 ч., 2ж. - 4 ч., 3ж. - 5 ч.--->10ж. - 12 ч.
					this->cages[number - 1].setCountEmp(this->cages[number - 1].getCountEmp() + 1);
				} while (!HelperFunctions::isCorrectCageEmployee(this->cages[number - 1]));
			}
			else//Ако няма клетки, отговарящи на условията, то строим нова клетка.
			{
				std::cout << "You should build new cage!\n";
				saverCage.buildCageForExistedAnimal(std::cin, saverDino);
				//Строим клетка, която трябва да има подходящ климат за животното.
				this->cages.push_back(saverCage);
				//Добавяме клетката към масива.
				this->cages.back().setAnimal(saverDino);
				//Слагаме животното в клетката, която сме построили.
				do {
					//Увеличаваме броя на служителите според броя на животните в клетката, т.е. 1ж. - 2 ч., 2ж. - 4 ч., 3ж. - 5 ч.--->10ж. - 12 ч.
					this->cages.back().setCountEmp(this->cages.back().getCountEmp() + 1);
				} while (!HelperFunctions::isCorrectCageEmployee(this->cages.back()));
			}
		}
		else if (action == 2)//2)Build new cage.
		{
			saverCage.buildCage(std::cin);//Строим клетка, в която няма да има животни и служители.
			this->cages.push_back(saverCage);//Добавяме клетката към масива.
		}

		else if (action == 3)//3)Remove available animal && reduce count of staff.
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
				for (size_t i = 0; i < this->cages.size(); i++)//Цикъл, обхождащ всички клетки.
				{
					for (size_t j = 0; j < this->cages[i].getAnimals().size(); j++)//Цикъл, обхождащ всички животни в дадена клетка.
					{
						if (dinosaurs[k - 1] == this->cages[i].getAnimals()[j])
						{
							//Сравняваме животното с номер "k" на кое животно отговаря от дадена клетка.
							//Ако открием такова, го премахваме, както и намаляме персонала.
							this->cages[i].removeAnimalAndStaffFromCage(j + 1); break;
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
						if (this->warehouse.getQuantityFish() > 15)//Ако има, храним.
						{
							this->warehouse.setQuantityFish(this->warehouse.getQuantityFish() - 15);//Намаляме количеството риба в склада с 15кг.
							std::cout << "You fed dinosaur: " << dinosaurs[i] << " with 15kg fish\n";
						}
						else//Ако няма, зареждаме склада с риба.
						{
							std::cout << "There is not enough fish in warehouse!\nPlease, load the warehouse with fish!\n";
							this->warehouse.loadWarehouseWithFish();
						}
					}
					else if (dinosaurs[i].getSpecies() == "Brontosaurus")//Бронтозавър - 20кг трева.
					{
						//Проверка дали има достатъчно храна в склада.
						if (this->warehouse.getQuantityMeat() > 20)//Ако има, храним.
						{
							this->warehouse.setQuantityGrass(this->warehouse.getQuantityGrass() - 20);//Намаляме количеството трева в склада с 20кг.
							std::cout << "You fed dinosaur: " << dinosaurs[i] << " with 20kg grass\n";
						}
						else // Ако няма, зареждаме склада с трева.
						{
							std::cout << "There is not enough grass in warehouse!\nPlease, load the warehouse with grass!\n";
							this->warehouse.loadWarehouseWithGrass();
						}
					}
					else if (dinosaurs[i].getSpecies() == "Tyrannosaur")//Тиранозавър - 50кг месо.
					{
						//Проверка дали има достатъчно храна в склада.
						if (this->warehouse.getQuantityMeat() > 50)//Ако има, храним.
						{
							this->warehouse.setQuantityMeat(this->warehouse.getQuantityMeat() - 50);//Намаляме количеството месо в склада с 50кг.
							std::cout << "You fed dinosaur: " << dinosaurs[i] << " with 50kg meat\n";
						}
						else// Ако няма, зареждаме склада с месо.
						{
							std::cout << "There is not enough meat in warehouse!\nPlease, load the warehouse with meat!\n";
							this->warehouse.loadWarehouseWithMeat();
						}
					}
					else if (dinosaurs[i].getSpecies() == "Pterosaur")//Птицезавър - 35кг месо. 
					{
						//Проверка дали има достатъчно храна в склада.
						if (this->warehouse.getQuantityMeat() > 35)//Ако има, храним.
						{
							this->warehouse.setQuantityMeat(this->warehouse.getQuantityMeat() - 35);//Намаляме количеството месо в склада с 35кг.
							std::cout << "You fed dinosaur: " << dinosaurs[i] << " with 35kg meat\n";
						}
						else// Ако няма, зареждаме склада с месо.
						{
							std::cout << "There is not enough meat in warehouse!\nPlease, load the warehouse with meat!\n";
							this->warehouse.loadWarehouseWithMeat();
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
			this->warehouse.loadWarehouse();//Зареждаме склада с трите вида храна.
			std::cout << "In the warehouse there are " << this->warehouse.getQuantityGrass() << "kg grass, "
				<< this->warehouse.getQuantityMeat() << "kg meat, "
				<< this->warehouse.getQuantityFish() << "kg fish.\n";
		}
		else if (action == 6)//6) See information about Jurassic park.
		{
		(*this).print();
		}

	} while (action != 7);
	if (action == 7)//6)Finalize your Jurassic Park!
	{
		(*this).print();
		(*this).storeInBin();//Записваме информацията в бинарния файл.
	}

}

