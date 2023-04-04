#include <iostream>
#include <math.h>
#include <windows.h>

using namespace std;

int main()
{	
	SetConsoleCP(65001); // поддержка русского языка 
 	SetConsoleOutputCP(65001);
 	
 	float a,b,x,xn,xk,dx,z;
 	
	cout<<"Введите значение а:";
	cin>>a;
	cout<<"Введите значение b:";
	cin>>b;
	cout<<"Введите значение Xнач:";
	cin>>xn;
	cout<<"Введите значение Xкон:";
	cin>>xk;
	cout<<"Введите шаг:";
	cin>>dx;
	
	x = xn;
	
	cout<<"|\tx\t|\tz=f(x)\n";
	
	while(x<=xk)
	{
		cout<<"|\t"<<x<<"\t|";
		if(x <= a)
		{
			z = exp(x)/(3+sin(x));
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
		
		cout<<"\t"<<z<<endl;
		
		x += dx;
	}
	
	return 0;
}