#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

// Данные
typedef struct data {
	unsigned int index_number;
	char payer_account[11];
	char buyer_account[11];
	unsigned int transferred_amount;
} data;

// Определение узла бинарного дерева
typedef struct Node {
	data inf;
	struct Node *left;
	struct Node *right;
} Node;

const int size_data = sizeof(data); // Размер информационного поля

Node *create_tree(Node *root); // Организация дерева
Node *create_new(data inf); // Создание узла
Node *insert(Node *node, data inf); // Вставка нового узла в дерево
Node *create_new_node(Node *node); // Добавление определённого количества узлов
Node *search(Node *node, int key); // Поиск узла по значению(index)

Node *delete_node(Node *root, int index); // Удаление узла дерева
Node *minValue_node(Node *node); // Поиск минимального значения(вспомогательная функция)

data read_data(int count); // Чтение данных

void loading_to_file(FILE *f, Node *node); // Загрузка в файл
Node *upload_from_file(FILE *f);  // Загрузка из файла

void pre_order(Node *node); // прямой обход
void in_order(Node *node); // симметричный обход
void post_order(Node *node); // обратный обход
void print_tree(Node *node, int level); // вывод структуры дерева

//Функции, согласно варианту
void leaf_output(Node *node); // Вывод всех листьев дерева
int average(Node *node); // Вывод среднего арифметического всеё перечисленной суммы
int count_notes(Node *node); // Вспомогательная функция(подсчёт узлов относительно текущего)

// Балансировка дерева
Node *balance_tree(Node *root);
Node *rotate_left(Node *node);
Node *rotate_right(Node *node);
int get_balabce_factor(Node *node);

void delete_tree(Node *node); // Освобождение памяти всего дерева

int main() {
	system("chcp 65001");
	system("cls");

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

	int TreeCheck = 0; // Вспомогательная переменная для предотвращения повторной записи в файл
	int RootCheck = 1; // Вспомогательная переменная для отображения текущего дерева

	Node *temp = NULL; // Вспомогательная переменная обмена корней дерева
	Node *root = NULL, *root_temp = NULL; // Переменные, которые будут указывать на корни деревьев
	root = create_tree(root);
	char c;

	while (1) {
		system("cls");

		if (RootCheck == 1) printf("->Tree1    Tree2\n\n");
		else if (RootCheck == 2) printf("Tree1 ->Tree2\n\n");

		puts("0 - Exit");
		puts("1 - Pre-order");
		puts("2 - In-order");
		puts("3 - Post_order");
		puts("4 - Adding a node to the tree");
		puts("5 - Removing a node by index value");
		puts("6 - Displaying all the leaves of a tree");
		puts("7 - Loading data to a file and creating a new tree");
		puts("8 - Finding a Specific Node");
		puts("9 - Printing of the tree structure");
		puts("a - Number of nodes in the tree");
		puts("b - Arithmetic mean of the entire transferred amount\n");

		puts("x - change tree");


		c = getch();
		switch (c) {
			case '1':
				system("cls");
				puts("| Index number | Payer's account | Buyer's account | Transferred amount |\n");
				pre_order(root);
				getch();
				break;
			case '2':
				system("cls");
				puts("| Index number | Payer's account | Buyer's account | Transferred amount |\n");
				in_order(root);
				getch();
				break;
			case '3':
				system("cls");
				puts("| Index number | Payer's account | Buyer's account | Transferred amount |\n");
				post_order(root);
				getch();
				break;
			case '4':
				root = create_new_node(root);
				break;
			case '5':
				int index;
				printf("\nEnter the index of the node to be deleted: ");
				scanf("%d", &index);

				if (search(root, index) != NULL) {
					root = delete_node(root, index);
					puts("\nNode deleted successfully!");
				}
				else {
					puts("\nNo such node exists in the tree :(");
				}

				getch();
				break;
			case '6':
				leaf_output(root);
				getch();
				break;
			case '7':
				if (TreeCheck == 1) {
					puts("\nThe new tree has already been created!!!");
					getch();
				}
				else {
					fseek(f, 0, SEEK_END);
					loading_to_file(f, root);
					puts("\nThe data has been loaded into a file.");
					puts("Press any key to make a new tree(Tree2)...");
					getch();
					root_temp = root;
					root = upload_from_file(f);

					TreeCheck = 1;
					RootCheck = 2;
				}
				break;
			case '8':
				int key;
				printf("\nEnter the index of the desired node: ");
				scanf("%d", &key);

				if (search(root, key) != NULL) puts("\nThe node exists in the tree :)");
				else puts("No such node exists in the tree :(");

				getch();
				break;
			case '9':
				printf("\n");
				print_tree(root, 0);
				getch();
				break;
			case 'a':
				printf("\nNodes count: %d", count_notes(root));
				getch();
				break;
			case 'b':
				printf("\nAverage: %f", (float)average(root)/count_notes(root));
				getch();
				break;
			case 'x':
				if (root_temp != NULL) {
					temp = root_temp;
					root_temp = root;
					root = temp;

					if (RootCheck == 1) RootCheck = 2;
					else if (RootCheck == 2) RootCheck = 1;

					puts("\nThe current tree has been changed. Press any key...");
					getch();
				}
				break;
			case '0':
			case 3:
				delete_tree(root);
				delete_tree(root_temp);
				fclose(f);
				system("chcp 866");
				return 0;
			default:
				puts("Error, wrong choice...");
				getch();
				system("cls");
		}
	}
}

