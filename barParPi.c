#include <stdio.h>
#include <omp.h>

static long num_steps = 100000000;
double step;
#define NUM_THREADS 4
int main() {
    int threads[19];
    int j;
    for (j = 0; j < 19; j++) {
        threads[j] = j+2;
    }

    int i, k, nthreads; 
    double time = 0.0;
    step = 1.0/(double) num_steps;
    printf("PI, Threads, Time\n");
    for (k = 0; k < 19; k++) {
        double start = omp_get_wtime();
        omp_set_num_threads(threads[k]);
        double pi = 0.0;
        #pragma omp parallel
        {
            int i, id, nthrds;
            double x, sum;
            id = omp_get_thread_num();
            nthrds = omp_get_num_threads();
            if (id==0) nthreads = nthrds;
            for (i = id, sum=0.0; i < num_steps; i=i+nthrds) {
                x = (i+0.5)*step;
                sum += 4.0/(1.0 + x*x);
            }
            #pragma omp critical
            {
                pi += sum * step;
            }
        }
        double end = omp_get_wtime();
        time = (end-start);
        printf("%f, %d, %f\n", pi, threads[k], time);
    }
    return 0;
}
