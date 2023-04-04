#include <iostream>
#include <windows.h>

using namespace std;
const unsigned int nrow = 5, ncol = 5;

void create_arr(int** arr, int nrow, int ncol);
void output_arr(int** arr, int nrow, int ncol);
void delete_arr(int** arr, int nrow, int ncol);
void num_elem_arr(int** arr, int nrow, int ncol);
void local_max_arr(int** arr, int nrow, int ncol);
int amount_elem_arr(int** arr, int i, int j);

int main() {
	SetConsoleCP(65001);
	SetConsoleOutputCP(65001);
	
	int** arr = new int*[nrow];
	for (int i = 0; i < nrow; i++) {
		arr[i] = new int[ncol];
	}
	
	cout << "### Поиск локальных максимумов матрицы 5х5 ###" << endl;
	cout << "1) Найти количество и сумму нечётных элементов матрицы." << endl;
	cout << "2) Найти количество локальных максимумов матрицы." << endl;
	system("pause");
	
	cout << "### Ввод элементов матрицы ###" << endl;
	system("pause");
	create_arr(arr, nrow, ncol);
	
	cout << "### Итоговая матрица: " << endl;
	output_arr(arr, nrow, ncol);
	
	num_elem_arr(arr, nrow, ncol);
	system("pause");

	local_max_arr(arr, nrow, ncol);
	delete_arr(arr, nrow, ncol);
 	
 	cout << "### Конец ###" << endl;
 	system("pause");
	return 0;
}

void create_arr(int** arr, int nrow, int ncol) {	
	for (int i = 0; i < nrow; i++){
		for (int j = 0; j < ncol; j++){
			//arr[i][j] = rand() % 20;
			cout << "Input arr[ " << i << " ][ " << j << " ]: " ; cin >> arr[i][j];
		}
	}
	cout << endl;
}

void output_arr(int** arr, int nrow, int ncol) {
	for (int i = 0; i < nrow; i++) {
		for (int j = 0; j < ncol; j++) {
			cout << arr[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;
}

void delete_arr(int** arr, int nrow, int ncol) {
	for (int i = 0; i < nrow; i++) {
		delete[] arr[i];
	}
	delete[] arr;
}

void num_elem_arr(int** arr, int nrow, int ncol) {
	int count1 = 0, count2 = 0;
	
	for (int i = 0; i < nrow; i++) {
		for (int j = 0; j < ncol; j++) {
			if ((arr[i][j] % 2 != 0) && (arr[i][j] < 0)) {
				count1 += arr[i][j];
				count2 += 1;
			}
		}
	}
	cout << "### Количество нечётных отрицательных элементов матрицы: " << count2 << endl;
	cout << "### Сумма нечётных отрицательных элементов матрицы: " << count1 << endl;
	cout << endl;
}

void local_max_arr(int** arr, int nrow, int ncol) {
	int count = 0;
	for (int i = 0; i < nrow; i++) {
		for (int j = 0; j < ncol; j++) {
			if (((i - 1 == -1) && (j + 1 == ncol)) 
			 || ((i + 1 == nrow) && (j + 1 == ncol))
			 || ((i + 1 == nrow) && (j - 1 == -1)) 
			 || ((i - 1 == -1) && (j - 1 == -1))) { // Угловые элементы матрицы
				if (amount_elem_arr(arr, i, j) == 3) count += 1;
			} else if ((j + 1 == ncol) || (j - 1 == -1) 
			 || (i - 1 == -1) || (i + 1 == nrow)) { // Боковые элементы матрицы
				if (amount_elem_arr(arr, i, j) == 5) count += 1;
			} else {
				if (amount_elem_arr(arr, i, j) == 8) count += 1;
			}
		}
	}
	cout << "### Количество локальных максимумов матрицы: " << count << endl;
}

int amount_elem_arr(int** arr, int i, int j) {
	int temp = 0;
	if (j + 1 < ncol) { // Правый элемент
		if (arr[i][j] > arr[i][j+1]) {
			temp += 1;
		}
	}
	
	if (j - 1 > -1) { // Левый элемент
		if (arr[i][j] > arr[i][j-1]) {
			temp += 1;
		}
	}
	
	if (i - 1 > -1) { // Верхний элемент
		if (arr[i][j] > arr[i-1][j]) {
			temp += 1;
		}
	}
	
	if (i + 1 < nrow) { // Нижний элемент
		if (arr[i][j] > arr[i+1][j]) {
			temp += 1;
		}
	}
	
	if ((i - 1 > -1) && (j + 1 < ncol)) { // Верхний правый элемент
		if (arr[i][j] > arr[i-1][j+1]) {
			temp += 1;
		}
	}
	
	if ((i + 1 < nrow) && (j + 1 < ncol)) { // Нижний правый элемент
		if (arr[i][j] > arr[i+1][j+1]) {
			temp += 1;
		}
	}
	
	if ((i + 1 < nrow) && (j - 1 > -1)) { // Нижний левый элемент
		if (arr[i][j] > arr[i+1][j-1]) {
			temp += 1;
		}
	}
	
	if ((i - 1 > -1) && (j - 1 > -1)) { // Верхний левый элемент
		if (arr[i][j] > arr[i-1][j-1]) {
			temp += 1;
		}
	}
	return temp;
}