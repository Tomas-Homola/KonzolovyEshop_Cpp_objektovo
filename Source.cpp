#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include "strUpr_strLwr.h" // funkcie pre prepisanie pismen nejakeho stringu na bud vsetky male alebo velke

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

	void changeID(int newID) { this->ID = newID; } // funkcia na zmenu ID produktu
	void changeName(string newName) { this->name = newName; } // funkcia na zmenu nazvu produktu
	void changeProducer(string newProducer) { this->producer = newProducer; } // funkcia na zmenu vyrobcu produktu
	void changeQuantity(int newQuantity) { this->quantity = newQuantity; } // funkcia na zmenu mnozstva na sklade
	void changePrice(double newPrice) { this->price = newPrice; } // funkcia na zmenu ceny produktu

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
	void removeFromBudget(double productPrice) { budget -= productPrice; } // pridanie penazi do rozpoctu
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
	cout << "Thank you for you visit" << endl;

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
	cout << "\nQuantity of selected product: " << produkty[ID - 1].getQuantity() << "x\n\nPrice for selected product: " << produkty[ID - 1].getPrice() << " EUR\n" << endl;
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
	if (foundProducts == NULL)
	{
		cout << "Nothing found" << endl;
	}
	else
	{
		cout << "Found products:" << endl;
		cout << setw(2) << "ID" << setw(17) << "Name" << setw(12) << "Producer" << endl; // vypis prveho riadku tabulky

		for (int i = 0; i < getNumOfFoundProducts(); i++)
		{
			cout << setw(2) << produkty[foundProducts[i] - 1].getID() << setw(17) << produkty[foundProducts[i] - 1].getName() << setw(12) << produkty[foundProducts[i] - 1].getProducer() << endl;
		}
	}
}
 
  //################################################################################//

