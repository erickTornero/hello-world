#include <stdio.h>
#include <omp.h> 
#include <cstdlib>
#define N 10

void main()
{
	double avg = 0.0, a[N];

	int i;
	for (i = 0; i < N; i++)
	{
		a[i] = (double)i;
		printf("a[i]: %d  ", a[i]);
	}

#pragma omp parallel for num_threds(10) reduction(+:avg)
	for (i = 0; i < N; i++)
	{
		avg += a[i];
		printf("Thread: %d \n", omp_get_thread_num());
	}
	avg = avg / N;
	printf("Average = %f \n", avg);

	system("PAUSE");
}
