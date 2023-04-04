#include <iostream>
using namespace std;

int in_arr (const int rows, const int cols, int** arr);
void number_arr (const int rows, const int cols, int** arr);
int sort_arr (const int rows, const int cols, int** arr);
void out_arr (const int rows, const int cols, int** arr);
void menu ();

int main () {	
	unsigned int rows, cols;
	
	cout << "Input number of rows: "; cin >> rows;
	cout << "Input number of colomns: "; cin >> cols;
	
	int** arr = new int*[rows];
	for (int i = 0; i < rows; i++){
		arr[i] = new int[cols];
	}
	
	menu();
	
	int e;
	
	do {
		cout <<"Choose the function: ";
		cin >> e;
	
		switch(e){
			case 1: **arr = in_arr (rows, cols, arr); break;
			case 2: out_arr (rows, cols, arr); break;
			case 3: number_arr (rows, cols, arr); break;
			case 4: **arr = sort_arr (rows, cols, arr); cout << "Done" << endl; break;
			case 10: break;
			default: cout << "Error" << endl;
		}
	}
	while (e != 10);
	
	for (int i = 0; i < rows; i++){
		delete[] arr[i];
		arr[i] = 0;
	}
		delete[] arr;
		arr = 0;
		
	return 0;
}

int in_arr (const int rows, const int cols, int** arr){
	
	for (int i = 0; i < rows; i++){
		for (int j = 0; j < cols; j++){
			cout << "Input arr[ " << i << " ][ " << j << " ]: " ; cin >> arr[i][j];
		}
	}	
	
	return **arr;
}

void number_arr (const int rows, const int cols, int** arr){
	
	int counter = 0;
		
	for (int i = 0; i < rows; i++){
		for (int j = 0; j < cols; j++){
			if (arr[i][j] > 0) break;
				if (j == (cols - 1)) counter++;	
		}
	}
	
	cout << "Number of rows without positive elements: " << counter << endl;	
}

int sort_arr (const int rows, const int cols, int** arr){
	
	for (int i = 0; i < rows; i++){
		for (int j = 0; j < cols; j++){
			
			bool flag = false;
			
			for (int p = (j+1); p < cols; p++){
				
				if (arr[i][j] == arr[i][p]) {
					
					arr[i][p] = 0;
					flag = true;
				}
			}	
		if (flag) arr[i][j] = 0;
		}
    }
    
    for (int j = 0; j < cols; j++){
		for (int i = 0; i < rows; i++){
			
			bool flag = false;
			
			for (int p = (i+1); p < rows; p++){
				
				if (arr[i][j] == arr[p][j]) {
					
					arr[p][j] = 0;
					flag = true;
				}
			}	
		if (flag) arr[i][j] = 0;
		}
    }

	return **arr;
}

void menu (){
	cout << "\n=========================" << endl;
	cout << "1.Enter values of array: " << endl;
	cout << "2.Output array: " << endl;
	cout << "3.Output number of rows without positive elements:" << endl;
	cout << "4.Sorting of the array: " << endl;
	cout << "5.Press 10 to exit: " << endl;
	cout << "=========================" << endl;
}


void out_arr (const int rows, const int cols, int** arr){
	
	for (int i = 0; i < rows; i++){
		for (int j = 0; j < cols; j++){
			cout << arr[i][j] << "\t";
		} 
		cout << endl;
	}
}