#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

typedef struct order {
	int index_number;
	char payer_account[11];
	char buyer_account[11];
	int transferred_amount;
} order;

typedef struct order_data {
	order inf;
	struct order_data* next;
} order_data;

const int size_order = sizeof(order);

int WriteToFileFlag = 0;

void print_list(order_data *beg);
void del_list(order_data *beg);
void print_to_file(FILE *f, order_data *beg);
void create_list_file(FILE *f);
order read_data(int count);
order_data *del_element(order_data *beg);
order_data *del_two_element(order_data *beg);
order_data *add_first(order_data *beg, order base);
order_data *create_list(order_data *beg);

int main() {
	system("cls");
	order_data *beg = NULL;
	char c;

	FILE *f = fopen("fileData.dat", "rb+");
	if (!f) {
		f = fopen("fileData.dat", "wb+");
		if (!f) {
			puts("File opening error\n");
			getch();
			system("cls");
			return 1;
		}
	}

	beg = create_list(beg);

	system("cls");
	while (1) {
		puts("1 - Printing the elements of a list");
		puts("2 - Remove list element by index number");
		puts("3 - Add item to list");
		puts("4 - Save data to file");
		puts("5 - Creating a new list based on data from a file");
		puts("6 - ### Assignment by option. Remove the first two elements of the list");
		puts("0 - Exit");
		c = getch();
		switch (c) {
			case '1':
				print_list(beg);
				break;
			case '2':
				beg = del_element(beg);
				break;
			case '3':
				order base;
				base = read_data(1);
				beg = add_first(beg, base);
				system("cls");
				break;
			case '4':
				print_to_file(f, beg);
				WriteToFileFlag += 1;
				break;
			case '5':
				create_list_file(f);
				break;
			case '6':
				beg = del_two_element(beg);
				break;
			case '0':
			case 3:
				del_list(beg);
				fclose(f);
				system("cls");
				return 0;
			default:
				puts("Error, wrong choice...");
				getch();
				system("cls");
		}
	}
}

void print_list(order_data *beg) {
	system("cls");
	puts("| Index number | Payer's account | Buyer's account | Transferred amount |\n");	
	while (beg != NULL) {
		printf("%4d %22s %17s %12d\n", beg->inf.index_number, beg->inf.payer_account, beg->inf.buyer_account, beg->inf.transferred_amount);
		beg = beg->next;
	}
	getch();
	system("cls");
}

void del_list(order_data *beg) {
	while (beg != NULL) {
		order_data *t = beg;
		beg = t->next;
		free(t);
	}
}

void print_to_file(FILE *f, order_data *beg) {
	order base;
	while (beg != NULL) {
		base = beg->inf;
		fwrite(&base, size_order, 1, f);
		beg = beg->next;
	}

	puts("\nThe data was successfully written to the file!");
	getch();
	system("cls");
}

void create_list_file(FILE *f) {
	if (WriteToFileFlag == 0) {
		puts("\nFile has not been created yet!!!");
		getch();
		system("cls");
		return;
	}
	order_data *beg = NULL;
	order base;

	rewind(f);
	
	while (fread(&base, size_order, 1, f) > 0) {
		beg = add_first(beg, base);
	}

	puts("\nNew list created!");
	getch();
	system("cls");
	puts("Data from file:\n");
	print_list(beg);
	puts("Press any button to delete the newly created list:");
	getch();
	del_list(beg);
	system("cls");
}

order read_data(int count) {
	system("cls");
	order base;
	printf("items left to enter: %d\n", count);
	puts("Input index number: ");
	while (scanf("%d", &base.index_number) != 1) {
		rewind(stdin);
		printf("Enter correct value! Input index number: \n");
	}
		
	while (1) {
		puts("Input payer account: ");
		scanf("%s", base.payer_account);
		if ((strlen(base.payer_account) > 10) || (strlen(base.payer_account) < 10)) {
			puts("Error input...\n");
			continue;
		}
		break;
	}
		
	while (1) {
		puts("Input buyer account: ");
		scanf("%s", base.buyer_account);
		if ((strlen(base.buyer_account) > 10) || (strlen(base.buyer_account) < 10)) {
			puts("Error input...\n");
			continue;
		}
		break;
	}
		
	puts("Input transferred amount: ");
	while (scanf("%d", &base.transferred_amount) != 1) {
		rewind(stdin);
		printf("Enter coorect value! Input transferred amount: ");
	}

	return base;
	system("cls");
}

order_data *del_element(order_data *beg) {
	if (beg == NULL) {
		puts("\nThe list is empty, deleting elements is not possible!");
		getch();
		puts("!!! Use function 3 to add an element to the list ->");
		getch();
		system("cls");
		return beg;
	}

	int number;
	order_data *t1 = beg, *t2 = beg;
	printf("\nEnter the item's index number: ");
	scanf("%d", &number);

	if (beg->inf.index_number == number) {
		t1 = beg;
		beg = beg->next;
		free(t1);
		puts("item removed successfully!");
		getch();
		system("cls");
		return beg;
	}

	beg = beg->next;

	while (1) {
		if (beg == NULL) {
			puts("element with this number is not in the list!\n");
			getch();
			system("cls");
			return t1;
		}
		if (beg->inf.index_number == number) {
			t2->next = beg->next;
			free(beg);
			puts("item removed successfully!");
			getch();
			break;
		}
		t2 = t2->next;
		beg = beg->next;
	}
	system("cls");
	return t1;
}

order_data *del_two_element(order_data *beg) {
	system("cls");
	if (beg != NULL && beg->next != NULL) {
		int i = 0;
		while (beg != NULL) {
			if (i == 2) break;
			order_data *t1 = beg;
			beg = t1->next;
			i += 1;
			free(t1);
		}
		puts("items removed successfully!");
		getch();
	} else {
		puts("Not enough items to delete...");
		getch();
	}
	system("cls");
	return beg;
}

order_data *add_first(order_data *beg, order base) {
	order_data *t;
	t = (order_data*) malloc(sizeof(order_data));
	t->inf = base;
	t->next = beg;
	beg = t;
	return beg;
}

order_data *create_list(order_data *beg) {
	order base;
	int count;
	printf("Count base(Accounts must be 10 characters long!): ");
	scanf("%d", &count);
	

	while (count != 0) {
		base = read_data(count);
		beg = add_first(beg, base);
		count -= 1;
	}

	return beg;
}