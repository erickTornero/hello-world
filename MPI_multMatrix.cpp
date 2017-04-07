#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <mpi.h>

#define A_VAL 3.0
#define B_VAL 5.0
#define N 1000
double A[N][N], B[N][N], C[N][N];

double calcError(double *M, double val, int n)
{
	double error = 0.0;
	int i;
	for (i = 0; i < n*n; i++)
		error += fabs(M[i] - val);
	return error;
}

void serialMul(double time_par)
{
	double startTimeSeq = 0, endTimeSeq = 0, durationSeq = 0;
	printf("Processing serial multiplication...\n\n");
	// Serial
	for (int p = 1; p < 11; p++)
	{
		startTimeSeq = MPI_Wtime();
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
			{
				C[i][j] = 0;
				// Your serial code here...
				for (int k = 0; k < N; k++) {
					C[i][j] += A[i][k] * B[k][j];
				}
			}
		endTimeSeq = MPI_Wtime();
		durationSeq += endTimeSeq - startTimeSeq;
	}
	printf("End of serial multiplication...\n");
	printf("Seq Error = %f\n", calcError(&C[0][0], N * A_VAL * B_VAL, N));
	printf("Seq Time 10x= %f seg\n\n", durationSeq / 10.0);

	printf("Speedup = %f\n", durationSeq / time_par);
}

void main(int argc, char* argv[])
{
	int i, j, k;
	int p_id, n_p;
	int tag = 0;
	double startTimePar, endTimePar, durationPar = 0;
	double cVal;

	MPI_Status status;

	printf("---- Computacion de Alto Rendimiento ---- \n");
	printf("           Laboratorio 2 (MPI)     \n\n");

	printf("Pregunta 1: Multiplicacion de 2 matrices con MPI punto-a-punto\n");
	printf(" a) Con 8 procesos MPI: \n\n");
	printf("###############################################################################\n\n");

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &p_id);
	MPI_Comm_size(MPI_COMM_WORLD, &n_p);

	if (p_id == 0)
	{
		printf("The master task of %d slave tasks is running!\n\n", n_p);
		cVal = N * A_VAL * B_VAL;
		for (i = 0; i < N; i++)
			for (j = 0; j < N; j++)
			{
				A[i][j] = A_VAL;
				B[i][j] = B_VAL;
			}
	}
	else
	{
		printf("The slave task is now running...\n");
		printf("The Process ID is %d.\n\n", p_id);
	}
	for (int p = 1; p < 11; p++)
	{
		startTimePar = MPI_Wtime();

		// Distribuicion de datos
		if (p_id == 0)
		{
			for (i = 1; i < n_p; i++)
			{
				MPI_Send(&A[i*N / n_p][0], N*N / n_p, MPI_DOUBLE, i, tag, MPI_COMM_WORLD);
				MPI_Send(&B, N*N, MPI_DOUBLE, i, tag, MPI_COMM_WORLD);
			}
		}
		else
		{
			MPI_Recv(&A, N*N / n_p, MPI_DOUBLE, 0, tag, MPI_COMM_WORLD, &status);
			MPI_Recv(&B, N*N, MPI_DOUBLE, 0, tag, MPI_COMM_WORLD, &status);
		}

		// Computacion
		if (p == 1)
			printf("Processing MPI multiplication.");
		else
			printf(".");

		for (i = 0; i < (N / n_p); i++)
			for (j = 0; j < N; j++)
			{
				//  Your code here...
				C[i][j] = 0;
				// Your serial code here...
				for (int k = 0; k < N; k++) {
					C[i][j] += A[i][k] * B[k][j];
				}
			}

		// Colecta del resultado
		if (p_id != 0) // Slave
		{
			MPI_Send(&C, N*N / n_p, MPI_DOUBLE, 0, tag, MPI_COMM_WORLD);
			if (p == 10)
				printf("\nI have finished my slave work!\n");
		}
		else // Master
		{
			for (i = 1; i < n_p; i++)
			{
				MPI_Recv(&C[i*N / n_p][0], N*N / n_p, MPI_DOUBLE, i, tag, MPI_COMM_WORLD, &status);
			}
			endTimePar = MPI_Wtime();
			durationPar += endTimePar - startTimePar;
		}
	}
	if (p_id == 0)
	{
		printf("\n\nMPI Error = %f\n", calcError(&C[0][0], cVal, N));
		printf("MPI Time 10x= %f seg\n\n", durationPar / 10.0);
		serialMul(durationPar);
		system("pause");
	}
	MPI_Finalize();

}
