#ifndef WAREHOUSE_H
#define WAREHOUSE_H
#include<string>

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

};






#endif
