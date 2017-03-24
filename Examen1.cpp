#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "omp.h"

int main()
{
	int i, j, ID, nthreads;
#pragma omp parallel private(i,j,ID)
	{
		for (i = 0; i < 1000; i++)
		{
			for (j = 0; j < 1000; j++)
			{
				ID = omp_get_thread_num();
			}

		}
		printf("Thread %d : My value of ID is %d .\n", omp_get_thread_num(), ID);
	}
	system("PAUSE");
	return 0;
}
