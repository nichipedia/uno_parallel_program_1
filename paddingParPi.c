#include <stdio.h>
#include <omp.h>

static long num_steps = 100000000;
double step;
#define PAD 8
#define NUM_THREADS 8

int main() {
    int threads[19];
    int j;
    for (j = 0; j < 19; j++) {
        threads[j] = j+2;
    }
    int i;
    int nthreads;
    double pi;
    int k;
    printf("PI, Threads, Time\n");
    for (k = 0; k < 19; k++) {
        double start = omp_get_wtime();
        double sum[threads[k]][PAD];
        step = 1.0/(double)num_steps;
        omp_set_num_threads(threads[k]);
        #pragma omp parallel
        {
            int i, id, nthrds;
            double x;
            id = omp_get_thread_num();
            nthrds = omp_get_num_threads();
            if (id == 0) {
                nthreads = nthrds;
            }
            for (i=id, sum[id][0]=0.0; i<num_steps; i += nthrds) {
                x = (i+0.5)*step;
                sum[id][0] += 4.0/(1.0+x*x);
            }
        }
        for (i=0, pi=0.0; i<nthreads; i++) {
            pi += sum[i][0]*step;
        }
        double end = omp_get_wtime();
        double time = end-start;
        printf("%f, %d, %f\n", pi, threads[k], time);
    }
    return 0;
}
