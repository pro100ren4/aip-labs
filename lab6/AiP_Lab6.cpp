#include <conio.h>
#include <iostream>
#include <math.h>
#include <limits.h>
#include <stdlib.h>

using namespace std;

int** CreateMatrix(int **matrix, unsigned int lines, unsigned int columns);
int FindMaxNumOfZeroInLine(int **matrix, unsigned int lines, unsigned int columns);
void EnterMatrix(int **matrix, unsigned int lines, unsigned int columns);
void PrintMatrix(int **matrix, unsigned int lines, unsigned int columns);
int MinDiagonalModule(int **matrix, unsigned int lines, unsigned int columns);

int main()
{
	unsigned int lines = 0, columns = 0;
	
	cout << "Input number of lines and columns : ";
	cin >> lines >> columns;
	int **matrix = CreateMatrix(matrix, lines, columns);
	EnterMatrix(matrix, lines, columns);
	
	
	
	bool run = true;
	while(run)
	{	
		system("cls");
		cout << "================" << endl;
		cout << "MENU" << endl;
		cout << "================" << endl;
		cout << "1) Print matrix" << endl;
		cout << "2) Find index of line with max zero-elements in matrix" << endl;
		cout << "3) Find min sum of diagonale module" << endl;
		cout << "4) Exit" << endl;
		cout << "================" << endl;
		cout << "Enter the action: ";
		int i;
		cin >> i;
		
		switch(i)
		{
			case 1:
				PrintMatrix(matrix, lines, columns);
				break;
			case 2:
				cout << "index of line with max zero-elements in matrix: " << FindMaxNumOfZeroInLine(matrix, lines, columns) << endl;
				break;
			case 3:
				cout << "min sum of diagonale module: " << MinDiagonalModule(matrix, lines, columns) << endl;
				break;
			case 4: 
				run = false;
				break;
			default:
				cout << "invalid value. Please try again..." << endl;
				break;
		}
		cout << "Press <Enter>";
		getch();	
	}
	
	for(int i = 0; i < lines; i++)
	{
		delete []matrix[i];
	}
	delete []matrix;
	
	return 0;
}

int** CreateMatrix(int **matrix, unsigned int lines, unsigned int columns)
{
	int **arr = new int *[lines];
	for(int i = 0; i < lines; i++)
	{
		arr[i] = new int[columns];
	}
	return arr;
}

void EnterMatrix(int **matrix, unsigned int lines, unsigned int columns)
{
	cout << "Input matrix values (int)" << endl; // Заполнение
	for(int i = 0; i < lines; i++)
	{
		for(int j = 0; j < columns; j++)
		{
			cout <<"matrix["<<i<<"]["<<j<<"]=";
			cin >> matrix[i][j];
		}
	}
}

void PrintMatrix(int **matrix, unsigned int lines, unsigned int columns)
{	
	cout << "Matrix:" << endl;
	for(int i = 0; i < lines; i++)
	{	
		for(int j = 0; j < columns; j++)
		{
			cout << matrix[i][j] << '\t';
		}
		cout << endl;
	}
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

int MinDiagonalModule(int **matrix, unsigned int lines, unsigned int columns)
{
	int  temp = 0, min = INT_MAX;
	
	
	if(lines < columns) // Горизонтальная матрица
	{
		for(int k = 2; k <= lines; k++)// правый угол
		{
			temp = 0;
			for(int i = 0 , j = lines - k; i < lines & j >=0; i++, j-- )
			{
				temp += fabs(matrix[i][j]);	
			}
			if(temp < min)
			{
				min = temp;
			}
		}
		
		int l = columns - 1 - ( lines + 1 );// середина
		for(int k = 0; k <= l; k++)
		{
			temp = 0;
			for(int i = 0, j = lines + k; i < lines, j >= k + 1; i++, j--)
			{
				temp += fabs(matrix[i][j]);
			}
			if(temp < min)
			{
				min = temp;
			}
		}
		
		for(int k = 0; k < lines; k++)// левый угол
		{
			temp = 0;
			for(int i = k , j = columns -1 ; i < lines & j >=0; i++, j-- )
			{
				temp += fabs(matrix[i][j]);		
			}
			if(temp < min)
			{
				min = temp;
			}
		}
	}
	else if (lines > columns) // вертикальная матрица
	{
		for(int k = 2; k <= columns; k++)// верхний угол
		{
			temp = 0;
			for(int i = 0 , j = columns - k; i < columns & j >=0; i++, j-- )
			{
				temp += fabs(matrix[i][j]);	
			}
			if(temp < min)
			{
				min = temp;
			}
		}
		
		for(int k = 1; k < lines-3; k++)// середина
		{
			temp = 0;
			for(int i = k, j = columns - 1; i < lines-3, j >= 0; i++, j--)
			{
				temp += fabs(matrix[i][j]);
			}
			if(temp < min)
			{
				min = temp;
			}
		}
		
		for( int k = 3; k > 0 ; k--)// нижний угол
		{
			temp = 0;
			for(int i = lines - k, j = columns - 1; i < lines && j >= 0; i++, j--)
			{
				temp += fabs(matrix[i][j]);
			}
			if(temp < min)
			{
				min = temp;
			}
		}
	}
	else // квадратная матрица
	{	
		for(int k = 2; k <= lines; k++)//верхне-правый угол
		{
			temp = 0;
			for(int i = 0, j = lines - k; i < lines && j >= 0; i++, j-- )
			{
				temp += fabs(matrix[i][j]);
			}
			if(temp < min)
			{
				min = temp;
			}	
		}
		
		for(int k = 1; k < lines; k++)// нижне-левый угол
		{
			temp = 0;
			for(int i = k , j = columns -1 ; i < lines & j >=0; i++, j-- )
			{
				temp += fabs(matrix[i][j]);	
			}
			if(temp < min)
			{
				min = temp;
			}
		}
	}
	
	return min;
}