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

order_data *create_list(order_data *beg, int count);
order read_data();
void del_list(order_data *beg);
void print_list(order_data *beg);

// сортировка
order_data *sorting_measurements(order_data *beg);

//Добавление элемента сразу в своё место(моментальная сортировка)
//order_data *adding_element_in_its_place(order_data *beg);

// вспомогательные функции
int list_len(order_data *beg);

int main() {
	system("cls");

	order_data *beg = NULL, *end = NULL;
	unsigned int count;
	char c;

	printf("Initial number of elements in the list: ");
	scanf("%d", &count);

	beg = create_list(beg, count);

	while (1) {
		puts("1 - Printing the elements of a list");
		puts("2 - Sorting information field values ​​(easy sorting)");
		puts("3 - Adding an element to the list immediately in its place");
		puts("0 - Exit");

		c = getch();
		switch (c) {
			case '1':
				print_list(beg);
				break;
			case '2':
				beg = sorting_measurements(beg);
				break;
			//case '3':
				//beg = adding_element_in_its_place(beg);
				//break;
			case '0':
			case 3:
				del_list(beg);
				system("cls");
				return 0;
			default:
				puts("Error, wrong choice...");
				getch();
				system("cls");
		}
	}
}

order_data *create_list(order_data *beg, int count) {
	order_data *current = NULL;
	for ( ; count > 0; count--) {
		order_data *node = (order_data*) malloc(sizeof(order_data));
		node->inf = read_data();
		node->next = NULL;

		if (beg == NULL) {
			beg = node;
			current = node;
		}
		else {
			current->next = node;
			current = node;
		}
	}

	system("cls");
	return beg;
}

order read_data() {
	order base;
	system("cls");
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
		order_data *node = beg;
		beg = node->next;
		free(node);
	}
}

// Лёгкая сортировка
order_data *sorting_measurements(order_data *beg) {
	order_data *node1, *node2;
	node1 = beg;

	for ( ; node1->next != NULL; node1 = node1->next) {
		node2 = node1->next;
		for ( ; node2 != NULL; node2 = node2->next) {
			if (node1->inf.transferred_amount > node2->inf.transferred_amount) {
				order base = node1->inf;
				node1->inf = node2->inf;
				node2->inf = base;
			}
		}
	}

	puts("\nlist sorted!!!");
	getch();
	system("cls");
	return beg;
}


// Вспомогательная функция(Длина списка)
int list_len(order_data *beg) {
	int i = 0;
	for ( ; beg != NULL; beg = beg->next) i += 1;
	return i;
}