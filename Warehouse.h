#ifndef WAREHOUSE_H
#define WAREHOUSE_H

class Warehouse
{
private:
	int quantityGrass = 300;
	int quantityMeat = 300;
	int quantityFish = 300;
public:
	Warehouse() = default;

	int getQuantityGrass() const;
	int getQuantityMeat() const;
	int getQuantityFish() const;

	void setQuantityGrass(int quantityGrass);
	void setQuantityMeat(int quantityMeat);
	void setQuantityFish(int quantityFish);

	void loadWarehouseWithGrass();//Зареждане на склада с трева
	void loadWarehouseWithMeat();//Зареждане на склада с месо
	void loadWarehouseWithFish();//Зареждане на склада с риба

	void loadWarehouse();//Зареждане на склада с трева, месо и риба

	friend std::ostream& operator<<(std::ostream& out, const Warehouse& other);

	void write(std::ofstream& out);//Записване на информация за склада в бинарен файл
	void read(std::ifstream& in);//Четене на информация за склада от бинарен файл
};






#endif
