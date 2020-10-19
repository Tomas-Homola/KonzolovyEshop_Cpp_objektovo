#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include "strUpr_strLwr.h"

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

	int getID() { return ID; } // funkcia na vratenie ID produktu
	string getName() { return name; } // funkcia na vratenie nazvu produktu
	string getProducer() { return producer; } // funkcia na vratenie vyrobcu produktu
	int getQuantity() { return quantity; } // funkcia na vratenie mnozstva na sklade
	double getPrice() { return price; } // funkcia na vratenie ceny produktu

	void changeID(int newID) { ID = newID; } // funkcia na zmenu ID produktu
	void changeName(string newName) { name = newName; } // funkcia na zmenu nazvu produktu
	void changeProducer(string newProducer) { producer = newProducer; } // funkcia na zmenu vyrobcu produktu
	void changeQuantity(int newQuantity) { quantity = newQuantity; } // funkcia na zmenu mnozstva na sklade
	void changePrice(double newPrice) { price = newPrice; } // funkcia na zmenu ceny produktu

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

//#################################################################################//

class Zakaznik
{
private:
	string name;
	string surname;
	double budget;
	int boughtProducts[25]; // skusit pouzit iba int array???
	int productCount; // pocet kupenych produktov

public:
	Zakaznik();
	Zakaznik(string name, string surname, double budget);

	string getName() { return name; } // funkcia na vratenie mena
	string getSurname() { return surname; } // funkcia na vratenie priezviska
	double getBudget() { return budget; } // funkcia na vratenie rozpoctu
	int* getProductByID(int ID) { return &boughtProducts[ID]; } // funkcia na vratenie adresy produktu z kosika

	bool createReceipt(Produkt* products); // funkcia na vytvorenie vystupneho suboru s vypisanim kupenych produktov

	void changeName(string newName) { name = newName; } // zmena mena
	void changeSurname(string newSurname) { surname = newSurname; } // zmena priezviska
	void addToBudget(double addedSum) { budget += addedSum; } // pridanie penazi do rozpoctu
	void buyProduct(int ID); // pridanie produktu do kosika
	void printCustomerInfo(); // vypisat info o zakaznikovi

};

Zakaznik::Zakaznik()
{
	this->name = "N/A";
	this->surname = "N/A";
	this->budget = 0.0;
	this->productCount = 0;
} // done // done

Zakaznik::Zakaznik(string name, string surname, double budget)
{
	this->name = name;
	this->surname = surname;
	this->budget = budget;
	this->productCount = 0;
} //done

bool Zakaznik::createReceipt(Produkt* products)
{
	fstream blocik;

	blocik.open("blocik_od_nakupu.txt", ios::out);
	if (!blocik.is_open())
	{
		cout << "Nepodarilo sa otvorit blocik" << endl;
		return false;
	}

	blocik << "Kupene produkty:\n";

	for (int i = 0; i < productCount; i++)
	{
		blocik << "1x " << products[boughtProducts[i] - 1].getName() << ", price: " << products[boughtProducts[i] - 1].getPrice() << " EUR" << endl;
	}

	blocik.close();
	cout << "Dakujeme za nakup" << endl;

	return true;
} // asi done

void Zakaznik::buyProduct(int ID)
{
	boughtProducts[productCount] = ID;
	
	productCount++;
}

void Zakaznik::printCustomerInfo()
{
	cout << "Meno a priezvisko zakaznika: " << getName() << " " << getSurname() << endl << "Budget: " << getBudget() << " EUR" << endl;
}

//################################################################################//

class Eshop
{
private:
	string getProductsFrom;
	int numberOfProducts;
	int numOfFoundProducts;
	Produkt* produkty;
public:
	Eshop(string filename) { this->getProductsFrom = filename; }
	bool getProductsFromFile();
	string getFileName() { return getProductsFrom; }
	int getNumberOfProducts() { return numberOfProducts; }
	int getNumOfFoundProducts() { return numOfFoundProducts; }

	int* searchByName(string searchedWord);
	int* searchByProducer(string searchedWord);
	Produkt* returnProducts() { return produkty; } // funkcia, co vrati adresu, kde su ulozene produkty

	void printQuantityAndPriceByID(int ID);
	void productBought(int ID);
	void changeNumberOfProducts(int newNumberOfProducts) { numberOfProducts = newNumberOfProducts; }
	void printAllProducts();
	void printFoundProducts(int* foundProducts);
	
	void changeNumOfFoundProducts(int newNum) { numOfFoundProducts = newNum; }
	void increaseNumOfFoundProducts(int increaseBy) { numOfFoundProducts += increaseBy; }
};

