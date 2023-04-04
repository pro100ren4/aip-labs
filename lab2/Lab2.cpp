#include <iostream>
#include <windows.h>
#include <math.h>

using namespace std;

int main()
{	
	SetConsoleCP(65001); // поддержка русского языка 
 	SetConsoleOutputCP(65001);
 	
	float a,b,x,z;
	
	cout << "Введите значение a:";
	cin >> a;
	
	cout << "Введите значение b: ";
	cin >> b;
	
	cout << "Введите значение x:";
	cin >> x;
	
	if(x <= a)
	{
		z = exp(x)/(3 + sin(x));
	}
	else
	{
		if(x <= b)
			z = cos(x) + pow(x,2);
		else
			z = 1.3 + sin(x);
	}
	
	cout << "Значение z:" << z << endl;
	
	return 0;
}