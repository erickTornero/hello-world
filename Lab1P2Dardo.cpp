//Cálculo de PI a travez de números aleatorios usando el método de montecarlo
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
static long numTrials = 100000000;

void Pi_serial()
{
	long i, numCirc;
	double x, pi, y;
	double start_time, run_time = 0.0;
	double distance;
	printf("Running serial version 10x ...\n");

	for (int q = 1; q <= 10; q++)
	{
		numCirc = 0;
		srand((unsigned)time(NULL));
		start_time = omp_get_wtime();

		// Your serial code here...
		numCirc = 0;
		for (i = 0; i < numTrials; i++)
		{
			x = 2*((double)rand()/RAND_MAX)-1;
			y = 2 * ((double)rand() / RAND_MAX) - 1;
			distance = sqrt(x*x + y*y);
			if (distance <= 1)
			{
				numCirc++;
			}
		}
		pi = 4.0 * numCirc /(double) numTrials;

		run_time += omp_get_wtime() - start_time;
		printf("Pi with %d trials is : %f in : %f seconds. \n\n", numTrials, pi, run_time);
	}
	printf("Pi with %d trials is : %f in : %f seconds. \n\n", numTrials, pi, run_time / 10.0);
}

void Pi_Paralelo(int NUM_THREADS)
{
	long i, numCirc;
	double x, pi, y;
	double start_time, run_time = 0.0;
	double distance;
	printf("Running parallel version 10x ...\n");

	for (int q = 1; q <= 10; q++)
	{
		numCirc = 0;
		srand((unsigned)time(NULL));
		start_time = omp_get_wtime();

		// Your parallel code here...
		numCirc = 0;
#pragma oem parallel for num_Threads(NUM_THREADS) reduction(+:numCirc)
		for (i = 0; i < numTrials; i++)
		{
			x = 2 * ((double)rand() / RAND_MAX) - 1;
			y = 2 * ((double)rand() / RAND_MAX) - 1;
			distance = sqrt(x*x + y*y);
			if (distance <= 1)
			{
				numCirc++;
			}
		}
		pi = 4.0 * numCirc / (double)numTrials;

		run_time += omp_get_wtime() - start_time;
		printf("Pi with %d trials is : %f in : %f seconds. \n\n", numTrials, pi, run_time);
	}
	printf("Pi with %d trials and %d threads is : %f in : %f seconds. \n\n", numTrials, NUM_THREADS, pi, run_time / 10.0);

}

void main()
{
	printf("Introduccion a la Computacion de Alto Rendimiento \n");
	printf("             Laboratorio 1 - OpenMP \n\n");
	printf("Pregunta 2: Calculo del valor de Pi por el metodo de Monte Carlo: \n\n");

	Pi_serial();			// Version Serial
	for (int i = 2; i <= 8; i++)
	{
		Pi_Paralelo(i);		// Version Paralela
	}
}
