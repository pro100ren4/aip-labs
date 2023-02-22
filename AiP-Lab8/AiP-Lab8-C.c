#include <stdio.h>
#include <string.h>
#include <conio.h>
const int len = 100;
int main()
{
	char file_name[100];
	printf("1) A.txt\n2) B.txt\n3) C.txt\n");
	printf("please enter file name:");
	scanf("%s", file_name);
	printf("-----%s-----\n", file_name);
	
	FILE* file = fopen(file_name, "rt");
	
	int count = 0;
	char str[len]; 
	while(!feof(file))
	{
		fgets(str, len, file);
		printf("%s", str);
		if(str[0] == ' ' && str[strlen(str) - 2] == ' ')
		{
			count++;
		}
	}
	
	printf("\n==========\nNumber of string that srart and end with \'space\'-character: %d\n==========", count);
	 
	getch();
	return 0;
}