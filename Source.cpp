#include<iostream>
#include<fstream>		/*it can create files, write information to files, and read information from files, while the ofstream allows us to write only, and
						  the ifstream allows us to read only*/
using namespace std;

class shopping		//class is where we put all our functions used in the program.
{
private:		//access specifier | private, public and protected, users can't edit on the private section.
	int product_code;		//attribute of the class(int variable)
	float price, discount;	//attribute of the class(float variable)
	string product_name;	//attribute of the class(string variable)
public:
	void menu();		
	void manager();		
	void customer();		
	void add();			
	void edit();		
	void removeProduct();	
	void list();			
	void receipt();		
};

void shopping::menu()		//here we declare what we put in the menu function.
{
	tryAgain:		//we use this in case the user chooses an invalid sections of the 3 sections down below, it brings them back to the beginning.
	int selection;
	string email, password;

	cout << "\t\t\t\t________________________________\n";
	cout << "\t\t\t\t                                \n";
	cout << "\t\t\t		Super Market Menu		 \n";
	cout << "\t\t\t\t                                \n";
	cout << "\t\t\t\t________________________________\n";
	cout << "\t\t\t\t                                \n";
	cout << "\t\t\t\t\t|    1)Manager    |\n";
	cout << "\t\t\t\t\t|                 |\n";
	cout << "\t\t\t\t\t|    2)Customer   |\n";
	cout << "\t\t\t\t\t|                 |\n";
	cout << "\t\t\t\t\t|    3)Exit       |\n";
	cout << "\t\t\t\t\t|                 |\n";
	cin >> selection;

	switch (selection)
	{
	case 1:
		cout << "\t\t\t\a Email: ";
		cin >> email;
		cout << "\n\t\t\t\a Password: ";
		cin >> password;

		if (email == "omarhesham1337@gmail.com" && password == "123456789")
		{
			manager();		//it means if the email & password are correct, the person will go to manager function.
		}
		else 
		{
			cout << "\t\t\t\t\n\aInvalid Email/Password, Please Try Again !";
			goto tryAgain;		//if the email & password are incorrect, the person will move to the menu again.
		}
		break;

	case 2:
	{
		customer();
		break;
	}
	case 3:
	{
	exit(0);
	break;
	}
	default: {
		cout << "Invalid Selection !";
		break;
		goto tryAgain;
	}
	}
}

void shopping::manager()
{
tryAgain:
	int selection;
	cout << "\n\n\n\t\t\t\t  The Manager Menu\n";
	cout << "\n\t\t\t\t  |____1)Add A Product____|";
	cout << "\n\t\t\t\t  |                       |";
	cout << "\n\t\t\t\t  |___2)Modify A Product__|";
	cout << "\n\t\t\t\t  |                       |";
	cout << "\n\t\t\t\t  |___3)Delete A Product__|";
	cout << "\n\t\t\t\t  |                       |";
	cout << "\n\t\t\t\t  |__4)Back To Main Menu__|";

	cout << "\n\n\tSelection: ";
	cin >> selection;

	switch (selection)
	{
	case 1:
		add();
		break;

	case 2:
		edit();
		break;

	case 3:
		removeProduct();
		break;

	case 4:
		menu();
		break;

	default:
		cout << "Invalid Selection, Please Try Again !";
		goto tryAgain;
	}
}

void shopping::customer()
{
	tryAgain:
	int selection;
	
	cout << "\t\t\t Customer \n";
	cout << "\t\t\t ________     \n";
	cout << "                    \n";
	cout << "\t\t\t1) Buy A Product";
	cout << "                    \n";
	cout << "\t\t\t2) Go Back    \n";
	cout << "\t\t\tPress Your Selection: ";
	cin >> selection;

	switch (selection)
	{
	case 1:
		receipt();
		break;

	case 2:
		menu();

	default:
		cout << "Invalid Selection, Try Again !";
		goto tryAgain;
		break;
	}
}	

void shopping::add()
{
	tryAgain:
	fstream data;
	int productCode, token = 0;
	float productPrice = 0, productDiscount = 0;
	string productName;

	cout << "\n\n\t\t\t#Adding A New Product#";
	cout << "\n\n\tProduct Name: ";
	cin >> product_name;
	cout << "\n\n\tProduct Code: ";
	cin >> product_code;
	cout << "\n\n\tProduct Price: ";
	cin >> price;
	cout << "\n\n\tProduct Discount: ";
	cin >> discount;
				/*Now we need to store the information we entered in a file so we're gonna summon a file to store it using fstream data*/
	data.open("database.txt", ios::in);		//ios::in means open the file in reading mode, if out instead of in then open the file in writing mode

	if (!data)
	{
		data.open("database.txt", ios::app | ios::out);		// | means OR which means compiling the writing mode(out) and the apply mode(app)
		//ios::app		All output operations are performed at the end of the file, appending the content to the current content of the file.
		data << " " << product_code << " " << product_name << " " << price << " " << discount << "\n";
		data.close();		//we use this function to close the file after storing the info.
	}
	else
	{
		data >> productCode >> productName >> productPrice >> productDiscount;

		while (!data.eof())			//eof stands for end of file function
		{
			if (productCode == product_code)
			{
				token++;
			}
			data >> productCode >> productName >> productPrice >> productDiscount;
		}
		data.close();

		if (token == 1)
		{
			goto tryAgain;
		}
		else
		{
			data.open("database.txt", ios::app | ios::out);
			data << " " << product_name << " " << product_code << " " << price << " " << discount << "\n";
			data.close();
		}
	}
	cout << "\n\n\t\tChanges Saved Successfully !";
}

