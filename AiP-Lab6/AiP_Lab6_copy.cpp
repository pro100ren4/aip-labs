#include <iostream>
#include <math.h>

using namespace std;

int FindMaxNumOfZeroInLine(int **matrix, unsigned int lines, unsigned int columns);

int main()
{
	unsigned int lines = 0, columns = 0;
	cout << "Input number of lines: ";
	cin >> lines;
	cout << "Input number of columns: ";
	cin >> columns;
	
	int** matrix = new int *[lines]; // Выделение памяти
	for(int i = 0; i < columns; i++)
	{
		matrix[i] = new int[columns];
	}
	
	cout << "Input matrix values (int)" << endl; // Заполнение
	for(int i = 0; i < lines; i++)
	{
		for(int j = 0; j < columns; j++)
		{
			cout <<"matrix["<<i<<"]["<<j<<"]=";
			cin >> matrix[i][j];
		}
	}
	
	cout << FindMaxNumOfZeroInLine((int**)matrix, lines, columns) << endl;
	
	return 0;
}

int FindMaxNumOfZeroInLine(int **matrix, unsigned int lines, unsigned int columns)
{
	int maxZeroNum = 0, imaxZeroNum = 0, zeroCount;
	for (int i  = 0; i < lines; i++)
	{
		zeroCount = 0;
		
		for(int j = 0; j < columns; j++)
		{
			if( matrix[i][j] == 0)zeroCount++;
		}
		if(maxZeroNum<zeroCount)
		{
			imaxZeroNum = i;
			maxZeroNum = zeroCount;	
		}
	}
	return imaxZeroNum;
}

