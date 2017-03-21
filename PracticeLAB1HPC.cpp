#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
static long n = 1000000000;
double dx;
double funcionPI(double x);
void main(void)
{
	int i;
	double x, pi, sum = 0.0;
	double start_time, run_time;
	double approx;
	start_time = omp_get_wtime();
	dx = 1.0 / (double)n;

	// Your code here...
	approx = (funcionPI(0.0) + funcionPI(1.0)) / 2.0;
	for (i = 1; i <= n - 1; i++)
	{
		x = i*dx;
		sum += funcionPI(x);
	}
	pi = sum*dx;
	run_time = omp_get_wtime() - start_time;
	printf("Pi with %d steps is %f calculated in %f seconds\n", n, pi, run_time);
	system("PAUSE");

	////MI CODE PARALLEL
	start_time = omp_get_wtime();
	dx = 1.0 / (double)n;
	sum = 0.0;
	// Your code here...
	approx = (funcionPI(0.0) + funcionPI(1.0)) / 2.0;
#pragma omp parallel for num_threads(64) reduction(+:sum)
	for (i = 1; i <= n - 1; i++)
	{
		x = i*dx;
		sum += funcionPI(x);
	}
	pi = sum*dx;
	run_time = omp_get_wtime() - start_time;
	printf("Pi with %d steps is %f calculated in %f seconds\n", n, pi, run_time);
	system("PAUSE");
	//FINISH CODE PARALLEL
}

double funcionPI(double x)
{
	double fx = 4.0 / (1.0 + x*x);
	return fx;
}
