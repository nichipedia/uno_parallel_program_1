#include <stdio.h>
#include <omp.h>
#include <time.h>

int main() {
    time_t time1;
    time(&time1);

    #pragma omp parallel num_threads(10)
    {
        int num_threads = omp_get_thread_num();
        int total_threads = omp_get_num_threads();
        printf("Thread: %d, Total Threads: %d\n", num_threads, total_threads);
	    printf("Hello World!\n");
    }
    time_t time2;
    time(&time2);
    double length = difftime(&time1, &time2);
    printf("%f\n", length);
	return 0;	
} 
