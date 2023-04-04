#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

struct bank_client
{
	int index=0;
	string name;
	string surname;

	string city;
	string street;
	int houseNumber=0;
	int flatNumber=0;
	
	void PrintInfo()
	{
		cout << index << '\t' << surname + " " + name ;cout.width(4);
		cout <<'\t'<< city+" "+street+" "<< houseNumber << "/" << flatNumber << endl;
	}
};

void FillArray(bank_client arr[], int size);
void PrintArray(bank_client arr[], int size);
void SortArray(bank_client arr[], int size);
int FindSameStreet(bank_client arr[], int size);
void OutResultOfSearch(bank_client arr[], int size);

int main()
{
	cout << "Enter client list size: ";
	int size = 0;
	cin >> size;
	bank_client *clientList = new bank_client[size];
	cout << "memory allocated." << endl;
	system("pause");
	system("cls");
	FillArray(clientList, size);
	
	bool run = true;
	while(run)
	{
		system("cls");
		cout << "==========" << endl;
		cout << "MENU" << endl;
		cout << "==========" << endl;
		cout << "1) Print client list" << endl; 
		cout << "2) Sort client list (flat)" << endl;
		cout << "3) Find number of clients with the same street but diffrent houses" << endl;
		cout << "4) Exit" << endl;
		cout << "==========" << endl;
		cout << "Enter the action: ";
		int action = 0;
		cin >> action;
		switch(action)
		{
			case 1:
				PrintArray(clientList, size);
				break;
			case 2:
				SortArray(clientList, size);
				cout << "List was sorted " << endl;
				break;
			case 3:
				OutResultOfSearch(clientList,size);
				break;
			case 4:
				run = false;
				break;
			default:
				cout << "Incorrect action." << endl;
				break;			
		}	
		system("pause");
	}
	
	delete[] clientList;
	clientList = NULL;
}

void FillArray(bank_client arr[], int size)
{
	cout << "Please fill client list (use English symbol)" << endl;
	for(int i = 0; i < size; i++)
	{
		cout << "==========" << endl;
		cout << "Enter index: ";
		cin >> arr[i].index;
		while (!cin)//проверка на корректность ввода 
		{
			cin.clear();
			cin.ignore();
				
			cout << "Enter correct value!" << endl;
			cout << "Enter index: ";
			cin >> arr[i].index;
		}
		cout << "==========" << endl;
		cout << "Enter surname: ";
		cin >> arr[i].surname;
		cout << "Enter name: ";
		cin >> arr[i].name;
		cout << "==========" << endl;
		cout << "Enter city: ";
		cin >> arr[i].city;
		cout << "Enter street: ";
		cin >> arr[i].street;
		cout << "Enter house number: ";
		cin >> arr[i].houseNumber;
		while (!cin)//проверка на корректность ввода 
		{
			cin.clear();
			cin.ignore();
				
			cout << "Enter correct value!" << endl;
			cout << "Enter house number: ";
			cin >> arr[i].houseNumber;
		}
		cout << "Enter flat number: ";
		cin >> arr[i].flatNumber;
		while (!cin)//проверка на корректность ввода 
		{
			cin.clear();
			cin.ignore();
				
			cout << "Enter correct value!" << endl;
			cout << "Enter flat number: ";
			cin >> arr[i].flatNumber;
		}
		cout << "==========" << endl;
		cout << endl;
	}
}

void PrintArray(bank_client arr[], int size)
{
	cout << "Index\tFull name";
	cout.width(16);
	cout<<"\tAddress"<<endl;
	cout<<"=========================================================="<<endl;
	for(int i = 0; i < size; i++)
	{
		arr[i].PrintInfo();
	}
}

void SortArray(bank_client arr[], int size)
{
	
	int imin; bank_client temp;
	for(int i = 0; i < size; i++)
	{
		temp = arr[i];imin = i;
		for(int j = i + 1; j < size; j++)
		{
			if(temp.flatNumber > arr[j].flatNumber)
			{
				temp = arr[j];
				imin = j;
			}	
		}
		arr[imin] = arr[i];
		arr[i] = temp;
	}
}

void OutResultOfSearch(bank_client arr[], int size)
{
	int res = FindSameStreet(arr, size);
	if(res != 0)
	{
		cout << "Number of clients with the same street but diffrent houses: " << res << endl;
	}
	else
	{
		cout << "There are no clients satisfying the condition :(" << endl;
	}
}

int FindSameStreet(bank_client arr[], int size)
{
	bank_client temp;int imin;
	for(int i = 0; i < size; i++) // сортировка по street
	{	
		temp = arr[i]; imin = i;
		for(int j = i+1; j < size; j++)
		{
			if(temp.street > arr[j].street)
			{
				temp = arr[j];
				imin = j;
			}
		}
		arr[imin] = arr[i];
		arr[i] = temp;
	}
	
	int count = 0, tempCount; 
	string curStreet = "";
	for(int i = 0; i < size; i++)
	{
		if(arr[i].street != curStreet)
		{
			curStreet = arr[i].street;
			tempCount = 0;
			for(int j = i+1; j < size; j++)
			{
				if(arr[i].street == arr[j].street && arr[i].houseNumber != arr[j].houseNumber)
				{
					tempCount++;
				}	
			}
			if(tempCount != 0)
			{
				count += tempCount + 1;
			}	
		}
		else
		{
			continue;
		}
	}
	
	for(int i = 0; i < size; i++) // сортировка по index
	{	
		temp = arr[i]; imin = i;
		for(int j = i+1; j < size; j++)
		{
			if(temp.index > arr[j].index)
			{
				temp = arr[j];
				imin = j;
			}
		}
		arr[imin] = arr[i];
		arr[i] = temp;
	}
	
	return count;
}
		