#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

class Produkt
{
private:
	int ID;
	string name;
	string producer;
	int quantity;
	double price;
public:
	Produkt();
	Produkt(int ID, string name, string producer, int quantity, double price);

	int getID() { return ID; }
	string getName() { return name; }
	string getProducer() { return producer; }
	int getQuantity() { return quantity; }
	double getPrice() { return price; }

	void changeID(int newID) { ID = newID; }
	void changeName(string newName) { name = newName; }
	void changeProducer(string newProducer) { producer = newProducer; }
	void changeQuantity(int newQuantity) { quantity = newQuantity; }
	void changePrice(double newPrice) { price = newPrice; }
};

Produkt::Produkt()
{
	this->ID = -1;
	this->name = "N/A";
	this->producer = "N/A";
	this->quantity = -1;
	this->price = -1;
}

Produkt::Produkt(int ID, string name, string producer, int quantity, double price)
{
	this->ID = ID;
	this->name = name;
	this->producer = producer;
	this->quantity = quantity;
	this->price = price;
}

class Zakaznik
{
private:
	string name;
	string surname;
	double budget;
	Produkt bought_products[25]; // skusit pouzit iba int array???

public:
	Zakaznik();
	Zakaznik(string name, string surname, double budget);

	string getName() { return name; }
	string getSurname() { return surname; }
	double getBudget() { return budget; }
	Produkt getProductByID(int ID) { return bought_products[ID]; }

	bool createReceipt(string filename);

	void changeName(string newName) { name = newName; }
	void changeSurname(string newSurname) { surname = newSurname; }
	void addToBudget(double addedSum) { budget += addedSum; }

};

Zakaznik::Zakaznik()
{
	this->name = "N/A";
	this->surname = "N/A";
	this->budget = 0.0;
}

Zakaznik::Zakaznik(string name, string surname, double budget)
{
	this->name = name;
	this->surname = surname;
	this->budget = budget;
}

bool Zakaznik::createReceipt(string filename)
{
	return false;
}

class Eshop
{
private:
	Produkt* produkty;
	string getProductsFrom;
public:
	Eshop(string filename) { this->getProductsFrom = filename; }
	bool getProductsFromFile();

	Produkt* searchByName(string searchedWord);
	Produkt* searchByProducer(string searchedWord);

	void printInfo(int ID);
	void changeQuantityOfProduct(int ID);

};

bool Eshop::getProductsFromFile()
{

	return false;
}

Produkt* Eshop::searchByName(string searchedWord)
{

}

Produkt* Eshop::searchByProducer(string searchedWord)
{


}

void Eshop::printInfo(int ID)
{

}

void Eshop::changeQuantityOfProduct(int ID)
{

}


int main()
{
	string name = "Tomas";
	string surname = "Homola";
	double budget = 55.5;

	Zakaznik zakaznik;

	cout << "Meno a priezvisko zakaznika: " << zakaznik.getName() << " " << zakaznik.getSurname() << endl << "Budget: " << zakaznik.getBudget() << endl;



	return 0;
}


