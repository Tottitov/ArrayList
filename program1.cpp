// Student: Tony Nguyen
// Student ID: U592R887
// Assignment: 1
// Updated: 08/13/16
// Inventory array list

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

class part { // main class
	public:
		int partnumber;
		string description;
		int quantity;
		double price;
		double total;
};

void printAllparts(part arr[], int count) // case 1
{	
	if (count == 0)
	{
		cout << "\nEmpty Inventory!" << endl;
		return;
	}
	else {
		for (int i = 0; i < count; i++) {
			cout << endl << left << setw(5) << arr[i].partnumber;
			cout << left << setw(20) << arr[i].description;
			cout << left << setw(8) << arr[i].quantity;
			cout << "$" << arr[i].price << endl;
		}
	}
}

void addPart(part arr[], int &count, string desc, int quantity, double price) // case 2
{
	cout << "\nEnter a new part description: ";
	getline(cin, desc);
	cout << "\nEnter new part quantity: ";
	cin >> quantity;
	cout << "\nEnter new part price: $";
	cin >> price;
	
	arr[count].partnumber = count + 1;
	arr[count].description = desc;
	arr[count].quantity = quantity;
	arr[count].price = price;
	arr[count].total = quantity * price;
	count++;
}

void modifyPart(part arr[], int &count, string desc, int quantity, double price) // case 3
{
	int newpart;
	cout << "\nEnter part to modify: ";
	cin >> newpart;
	
	if (newpart < count + 1) {
		cout << endl << left << setw(5) << arr[newpart - 1].partnumber;
		cout << left << setw(20) << arr[newpart - 1].description;
		cout << left << setw(8) << arr[newpart - 1].quantity;
		cout << "$" << arr[newpart - 1].price << endl;
	
		cout << "\nEnter modified item description: ";
		cin.ignore();
		getline(cin, desc);
		cout << "\nEnter modified item quantity: ";
		cin >> quantity;
		cout << "\nEnter modified price: $";
		cin >> price;
		
		arr[newpart - 1].description = desc;
		arr[newpart - 1].quantity = quantity;
		arr[newpart - 1].price = price;
		arr[newpart - 1].total = quantity * price;
	}
}

void printTotal(part arr[], int &count, double sum) // case 4
{
	for (int j = 0; j < count; j++) // prints total inventory list
		sum = sum + arr[j].total;
	cout << "\nTotal cost of inventory: $" << sum << endl;
}

void fileIOWrite(part arr[], int &count) // reads txt file to array
{
	std::fstream file("inventory.txt", std::ios::out); // reads txt file and adds to array
	if (file) {	
		for (int x = 0; x < count; x++) {
			file << left << setw(5) << arr[x].partnumber;
			file << left << setw(20) << arr[x].description;
			file << left << setw(8) << arr[x].quantity;
			file << "$" << arr[x].price << endl;
		}		
		cout<<"\nWriting file \"inventory.txt\" succeeded." << endl;
		file.close();
	}
	else {
		cout << "Error when writing file \"inventory.txt\"" << endl;
		file.close();
		cout << "\nProgram exited";
	}
}
	
void fileIORead(part arr[], int &count) // writes array to txt file
{
	std::fstream file("inventory.txt", std::ios::in);
	if (file) {
		int i = 0, partnumber = 0, quantity = 0;
		std::string description = "";
		float unitPrice = 0;
		// use a loop to keep reading file.
		// if reading file fails, the loop will end
		while(file >> partnumber && i < 100) {
			file.ignore();
			std::getline(file, description);
			file >> quantity;
			file >> unitPrice;	
			
			arr[i].partnumber = partnumber;
			arr[i].description = description;
			arr[i].quantity = quantity;
			arr[i].price = unitPrice;
			i++;
			count++;
		}
		cout<<"\nReading file \"inventory.txt\" succeeded.\n" << endl;
		file.close();
	}
	else {
		cout << "\nError when reading file \"inventory.txt\"" << endl;
		file.close();
	}
}

int main()
{
	part p;
	part arr[100]; // this is array to hold objects
	int count = 0, choice = 0, quantity = 0;
	double price = 0, sum = arr[count].total;// all my global variables
	string desc;
	
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);
	
	fileIORead(arr, count);
	
	while (cin.good() && choice <= 5)
	{
		cout << "\n----------------------------" << endl
			 << "1. Print parts\n"
			 << "2. Enter a new part\n"
			 << "3. Modify a part\n"
			 << "4. Print total\n"
			 << "5. Exit/save the program\n\n"
			 << "Enter your number of choice: ";
			
		cin >> choice;
		
		switch(choice){
			case 1:
				printAllparts(arr, count);
				break;
			case 2:
				cin.ignore();
				addPart(arr, count, desc, quantity, price);
				break;
			case 3:
				modifyPart(arr, count, desc, quantity, price);
				cin.ignore();
				break;
			case 4:
				cin.ignore();
				printTotal(arr, count, sum);
				break;
			case 5:
				cin.ignore();
				fileIOWrite(arr, count);
				return 0;
			default:
				cout << "\n\nInvalid choice!" << endl;
		}
	}
}

