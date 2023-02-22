#include <stdio.h>
#include <windows.h>
#include <math.h>

int main()
{
	SetConsoleCP(65001); // поддержка русского языка 
	SetConsoleOutputCP(65001);
	
	float a,b,x,z;
	
	printf("Введите a:");
	scanf("%2f", &a);
	printf("Введите b:");
	scanf("%2f", &b);
	printf("Введите x:");
	scanf("%2f", &x);
	
	if(x <= a)
	{
		z = exp(x)/(3 + sin(x));
	}
	else
	{
		if(x <= b)
		{
			z = cos(x) + pow(x,2);	
		}
		else
		{
			z = 1.3 + sin(x);
		}
	}
	
	printf("Значение z: %g", z);
	
	return 0;
}