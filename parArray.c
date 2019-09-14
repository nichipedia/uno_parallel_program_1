#include <stdio.h>
#include <omp.h>

static int array[20][100];

int main() {
    int threads[19];
    int j, k;
    for (j = 0; j < 19; j++) {
        threads[j] = j+2;
    }
    int total = 20*100;
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 100; j++) {
            array[i][j] = i*j;
        }
    }
    printf("Sum, Mean, Threads, Time\n");
    for (k = 0; k < 19; k++) {
        int sum = 0;
        double start = omp_get_wtime();
        omp_set_num_threads(threads[k]);
        #pragma omp do schedule(dynamic) 
        {
            #pragma parellel for collapse(2) reduction(+:sum)
            {
                for (int i = 0; i < 20; i++) {
                    for (int j = 0; j < 100; j++) {
                        sum += array[i][j];
                    }
                }
            }
        }
        double end = omp_get_wtime();
        double time = end-start;
        double mean = sum/(double)(20*100);
        printf("%d, %f, %d, %f\n", sum, mean, threads[k], time);
    }
    return 0;
}
