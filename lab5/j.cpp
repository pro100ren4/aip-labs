#include <iostream>

using namespace std;

float* fill_arr(float *arr, int unsigned N);
float replace(float *arr, int unsigned N);
float sorted_arr(float *arr, int p, int q, int unsigned N);
void output_arr(float *arr, int unsigned N);

int main() {
 	unsigned int p, q, n;
 	cout << "Input 'p', 'q', 'n': ";
 	cin >> p >> q >> n;
 	
 	// Проверка условия
 	if (p <= 1 || q <= 1 || n <= 1) {
 		cout << "### not correct condition ###" << endl;
 		system("pause");
 		return 0;
	}
 	
 	float *arr = fill_arr(arr, n);
 	*arr = replace(arr, n);
 	cout << "1) ";
	output_arr(arr, n);
 	*arr = sorted_arr(arr, p, q, n);
 	cout << "2)";
	output_arr(arr, n);
 	
 	delete[] arr;
 	
 	system("pause");
	return 0;
}

float* fill_arr(float *arr, int unsigned N) {
	arr = new float[N];
	for (int i = 0; i < N; i++) {
		cout << "arr[" << i << "] = ";
		cin >> arr[i];
	}
	return arr;
}

float replace(float *arr, int unsigned N) {
	float* t = new float[N];
	int j = 0;
	for (int i = 0; i < N; i++){
		if (arr[i] == 0) t[j++] = 0;
	}
	for (int i = 0; i < N; i++) {
		if (arr[i] != 0) t[j++] = arr[i];
	}
	for (int i = 0; i < N; i++) {
		arr[i] = t[i];
	}
	delete[] t;
	return *arr;
}

float sorted_arr(float *arr, int p, int q, int unsigned N) {
	float temp;
	int i, j;
	for (j = q; j > 1; j--) {
		for (i = p; i < j - 1; i++) {
			if (arr[i] > arr[i+1]) {
				temp = arr[i];
				arr[i] = arr[i+1];
				arr[i+1] = temp;
			}
		}
	}
	return *arr;
}

void output_arr(float *arr, int unsigned N) {
	for (int i = 0; i < N; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}