Node *create_tree(Node *root) {
	int count;
	printf("Enter the initial number of elements in the tree: ");
	while (scanf("%d", &count) != 1) {
		rewind(stdin);
		printf("\nEnter correct value!");
		printf("Enter the initial number of elements in the tree: ");
	}

	for ( ; count > 0; count--) {
		data inf = read_data(count);
		root = insert(root, inf);
		system("cls");
	}

	return root;
}

Node *insert(Node *node, data inf) {
	if (node == NULL) {
		return create_new(inf);
	}

	if (inf.index_number < node->inf.index_number) {
		node->left = insert(node->left, inf);
	}
	else if (inf.index_number >= node->inf.index_number) {
		node->right = insert(node->right, inf);
	}

	return node;
}

Node *create_new(data inf) {
	Node *temp = (Node*) malloc(sizeof(Node));
	temp->inf = inf;
	temp->left = NULL;
	temp->right = NULL;

	return temp;
}

Node *create_new_node(Node *node) {
	int count;
	printf("\nNumber of added nodes: ");
	while (scanf("%d", &count) != 1) {
		rewind(stdin);
		printf("\nEnter correct value!");
		printf("Number of added nodes: ");
	}

	for ( ; count > 0; count--) {
		data inf = read_data(count);
		node = insert(node, inf);
		system("cls");
	}

	return node;
}

Node *search(Node *node, int key) {
	if (node == NULL || node->inf.index_number == key) {
		return node;
	}

	if (key < node->inf.index_number) {
		return search(node->left, key);
	}
	return search(node->right, key);
}

Node *delete_node(Node *root, int index) {
	if (root == NULL) {
		return root;
	}

	if (index < root->inf.index_number) {
		root->left = delete_node(root->left, index);
	}
	else if (index > root->inf.index_number) {
		root->right = delete_node(root->right, index);
	}
	else {
		if (root->left == NULL) {
			Node *temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL) {
			Node *temp = root->left;
			free(root);
			return temp;
		}

		Node *temp = minValue_node(root->right);
		root->inf = temp->inf;
		root->right = delete_node(root->right, temp->inf.index_number);
	}

	return root;
}

Node *minValue_node(Node *node) {
	Node *current = node;
	while (current && current->left != NULL) {
		current = current->left;
	}

	return current;
}

