#ifndef WAREHOUSE_H
#define WAREHOUSE_H
#include<string>
#include<fstream>

class Warehouse
{
private:
	int quantityGrass;
	int quantityMeat;
	int quantityFish;
	
public:
	Warehouse() = default;
	Warehouse(int quantityGrass, int quantityMeat, int quantityFish);
	int getQuantityGrass();
	int getQuantityMeat();
	int getQuantityFish();
	void setQuantityGrass(int quantityGrass);
	void setQuantityMeat(int quantityMeat);
	void setQuantityFish(int quantityFish);

	void loadWarehouseWithGrass();
	void loadWarehouseWithMeat();
	void loadWarehouseWithFish();
	void loadWarehouse();

	friend std::ostream& operator<<(std::ostream& out, const Warehouse& other);

	void write(std::ofstream& out);
	void read(std::ifstream& in);
};






#endif
