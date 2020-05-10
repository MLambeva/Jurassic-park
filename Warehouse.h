#ifndef WAREHOUSE_H
#define WAREHOUSE_H

class Warehouse
{
private:
	int quantityGrass;
	int quantityMeat;
	int quantityFish;
public:
	Warehouse() = default;
	Warehouse(int quantityGrass, int quantityMeat, int quantityFish);

	int getQuantityGrass() const;
	int getQuantityMeat() const;
	int getQuantityFish() const;

	void setQuantityGrass(int quantityGrass);
	void setQuantityMeat(int quantityMeat);
	void setQuantityFish(int quantityFish);

	void loadWarehouseWithGrass();//��������� �� ������ � �����
	void loadWarehouseWithMeat();//��������� �� ������ � ����
	void loadWarehouseWithFish();//��������� �� ������ � ����

	void loadWarehouse();//��������� �� ������ � �����, ���� � ����

	friend std::ostream& operator<<(std::ostream& out, const Warehouse& other);

	void write(std::ofstream& out);//��������� �� ���������� �� ������ � ������� ����
	void read(std::ifstream& in);//������ �� ���������� �� ������ �� ������� ����
};






#endif
