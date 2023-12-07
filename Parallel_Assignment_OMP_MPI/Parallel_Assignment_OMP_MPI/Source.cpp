#include <mpi.h>
#include <iostream>
#include <omp.h>
using namespace std;

int main() {
	int matrix1[30][30], matrix2[30][30], multiple_matrix[30][30] = { 0 }, total[30][30] = { 0 };
	float time;
	int rank;
	int k, i, j;
	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	for (i = 0; i < 30; i++) {
		for (j = 0; j < 30; j++) {
			matrix1[i][j] = 2;
			matrix2[i][j] = 3;
		}
	}
	
	time = omp_get_wtime();
	int total1[30][30] = { 0 }, multiple_matrix1[3][30][30] = { 0 };
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	for (i = 0; i < 30; i++) {
		for (j = 0; j < 30; j++) {
			total[i][j] = 0; 
		}
	}
	
	int nthr, tid;
#pragma omp parallel private(i,j,k, tid) num_threads(3)
	{
	
		tid = omp_get_thread_num();
		for (i = tid + rank * 10; i < 10 * (rank + 1); i += 3) {
			for (j = 0; j < 30; j++) {
				for (k = 0; k < 30; k++) {
					multiple_matrix1[tid][i][j] += matrix1[i][k] * matrix2[k][j];
				}
			}
		}
	}
	
	for (tid = 0; tid < 3; tid++) {
		for ( i = 0; i < 30; i++) {
			for ( j = 0; j < 30; j++) {
				total[i][j] += multiple_matrix1[tid][i][j];
			}
		}
	}
	MPI_Reduce(total, total1, 900, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	if (rank == 0) {
		cout << "--------------------------------   MPI_OMP   ----------------------------" << endl;
		time = omp_get_wtime() - time;
		for (int i = 0; i < 30; i++) {
			for (int j = 0; j < 30; j++) {
				cout << "i:       " << i << "       j:" << j << "        " << total1[i][j] << endl;
			}
		}
		cout <<"time : " << time << endl;
	}
	MPI_Finalize();



	return 0;
}
