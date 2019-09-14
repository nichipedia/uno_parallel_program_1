#include <stdio.h>
#include <time.h>

static long num_steps = 100000000;
double step;
int main() {
    double time = 0.0;
    clock_t start = clock();
    int i; double x, pi, sum = 0.0;
    step = 1.0/(double) num_steps;
    for (i = 0; i < num_steps; i++) {
        x = (i+0.5)*step;
        sum = sum + 4.0/(1.0 + x*x);
    }
    pi = step*sum;
    clock_t end = clock();
    time += (double)(end-start) / CLOCKS_PER_SEC;
    printf("PI:%f in %f\n", pi, time);
    return 0;
}