data read_data(int count) {
	system("cls");
	data inf;
	printf("items left to enter: %d\n", count);
	puts("Input index number: ");
	while (scanf("%d", &inf.index_number) != 1) {
		rewind(stdin);
		printf("Enter correct value! Input index number: \n");
	}
		
	while (1) {
		puts("Input payer account: ");
		scanf("%s", inf.payer_account);
		if ((strlen(inf.payer_account) > 10) || (strlen(inf.payer_account) < 10)) {
			puts("Error input...\n");
			continue;
		}
		break;
	}
		
	while (1) {
		puts("Input buyer account: ");
		scanf("%s", inf.buyer_account);
		if ((strlen(inf.buyer_account) > 10) || (strlen(inf.buyer_account) < 10)) {
			puts("Error input...\n");
			continue;
		}
		break;
	}
		
	puts("Input transferred amount: ");
	while (scanf("%d", &inf.transferred_amount) != 1) {
		rewind(stdin);
		printf("Enter coorect value! Input transferred amount: ");
	}

	system("cls");
	return inf;
}

// Запись в файл
void loading_to_file(FILE *f, Node *node) {
	if (node == NULL) return;
	fwrite(&node->inf, size_data, 1, f);
	loading_to_file(f, node->left);
	loading_to_file(f, node->right);
}

// Выгрузка из файла
Node *upload_from_file(FILE *f) {
	Node *root = NULL;
	data inf;
	rewind(f);
	while (fread(&inf, size_data, 1, f) > 0) {
		root = insert(root, inf);
	}
	return root;
}

void pre_order(Node *node) {
	if (node == NULL) return;
	printf("%4d %22s %17s %12d\n", node->inf.index_number, node->inf.payer_account, node->inf.buyer_account, node->inf.transferred_amount);
	pre_order(node->left);
	pre_order(node->right);
}

void in_order(Node *node) {
	if (node == NULL) return;
	in_order(node->left);
	printf("%4d %22s %17s %12d\n", node->inf.index_number, node->inf.payer_account, node->inf.buyer_account, node->inf.transferred_amount);
	in_order(node->right);
}

void post_order(Node *node) {
	if (node == NULL) return;
	post_order(node->left);
	post_order(node->right);
	printf("%4d %22s %17s %12d\n", node->inf.index_number, node->inf.payer_account, node->inf.buyer_account, node->inf.transferred_amount);
}

void print_tree(Node *node, int level) {
	if (node == NULL) {
		return;
	}
	print_tree(node->right, level + 1);
	for (int i = 0; i < level; i++) {
		printf("	");
	}
	printf("[%d]\n", node->inf.index_number);
	print_tree(node->left, level + 1);
}

// Функции, согласно варианту
void leaf_output(Node *node) {
	if (node == NULL) {
		return;
	}

	if (node->left == NULL && node->right == NULL) {
		printf("%d ", node->inf.index_number);
		return;
	}
	leaf_output(node->left);
	leaf_output(node->right);
}

int average(Node *node) {
	if (node == NULL) {
		return 0;
	}
	else {
		return node->inf.transferred_amount + average(node->left) + average(node->right);
	}
}

int count_notes(Node *node) {
	if (node == NULL) {
		return 0;
	}
	else {
		return 1 + count_notes(node->left) + count_notes(node->right);
	}
}

// Балансировка дерева
Node *balance_tree(Node *root) {
	int balabce_factor = get_balabce_factor(root);
	if (balabce_factor > 1) {
		if (get_balabce_factor(root->left) < 0) {
			root->left = rotate_left(root->left);
		}
		root = rotate_right(root);
	}
	else if (balabce_factor < -1) {
		if (get_balabce_factor(root->right) > 0) {
			root->right = rotate_right(root->right);
		}
		root = rotate_left(root);
	}
	return root;
}

int get_balabce_factor(Node *node) {
	if (node == NULL) {
		return 0;
	}
	return count_notes(node->left) - count_notes(node->right);
}

Node *rotate_left(Node *node) {
	Node *new_root = node->right;
	node->right = new_root->left;
	new_root->left = node;
	//node->
}

void delete_tree(Node *node) {
	if (node == NULL) {
		return;
	}
	delete_tree(node->left);
	delete_tree(node->right);
	free(node);
}