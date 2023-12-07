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
	
	time = MPI_Wtime();
	for (i = 0; i < 10; i++) {
		for (j = 0; j < 30; j++) {
			for (k = 0; k < 30; k++) {

				multiple_matrix[rank * 10 + i][j] += matrix1[10 * rank + i][k] * matrix2[k][j];
			}
			//cout << "Rank: " << rank << "       " << 10 * rank + i << "    " << j << "        " << multiple_matrix[i][j] << endl;
		}
	}

	MPI_Reduce(multiple_matrix, total, 900, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	if (rank == 0) {
		cout << "--------------------------------   MPI   ----------------------------" << endl;
		time = MPI_Wtime() - time;
		for (int i = 0; i < 30; i++) {
			for (int j = 0; j < 30; j++) {
			
				cout << "i:       " << i << "    j:" << j << "        " << total[i][j] << endl;
			}
		}
		cout <<"time  :  "  <<time << endl;
	}
	

	MPI_Finalize();

	return 0; 
}
