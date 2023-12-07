#include <iostream>
#include <omp.h>
using namespace std;

int main() {
	int matrix1[30][30], matrix2[30][30], multiple_matrix[30][30] = { 0 }, total[30][30] = { 0 };
	float time;
	int k, i, j;
	for (i = 0; i < 30; i++) {
		for (j = 0; j < 30; j++) {
			matrix1[i][j] = 2;
			matrix2[i][j] = 3;
		}
	}
	
	cout << "--------------------------------   OMP   ----------------------------" << endl;

	time = omp_get_wtime();
#pragma omp parallel shared( multiple_matrix ) private(i,j,k)
	{
#pragma omp for
		for (i = 0; i < 30; i++) {
			for (j = 0; j < 30; j++) {
				for (k = 0; k < 30; k++) {
					multiple_matrix[i][j] += matrix1[i][k] * matrix2[k][j];
				}
			}
		}
	}

	time = omp_get_wtime() - time;
	for (i = 0; i < 30; i++) {
		for (j = 0; j < 30; j++) {
			cout << "i:  " << i << "    j:" << j << "        " << multiple_matrix[i][j] << "       " << endl;
		}
	}
	cout << "time :  " << time << endl;
	

	return 0;
}
