#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
 
int fib(int);
 
int main() {
    int n = 30;
    int threads[19];
    int j;
    for (j = 0; j < 19; j++) {
        threads[j] = j+2;
    }
    int result;
    int i;
    printf("Fib, Threads, Time\n");
    for (i = 0; i < 19; i++) {
        #pragma omp parallel num_threads(threads[i])
        {
            #pragma omp single
            {
                int total = omp_get_num_threads();
                double start = omp_get_wtime();
                int result = fib(n);
                double end = omp_get_wtime();
                double time = end-start;
                printf("%d, %d, %f\n", result, total, time);
            }
        }
    }
}
 
int fib(int n) {
    int i, j, id;
    if (n < 2) {
        return n;
    }
 
    #pragma omp task shared(i) private(id)
    {
        i = fib(n-1);
    }
 
    #pragma omp task shared(j) private(id)
    {
        j = fib(n-2);
    }
 
    #pragma omp taskwait
    {
        return (i+j);
    }
}

