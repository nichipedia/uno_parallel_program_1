#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *doTheThing(void *ptr) {
    int id = (int)ptr;
    printf("Hello from Thread %d\n", id);
}

int main() {
    pthread_t threads[10];

    for (int i = 0; i < 10; i++) {
        pthread_create(&threads[i], NULL, doTheThing, (void *)i);
    }
    pthread_exit(NULL);
    return 0;
}