bool Eshop::getProductsFromFile()
{
	fstream fromFile;
	int tempInt = 0;
	double tempDouble = 0.0;
	string tempString;

	fromFile.open(getFileName(), ios::in);
	if (!fromFile.is_open())
		return false;
	
	fromFile >> tempInt;
	changeNumberOfProducts(tempInt);
	tempInt = 0;

	produkty = new Produkt[getNumberOfProducts()];

	for (int i = 0; i < getNumberOfProducts(); i++)
	{
		fromFile >> tempInt;
		produkty[i].changeID(tempInt);
		fromFile >> tempString;
		produkty[i].changeName(tempString);
		fromFile >> tempString;
		produkty[i].changeProducer(tempString);
		fromFile >> tempInt;
		produkty[i].changeQuantity(tempInt);
		fromFile >> tempDouble;
		produkty[i].changePrice(tempDouble);
	}

	fromFile.close();
	
	return true;
}

int* Eshop::searchByName(string searchedWord)
{
	// vratit to ma smernik na dynamicky alokovane pole, kde sa ulozia najdene produkty 
	int* foundProducts;
	foundProducts = new int[getNumberOfProducts()];

	changeNumOfFoundProducts(0);

	searchedWord = str_to_lwr(searchedWord); // zmena pismen zadaneho stringu na male pismena

	for (int i = 0; i < numberOfProducts; i++)
	{
		if (produkty[i].getName().find(searchedWord) != -1)
		{
			foundProducts[getNumOfFoundProducts()] = produkty[i].getID();
			increaseNumOfFoundProducts(1);
		}
	}

	if (getNumOfFoundProducts() == 0)
		return NULL;

	return foundProducts;
}

int* Eshop::searchByProducer(string searchedWord)
{
	// vratit to ma smernik na dynamicky alokovane pole, kde sa ulozia najdene produkty 
	int* foundProducts;
	foundProducts = new int[getNumberOfProducts()];
	
	changeNumOfFoundProducts(0);
	
	searchedWord = str_to_upr(searchedWord); // zmena pismen zadaneho stringu na male pismena

	for (int i = 0; i < numberOfProducts; i++)
	{
		if (produkty[i].getProducer().find(searchedWord) != -1)
		{
			foundProducts[getNumOfFoundProducts()] = produkty[i].getID();
			increaseNumOfFoundProducts(1);
		}
	}
	
	if ( getNumOfFoundProducts() == 0)
		return NULL;
	
	return foundProducts;
}

void Eshop::printQuantityAndPriceByID(int ID)
{
	cout << "Quantity of selected product: " << produkty[ID - 1].getQuantity() << ", Price for selected product: " << produkty[ID - 1].getPrice() << " EUR" << endl;
} // asi done

void Eshop::printAllProducts()
{
	cout << setw(2) << "ID" << setw(17) << "Name" << setw(12) << "Producer" << setw(12) << "Quantity" << setw(17) << "Price in EUR" << endl;
	
	for (int i = 0; i < getNumberOfProducts(); i++)
	{
		cout << setw(2) << produkty[i].getID() << setw(17) << produkty[i].getName() << setw(12) << produkty[i].getProducer() << setw(12) << produkty[i].getQuantity() << setw(17) << produkty[i].getPrice() << endl;
	}
} // asi done

void Eshop::productBought(int ID)
{
	produkty[ID - 1].changeQuantity(produkty[ID - 1].getQuantity() - 1);

	if (produkty[ID - 1].getQuantity() < 0)
		produkty[ID - 1].changeQuantity(0);
} // asi done

void Eshop::printFoundProducts(int* foundProducts)
{
	cout << "Found products:" << endl;
	cout << setw(2) << "ID" << setw(17) << "Name" << setw(12) << "Producer" << setw(12) << "Quantity" << setw(17) << "Price in EUR" << endl; // vypis prveho riadku tabulky

	for (int i = 0; i < getNumOfFoundProducts(); i++)
	{
		cout << setw(2) << produkty[foundProducts[i] - 1].getID() << setw(17) << produkty[foundProducts[i] - 1].getName() << setw(12) << produkty[foundProducts[i] - 1].getProducer() << setw(12) << produkty[foundProducts[i] - 1].getQuantity() << setw(17) << produkty[foundProducts[i] - 1].getPrice() << endl;
	}
}
 
  //################################################################################//

int main()
{
	string name = "Tomas";
	string surname = "Homola";
	double budget = 55.5;
	Produkt* produkty;
	int* foundProducts;
	string searchedWord;

	Zakaznik zakaznik(name, surname, budget);
	//zakaznik.printCustomerInfo();

	Eshop obchod("produkty.txt");
	obchod.getProductsFromFile();
	obchod.printAllProducts();
	produkty = obchod.returnProducts();

	cout << "Search by?" << endl;
	cin >> searchedWord;

	foundProducts = obchod.searchByProducer(searchedWord);
	
	cout << "\n\n";

	obchod.printFoundProducts(foundProducts);

	cout << "\n\n";

	cout << "Search by?" << endl;
	cin >> searchedWord;

	foundProducts = obchod.searchByName(searchedWord);

	cout << "\n\n";

	obchod.printFoundProducts(foundProducts);
	
	delete[] foundProducts;



	return 0;
}


