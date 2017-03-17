#include <stdio.h>
#include <omp.h>

void main()
{
	// #pragma omp parallel
	#pragma omp parallel num_threads(100)
	// observamos un límite: 64. En este caso cada núcleo a lo más va a ejecutar 8 hilos
	// el límite tiene que ver con la máquina
	{
		int id = omp_get_thread_num(); // indica el id del núcleo donde se está ejecutando
		int thread_count = omp_get_num_threads();
		printf("Hello from the thread %d of %d \n", id, thread_count);
	}
}

/*
const int num_elements = 10;
double a[num_elements];

void Square(int id, double a[])
{
	int i;
	printf("thread id: %d\n", id);
	for (i = 0; i < num_elements; i++)
	{
		a[i] *= a[i];
		printf("a[%d] from Thread %d: %d\n", i, id, a[i]);
	}
}

void main(void) {

#pragma omp parallel num_threads(4)
	{
		int id = omp_get_thread_num();
		Square(id, a);
	}
	printf("all done\n");
}*/
