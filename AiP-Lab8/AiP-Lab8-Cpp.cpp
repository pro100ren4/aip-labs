#include <iostream>
#include <fstream>
#include <string.h>
#include <conio.h>
using namespace std;

const int len = 100;
int main()
{
	char file_name[100];
	cout << "1) A.txt\n2) B.txt\n3) C.txt" << endl;
	cout << "Please enter file name:";
	cin >> file_name;
	cout << "=====" << file_name << "=====" << endl;
	
	fstream fin(file_name, ios::in);
	int count = 0;
	char str[len];
	while(!fin.eof())
	{
		fin.getline(str, len);
		cout << str << endl;
		if(str[0] == ' ' && str[strlen(str) - 1] == ' ')
		{
			count++;
		}
	}
	cout << "==========\nNumber of string that srart and end with \'space\'-character: " << count << "\n==========";
	getch();
}