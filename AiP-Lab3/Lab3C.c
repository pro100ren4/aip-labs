#include <stdio.h>
#include <math.h>
#include <windows.h>

int main()
{
	SetConsoleCP(65001);
	SetConsoleOutputCP(65001);
	
	float a,b,x,z,xn,xk,dx;
	
	printf("Введите a:");
	scanf("%f",&a);
	printf("Введите b:");
	scanf("%f",&b);
	printf("Введите xn:");
	scanf("%f",&xn);
	printf("Введите xk:");
	scanf("%f",&xk);
	printf("Введите шаг:");
	scanf("%f",&dx);
	
	x = xn;
	
	printf("|\tx\t|\tz\t|\n");
	
	for(;x <= xk;x += dx)
	{
		printf("|\t%.3f\t",x);
		
		if(x <= a)
		{
			z = exp(x)/(3 + sin(x));
		}
		else
		{
			if(x >= b)
			{
				z = 1.3 + sin(x);
			}
			else
			{
				z = cos(x) + pow(x,2);
			}
		}
		
		printf("|\t%.3f\t|\n",z);
		//x += dx;
	}
	
	return 0;
}