#include <stdio.h>
#include <omp.h>
#include <time.h>

int main() {
    #pragma omp parallel num_threads(10)
    {
        int num_threads = omp_get_thread_num();
        printf("Hello from Thread: %d\n", num_threads);
    }
	return 0;	
} 