int main()
{
	string name, surname; // meno a priezvisko zakaznika
	string searchedWord; // premenna na hladany vyraz
	
	double budget = 0.0; // rozpocet zakaznika
	int choice = 0; // premenna na zistenie volby
	int chosenID = 0; // premenna pre vybrane ID produktu
	int bought = 0; // premenna, ci zakaznik chce alebo nechce kupit vybrany produkt
	int* foundProducts = NULL; // smernik na pole najdenych produktov

	Produkt* allProducts = NULL;

	Eshop eshop("produkty.txt");
	
	if (!eshop.getProductsFromFile())
	{
		cout << "Data not found" << endl;
		exit(-1);
	}
	
	allProducts = eshop.returnProducts();
	
	cout << "Vitajte v eshope!\nZadajte Vase meno:" << endl;
	cin >> name;
	cout << "\nZadajte Vase priezvisko:" << endl;
	cin >> surname;
	cout << "\nZadajte Vas rozpocet:" << endl;
	cin >> budget;

	Zakaznik customer(name, surname, budget);
	customer.printCustomerInfo();

	do
	{
		do // kontrola pre spravne zadanu moznost 1, 2 alebo 3
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			
			cout << "\nChoose an option:\n1 -> search by name\n2 -> search by producer\n3 -> finish shopping" << endl;

			cin >> choice;
			if (choice == 1 || choice == 2 || choice == 3) // ak je spravne zadane, tak pokracuje dalej
				break;
			else // ak nie je, tak si to pyta znovu
			{
				cout << "\nChoose a correct option" << endl;
				continue;
			}
		} while (choice > 3 || choice < 1);

		if (choice == 1) // vyhladavanie podla mena produktu
		{
			cout << "Search by name:" << endl;
			cin >> searchedWord;

			foundProducts = eshop.searchByName(searchedWord); // funkcia na hladanie
			eshop.printFoundProducts(foundProducts); // vypisanie najdenych produktov

			cout << "Choose product by its ID" << endl;
			cin >> chosenID;

			do // kontrola pre spravne zadane ID, este to skusit prerobit tak, aby to kontrolovalo iba z ID najdenych produktov
			{
				if (chosenID < 1 || chosenID > eshop.getNumberOfProducts())
				{
					cout << "Choose a correct ID" << endl;
					cin.clear();
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					cin >> chosenID;
					continue;
				}
				else
					break;
			} while (chosenID < 1 || chosenID > eshop.getNumberOfProducts());

			if (allProducts[chosenID - 1].getQuantity() == 0) // ak nie je produkt na sklade, vymazu sa dealokuju sa najdene pordukty a ide sa naspat na zaciatok
			{
				cout << "Product is not available" << endl;
				delete[] foundProducts;
				continue;
			}
			else // ak je produkt na sklade, tak vypise o nom uz iba pocet kusov a cenu
				eshop.printQuantityAndPriceByID(chosenID);
			
			cout << "1 -> to buy selected product\n0 -> back to main page" << endl;
			cin >> bought;

			do // kontrola pre spravne zadanu moznost 1/0
			{
				if (bought > 1 || bought < 0)
				{
					cout << "Choose a correct option" << endl;
					cin.clear();
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					cin >> bought;
					continue;
				}
				else if (bought == 1 || bought == 0)
					break;
			} while (bought > 1 || bought < 0);

			if (bought == 1) // ak si chce zakaznik kupit produkt
			{
				if (customer.getBudget() >= allProducts[chosenID - 1].getPrice()) // kontrola pre dostatok penazi na kupu produktu
				{
					customer.buyProduct(chosenID); // ulozenie ID kupeneho produktu
					customer.removeFromBudget(allProducts[chosenID - 1].getPrice()); // odcitanie ceny produktu od rozpoctu zakaznika
					cout << "Product bought\nRemaining budget: " << customer.getBudget() << " EUR" << endl; // vypisanie zostavajuceho rozpoctu
				}
				else
					cout << "Not enough money to buy selected product" << endl;
			}

			delete[] foundProducts;

		}
		else if (choice == 2) // vyhladavanie podla nazvu vyrobcu produktu
		{
			cout << "Search by producer:" << endl;
			cin >> searchedWord;

			foundProducts = eshop.searchByProducer(searchedWord); // funkcia na hladanie
			eshop.printFoundProducts(foundProducts); // vypisanie najdenych produktov

			cout << "Choose product by its ID" << endl;
			cin >> chosenID;

			do // kontrola pre spravne zadane ID, este to skusit prerobit tak, aby to kontrolovalo iba z ID najdenych produktov
			{
				if (chosenID < 1 || chosenID > eshop.getNumberOfProducts())
				{
					cout << "Choose a correct ID" << endl;
					cin.clear();
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					cin >> chosenID;
					continue;
				}
				else
					break;
			} while (chosenID < 1 || chosenID > eshop.getNumberOfProducts());

			if (allProducts[chosenID - 1].getQuantity() == 0) // ak nie je produkt na sklade, vymazu sa dealokuju sa najdene pordukty a ide sa naspat na zaciatok
			{
				cout << "Product is not available" << endl;
				delete[] foundProducts;
				continue;
			}
			else // ak je produkt na sklade, tak vypise o nom uz iba pocet kusov a cenu
				eshop.printQuantityAndPriceByID(chosenID);

			cout << "1 -> to buy selected product\n0 -> back to main page" << endl;
			cin >> bought;

			do
			{
				if (bought > 1 || bought < 0)
				{
					cout << "Choose a correct option" << endl;
					cin.clear();
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					cin >> bought;
					continue;
				}
				else if (bought == 1 || bought == 0)
					break;
			} while (bought > 1 || bought < 0);

			if (bought == 1)
			{
				if (customer.getBudget() >= allProducts[chosenID - 1].getPrice())
				{
					customer.buyProduct(chosenID);
					customer.removeFromBudget(allProducts[chosenID - 1].getPrice());
					cout << "Product bought\nRemaining budget: " << customer.getBudget() << " EUR" << endl;
				}
				else
					cout << "Not enough money to buy selected product" << endl;
			}

			delete[] foundProducts;
		}
		else if (choice == 3) // ak chce zakaznik koniec nakupu, tak sa vyskoci von z cyklu a pokracuje dalej na vytvorenie blociku
			break;

	} while (true);
	
	cout << "\nEnd of shopping" << endl;

	if (!customer.createReceipt(allProducts))
	{
		cout << "Error with receipt creation" << endl;
		delete[] allProducts;
		exit(-1);
	}
	
	delete[] allProducts; // dealokacia pamate pre produkty

	return 0;
}


