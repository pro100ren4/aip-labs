#include <iostream>
#include <math.h>
#include <iomanip>

using namespace std;

float* fillArr(float *arr, unsigned int Size);
float maxFracPart(float *arr, unsigned int Size);
void selectionSort(float arr[],unsigned int start ,unsigned int stop);
void PrintArray(float arr[], unsigned int Size);

int main()
{
	cout << setprecision(8);
	unsigned int p, q, size, action;
	do
	{
		cout << "Input 'p', 'q', 'size' (1 < p < q < size) : ";
		cin >> p >> q >> size;
	}
	while(!(1 < p && p < q && q < size));
	
	float *arr = fillArr(arr, size);
	
	bool run = true;
	
	while(run)
	{
		cout << "Input action (1 - maxFracPart, 2 - slectionSort, 3 - printArray, 4 - exit): ";
		cin >> action;
		if(action == 1)
		{
			cout << maxFracPart(arr, size)	<< endl;
			cout << "===================" << endl;
		}
		else if(action == 2)
		{
			selectionSort(arr, p, q);
			cout << "Array was sorted" << endl;
			cout << "===================" << endl;
		}
		else if(action == 3)
		{
			PrintArray(arr, size);
			cout << "===================" << endl;
		}
		else if(action == 4)
		{
			run = false;
		}
	}
		
	delete[] arr;
	
	return 0;
}

float* fillArr(float *arr, unsigned int Size)
{
	arr = new float[Size];
	for (int i = 0; i < Size; i++) {
		cout << "arr[" << i << "] = ";
		cin >> arr[i];
	}
	return arr;
}

float maxFracPart(float *arr, unsigned int Size)
{
	float NumFracPart = 0;
	for(int i = 0; i < Size; i++)
	{
		if( (arr[i] - floor(arr[i]) ) > NumFracPart && arr[i] >= 0)
		{
			NumFracPart = arr[i] - floor(arr[i]);
		}
		else if((fabs(arr[i]) - floor(fabs(arr[i]))) > NumFracPart && arr[i] < 0)
		{
			NumFracPart = fabs(arr[i]) - floor(fabs(arr[i]));
		}
	}
	return NumFracPart;
}

void selectionSort(float arr[],unsigned int start ,unsigned int stop)
{
	int min,j; float temp;
	for(int i = start; i < stop; i++)
	{
		min = i; temp = arr[i];
		for(j = i + 1; j < stop;j++)
		{
			if(arr[j] < arr[i])
			{
				min = j;
			}
		}
		arr[i]=arr[min];
		arr[min]=temp;
	}
}


void PrintArray(float arr[], unsigned int Size)
{
	for(int i = 0; i < Size; i++)
	{
		cout << "arr[" << i << "] = " << arr[i] << endl;
	}
}