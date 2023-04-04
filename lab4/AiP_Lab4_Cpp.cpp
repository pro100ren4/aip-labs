#include <iostream>
#include <math.h>
using namespace std;
int main()
{
	unsigned int length;
	cout<<"input length: ";
	cin>> length;
	float mass[length];

	for(int i = 0; i<length;i++) // Ввод элементов массива 
	{
		cout<<"input elem "<<i<<": ";
		cin>>mass[i]; 	
	}
	
	float sum = 0;
	for(int i = 0; i<length; i++)// Поиск суммы элементов с нечетным индексом
	{
		if(i%2 == 1 && mass[i] > 0)
		{
			sum += mass[i];
		}
	}
	cout<<"sum: "<<sum<<endl;
	
	int firstNegative = 0, lastNegative = length - 1;
	for(int i = 0; i < length; i++)// Поиск первого и последнего отрицательного 
	{
		if(mass[i]<0)
		{
			firstNegative = i;
			break;
		}
	}
	
	for(int i = length; i > 0; i--)
	{
		if(mass[i]<0)
		{
			lastNegative = i;
			break;
		}
	}
	
	float sum2 = 0;
	for(int i = 0; i < firstNegative; i++) // Поиск Суммы перед первым и после последнего отрицательными
	{
		sum2 += mass[i];	
	}
	
	for(int i = lastNegative+1; i < length ; i++)
	{
		sum2 += mass[i];
	}
	
	cout<<"firstNegative: "<<firstNegative<<", lastNegative: "<<lastNegative<<", sum2: "<<sum2<<endl;
	
	int countFabs = 0; // Удаление элементов модуль которых меньше 1
	for(int i = 0; i < length; i++)
	{
		if(fabs(mass[i])<1)
		{
			countFabs++;
		}
	}
	cout<<"countFabs: "<<countFabs<<endl;
	int chLength = length - countFabs;
	int j = 0;
	
	float changedMass[chLength];
	for(int i = 0; i < chLength; i++,j++)
	{	
		while(fabs(mass[j])< 1)
			j++;
		changedMass[i] = mass[j];
	}
	
	for(int i = chLength; i > 1; i--)// Сортировка
	{
		for (int j = 0; j < i-1; j++)
		{
			float temp;
			if(changedMass[j]<changedMass[j+1])
			{
				temp = changedMass[j];
				changedMass[j] = changedMass[j+1];
				changedMass[j+1] = temp;
			}
		}
	}
	
	
	for(int i = 0; i < chLength; i++)// Вывод измененного массива 
	{
		cout<<"ChMass "<<i<<": "<<changedMass[i]<<endl;
	}
	
	return 0;
}