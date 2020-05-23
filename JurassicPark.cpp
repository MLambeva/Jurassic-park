#include"JurassicPark.h"

JurassicPark::JurassicPark(std::vector<Cage> cages, Warehouse warehouse)
{
	this->cages = cages;
	this->warehouse = warehouse;
}

void JurassicPark::storeInBin()//��������� � ������� ����.
{
	std::ofstream outputFile("JurassicPark.bin", std::ios::out | std::ios::binary);//�������� ���� � ������� ����� �� �����.
	if (!outputFile.is_open())//����������� ���� � �������.
	{
		std::cout << "Error! The file cannot be opened!\n";
		return;
	}
	for (size_t i = 0; i < this->cages.size(); i++)
	{
		this->cages[i].write(outputFile);//��������� ������������ �� ����� ������.
	}
	this->warehouse.write(outputFile);//��������� ������������ �� ������.

	outputFile.close();//��������� �����.
}

void JurassicPark::readFromBin()//����� �� ������� ����.
{
	std::ifstream inputFile("JurassicPark.bin", std::ios::in | std::ios::binary | std::ios::ate);
	//�������� ���� � ������� ����� �� ������ ���� ��� �� �����������, �� ���������� �� ������ � ���� �� �����.
	if (!inputFile.is_open())//����������� ���� � �������.
	{
		std::cout << "Error! The file cannot be opened!\n";
		return;
	}
	std::streampos len = inputFile.tellg() - (std::streampos)12;
	//��������� ��������� �� ������������, ����� ������ �� �������� �� ��������, � �� � ����� �� (������ �������)-(3*sizeof(int)); 
	inputFile.seekg(0, std::ios::beg);//����������� ��������� �� ���� �������� �� �����.
	while (inputFile.tellg() != len)
	{
		//���� ����� �� �������������, �� �� �����, ������ ��������� ���������� ������� �� �������� ���� "len";
		Cage newCage;//��������� �� ��� ������ �����.
		newCage.read(inputFile);//����� ������������ �� ��������.
		this->cages.push_back(newCage);//�������� �������� ��� ������ �� ������.
	}
	this->warehouse.read(inputFile);//����� ������������ �� ������.

	inputFile.close();//��������� �����.
}

bool JurassicPark::isEmpty()//��������� ���� � ������� �������� ����� �� ������ � ���� ��� ������� � �����.
{
	//����� ������ ��� ������ �� �� ������ ��� � ������ � ���� ���� �� �������������, �� ������ �� �� �������� ������� ���������� ������.
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
	std::cout << "\nWarehouse: " << this->warehouse;
}

void JurassicPark::loadCages()//��� �������������� �� ���� ��� ��� ��������� �� ������,  �� �������� � ������� ���� ��� ���������� ��������� ������. 
{
	if (isEmpty())
	{
		/*��������� ������� � ������� ������ ��� ������� � ���,
		������ ��� ��� ��� ���� ����������� ����, ��� ��� � ������,
		��������� ���������� �� ���������� ������.*/
		Warehouse startWarehouse;
		Cage first("small", "dry");
		Cage second("medium", "water");
		Cage third("large", "air");
		std::vector<Cage>startCages = { first, second, third };
		JurassicPark start(startCages, startWarehouse);
		start.storeInBin();
	}
}