void shopping::edit()
{
	fstream data1, data2;
	int productKey, token = 0, productCode;
	float productPrice, productDiscount;
	string productName;

	cout << "\n\t\t\t#Modify A Product#";
	cout << "\n\t\t\tProduct Code: ";
	cin >> productKey;		//the code which entered by the manager

	data1.open("database.txt", ios::in);
	if (!data1)			//if the file doesn't exist
	{
		cout << "The File Doesnt Exist !";
	}
	else
	{
		data2.open("database1.txt", ios::app | ios::out);

		data1 >> product_code >> product_name >> price >> discount;
		while (!data1.eof())		//data still can be read from the data source
		{
			if (productKey == product_code)
			{
				cout << "\n\t\tProduct's New Code: ";
				cin >> productCode;
				cout << "\n\t\tProduct's New Name: ";
				cin >> productName;
				cout << "\n\t\tProduct's New Price: ";
				cin >> productPrice;
				cout << "\n\t\tProduct's New Discount: ";
				cin >> productDiscount;
				data2 << " " << productCode << " " << productName << " " << productPrice << " " << productDiscount << "\n";
				cout << "\n\n\t\tChanges Have Been Saved !";
				token++;
			}
			else
			{
				data2 << " " << product_code << " " << product_name << " " << price << " " << discount << "\n";
			}
			data1 >> product_code >> product_name >> price >> discount;

		}
		data1.close();
		data2.close();

		remove("database.txt");
		rename("database1.txt", "database.txt");

		if (token == 0)
		{
			cout << "\n\nChanges Not Saved, Sorry !";
		}
	}
}

void shopping::removeProduct()
{
	fstream data1, data2;
	int productKey, token = 0;

	cout << "\n\n\t#Removing A Product#";
	cout << "\n\n\tProduct Code: ";
	cin >> productKey;

	data1.open("database.txt", ios::in);

	if (!data1)
	{
		cout << "File Doesn't Exist !";
	}
	else
	{
		data2.open("database1.txt", ios::app | ios::out);
		data1 >> product_code >> product_name >> price >> discount;

		while (!data1.eof())
		{
			if (productKey == product_code)
			{
				cout << "\n\n\tProduct Removed Successfully !";
				token++; 
			}
			else
			{
				data2 << product_code << product_name << price << discount << "\n";
			}
			data1 >> product_code >> product_name >> price >> discount;
		}
		data1.close();
		data2.close();
		
		remove("database.txt");
		rename("database1.txt", "database.txt");

		if (token == 0)
		{
			cout << "\n\nChanges Not Found !";
		}
	}
}

void shopping::list()
{
	fstream data;
	data.open("database.txt", ios::in);
	cout << "\n\n___________________________________________\n";
	cout << "Product Number \t Product Name \t Product Price\n";
	cout << "\n\n___________________________________________\n";
	data >> product_code >> product_name >> price>>discount;
	while (!data.eof())
	{
		cout << product_code << "\t\t" << product_name << "\t\t" << price << "\n";
		data >> product_code >> product_name >> price >> discount;
	}
	data.close();
}

void shopping::receipt()
{
	fstream data;
	int arrC[100];			//array of codes
	int arrQ[100];			//array of quantity
	string selection;
	int counter = 0;
	float amount = 0, discount = 0, total = 0;		//dISCOUNT is typed like that to be different than the discount variable at the beginning.

	cout << "\n\n\t\t\t\t #Receipt#";
	data.open("database.txt", ios::in);
	if (!data)
	{
		cout << "\n\n\tEmpty DataBase File.";
	}
	else
	{
		data.close();

		list();
		cout << "___________________________________________\n";
		cout << "|                                         |\n";
		cout << "|             Please Order !              |\n";
		cout << "|_________________________________________|\n";
		do
		{
			tryAgain:
			cout << "\n\nEnter The Product Code: ";
			cin >> arrC[counter];
			cout << "\n\nEnter The Quantity Needed: ";
			cin >> arrQ[counter];
			for (int i = 0;i < counter;i++)
			{
				if (arrC[counter] == arrC[i])
				{
					cout << "\n\n The Code Is Already Existed, Please Try Again !";
					goto tryAgain;
				}
			}
			counter++;
			cout << "\n\n Do You Want To Buy Another Product ?\tIF You Want Then Press yes\tIf Not Press no";
			cin >> selection;
		} while (selection == "yes");
		cout << "\n\n\t\t\t________________#Receipt#________________";
		cout << "\nProduct Number\tProduct Name\tProduct Quantity\tProduct Price\tProduct Amount\tDiscount On Amount";

		for (int i = 0;i < counter;i++)
		{
			data.open("database.txt", ios::in);
		data >> product_code >> product_name >> price >> discount;

		while (!data.eof())
			{
			if (product_code == arrC[i])
				{
				amount = price * arrQ[i];
				discount = amount - (amount * discount / 100);
				total = total + discount;
				cout << "\n" << product_code << "\t\t" << product_name << "\t\t" << arrQ[i] << "\t\t" << price << "\t\t" << amount << "\t\t" << discount;
				}
			data >> product_code >> product_name >> price >> discount;
			}
		}
		data.close();
	}
	cout << "\n\n|__________________________________________________|";
	cout << "\n Total Amount: " << total;
}

int main()
{
	shopping s;
	s.menu();
	
	system("pause>0");
	return 0;
}