void JurassicPark::loadPark()
{
	loadCages();////��� �������������� �� ���� ��� ��� ��������� �� ������,  �� �������� � ������� ���� ��� ���������� ��������� ������. 

	std::vector<size_t> saveRightCage = { };//��������� ����� �� ������, � ����� ���� �� ���� �������� ����������.

	std::vector<Dinosaur> dinosaurs;//����������, � ����� �� ��������� ������� �� ����������� ��� ������ �� �����.
	Dinosaur saverDino;//������� ����� ��� ��������� �� ���������.
	Cage saverCage;//������� ����� ��� ��������� �� ������.

	size_t action;//����� �� ��������, ����� ���������� �� �������.

	(*this).readFromBin();//������ �� ����� � ��������� �� ������� �� �������� � ������.

	Dinosaur helper;//������� �����, ����� � ������.
	for (size_t i = 0; i < this->cages.size(); i++)//�����, �������� ������ ������.
	{
		for (size_t j = 0; j < this->cages[i].getAnimals().size(); j++)//�����, �������� ������ ������� � ������ ������.
		{
			if (this->cages[i].getAnimals()[j] != helper)
			{
				dinosaurs.push_back(this->cages[i].getAnimals()[j]);//� ����� ������ ��� ���������, �� ������� ��� ������ �� ���������.
			}
		}
	}
	/*�����, ����� ����������, ������ ������������ �� ������� �� �� ������� �������� 7,
	�.�. �� �� ���������� �������� ����� � �� �� ������� ������� � �������� ����.*/
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
			/*��� ����� ��������� �� ������  � �������� �� �������� 1, ������� ������ �� � ������,
			�� �� �� ������� ���������� ������ �� ��������, � ����� � �������� ����������� �� ���������.*/
			saverDino.createAnimal(std::cin);//��������� �������.
			dinosaurs.push_back(saverDino);//�������� ��������� ��� ������ �� ���������.
			for (size_t i = 0; i < this->cages.size(); i++)//�����, �������� ������ ������.
			{
				if (HelperFunctions::isCorrectCageAnimal(this->cages[i], this->cages[i].getAnimals()) &&
					HelperFunctions::isCorrectClimateAnimal(this->cages[i].getClimate(), saverDino))
					//�������� ���� ��� ����� � ������ ������ � ���� �������� � �������� �� ���������.
				{
					if (this->cages[i].getAnimals().size() != 0)
					{/*��� � �������� ��� �������, �� ����������� ���� �������� � ����� �� ���������, ����� ������ �� ��������,
					 ������� � ����� � ������� �� ������� ������� � ��������*/
						if (this->cages[i].getAnimals()[0].getOrder() == saverDino.getOrder()
							&& this->cages[i].getAnimals()[0].getEra() == saverDino.getEra())
						{
							std::cout << "You can choose " << i + 1 << " cage! It has got "
								<< this->cages[i].getAnimals().size() << " animals inside!\n";
							saveRightCage.push_back(i);
							//�������� ������ �� ��������, � ����� ���� �� ���� �������� �����������, ��� ��������� ���������.
						}
					}
					else//��� � �������� ���� �������.
					{
						std::cout << "Cage " << i + 1 << " is empty!\n";
						saveRightCage.push_back(i);
						//�������� ������ �� ��������, � ����� ���� �� ���� �������� �����������.
					}
				}
			}
			//����������� ���� ��� ������, � ����� ��� ���������� �� �����������.
			if (saveRightCage.size() != 0)
			{
				size_t number;//������� ����������, ���� ����� ��������� ������ �� ��������, � ����� ������ �� �������� ���������.
				std::cout << "You can choose from " << saveRightCage.size() << " cages!\n";
				std::cout << "The available cages are:\n";
				for (size_t t = 0; t < saveRightCage.size(); t++)
				{
					//��������� ���������� �� ���������� ������.
					std::cout << "Cage " << saveRightCage[t] + 1 << ": " << this->cages[saveRightCage[t]];
				}
				do {
					std::cout << "Please choose a cage`number where you want to put the dinosaur:\n-> ";
					std::cin >> number;//�������� ����� �� ������, ������ ������� �������� �����, �.�. �� � �� ������.
					std::cin.ignore();
				} while (!HelperFunctions::isCorrectData(number, saveRightCage));
				this->cages[number - 1].setAnimal(saverDino);//�������� ��������� � �������� � �������� �����.
				do {
					//����������� ���� �� ����������� ������ ���� �� ��������� � ��������, �.�. 1�. - 2 �., 2�. - 4 �., 3�. - 5 �.--->10�. - 12 �.
					this->cages[number - 1].setCountEmp(this->cages[number - 1].getCountEmp() + 1);
				} while (!HelperFunctions::isCorrectCageEmployee(this->cages[number - 1]));
			}
			else//��� ���� ������, ���������� �� ���������, �� ������ ���� ������.
			{
				std::cout << "You should build new cage!\n";
				saverCage.buildCageForExistedAnimal(std::cin, saverDino);
				//������ ������, ����� ������ �� ��� �������� ������ �� ���������.
				this->cages.push_back(saverCage);
				//�������� �������� ��� ������.
				this->cages.back().setAnimal(saverDino);
				//������� ��������� � ��������, ����� ��� ���������.
				do {
					//����������� ���� �� ����������� ������ ���� �� ��������� � ��������, �.�. 1�. - 2 �., 2�. - 4 �., 3�. - 5 �.--->10�. - 12 �.
					this->cages.back().setCountEmp(this->cages.back().getCountEmp() + 1);
				} while (!HelperFunctions::isCorrectCageEmployee(this->cages.back()));
			}
		}
		else if (action == 2)//2)Build new cage.
		{
			saverCage.buildCage(std::cin);//������ ������, � ����� ���� �� ��� ������� � ���������.
			this->cages.push_back(saverCage);//�������� �������� ��� ������.
		}

		else if (action == 3)//3)Remove available animal && reduce count of staff.
		{
			if (dinosaurs.size() == 0)
			{
				std::cout << "No animals available!";
			}
			else
			{
				size_t k;//������� ����������, �������� ��� ������� �� ���� ����������.
				std::cout << "The available animals are " << dinosaurs.size() << '\n';
				for (size_t i = 0; i < dinosaurs.size(); i++)
				{
					//��������� �� ������ ������� � ��������.
					std::cout << i + 1 << ")" << dinosaurs[i] << std::endl;
				}
				std::cout << "Please, select which animal to be removed:\n";
				do {
					//�������� ��� ������� �� ���� ����������.
					std::cout << "->";
					std::cin >> k;
					std::cin.ignore();
				} while (!(k >= 1 && k <= dinosaurs.size()));
				for (size_t i = 0; i < this->cages.size(); i++)//�����, �������� ������ ������.
				{
					for (size_t j = 0; j < this->cages[i].getAnimals().size(); j++)//�����, �������� ������ ������� � ������ ������.
					{
						if (dinosaurs[k - 1] == this->cages[i].getAnimals()[j])
						{
							//���������� ��������� � ����� "k" �� ��� ������� �������� �� ������ ������.
							//��� ������� ������, �� ����������, ����� � �������� ���������.
							this->cages[i].removeAnimalAndStaffFromCage(j + 1); break;
						}
					}
				}
				dinosaurs.erase(dinosaurs.begin() + (k - 1));//��������� ���������� �� ������� "k" �� ������.
				std::cout << "An animal was removed successfully!\n";
			}
		}
		else if (action == 4)//4)Feed dinosaurs.
		{
			//����������� ���� ��� ���������.
			if (dinosaurs.size() != 0)
			{
				for (size_t i = 0; i < dinosaurs.size(); i++)//��������� ������ �� ������ ���������.
				{
					//����� ��������� �� ����� � �������� ���������� �����.
					if (dinosaurs[i].getSpecies() == "Plesiosaur")//����������� - 15�� ����.
					{
						//�������� ���� ��� ���������� ����� � ������.
						if (this->warehouse.getQuantityFish() > 15)//��� ���, ������.
						{
							this->warehouse.setQuantityFish(this->warehouse.getQuantityFish() - 15);//�������� ������������ ���� � ������ � 15��.
							std::cout << "You fed dinosaur: " << dinosaurs[i] << " with 15kg fish\n";
						}
						else//��� ����, ��������� ������ � ����.
						{
							std::cout << "There is not enough fish in warehouse!\nPlease, load the warehouse with fish!\n";
							this->warehouse.loadWarehouseWithFish();
						}
					}
					else if (dinosaurs[i].getSpecies() == "Brontosaurus")//����������� - 20�� �����.
					{
						//�������� ���� ��� ���������� ����� � ������.
						if (this->warehouse.getQuantityMeat() > 20)//��� ���, ������.
						{
							this->warehouse.setQuantityGrass(this->warehouse.getQuantityGrass() - 20);//�������� ������������ ����� � ������ � 20��.
							std::cout << "You fed dinosaur: " << dinosaurs[i] << " with 20kg grass\n";
						}
						else // ��� ����, ��������� ������ � �����.
						{
							std::cout << "There is not enough grass in warehouse!\nPlease, load the warehouse with grass!\n";
							this->warehouse.loadWarehouseWithGrass();
						}
					}
					else if (dinosaurs[i].getSpecies() == "Tyrannosaur")//����������� - 50�� ����.
					{
						//�������� ���� ��� ���������� ����� � ������.
						if (this->warehouse.getQuantityMeat() > 50)//��� ���, ������.
						{
							this->warehouse.setQuantityMeat(this->warehouse.getQuantityMeat() - 50);//�������� ������������ ���� � ������ � 50��.
							std::cout << "You fed dinosaur: " << dinosaurs[i] << " with 50kg meat\n";
						}
						else// ��� ����, ��������� ������ � ����.
						{
							std::cout << "There is not enough meat in warehouse!\nPlease, load the warehouse with meat!\n";
							this->warehouse.loadWarehouseWithMeat();
						}
					}
					else if (dinosaurs[i].getSpecies() == "Pterosaur")//���������� - 35�� ����. 
					{
						//�������� ���� ��� ���������� ����� � ������.
						if (this->warehouse.getQuantityMeat() > 35)//��� ���, ������.
						{
							this->warehouse.setQuantityMeat(this->warehouse.getQuantityMeat() - 35);//�������� ������������ ���� � ������ � 35��.
							std::cout << "You fed dinosaur: " << dinosaurs[i] << " with 35kg meat\n";
						}
						else// ��� ����, ��������� ������ � ����.
						{
							std::cout << "There is not enough meat in warehouse!\nPlease, load the warehouse with meat!\n";
							this->warehouse.loadWarehouseWithMeat();
						}
					}
				}
			}
			else//��� ���� �������, ��������� ���������.
			{
				std::cout << "There aren`t any animals in the park!\n";
			}
		}
		else if (action == 5)//5)Load the warehouse with food.
		{
			this->warehouse.loadWarehouse();//��������� ������ � ����� ���� �����.
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
		(*this).storeInBin();//��������� ������������ � �������� ����.
	}

}

