#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10000000
#define ITERATIONS 5

double diff_in_ms(struct timespec start, struct timespec end) {
    return (end.tv_sec - start.tv_sec) * 1000.0 +
           (end.tv_nsec - start.tv_nsec) / 1000000.0;
}

int main() {
    int *array = malloc(SIZE * sizeof(int));
    if (array == NULL) {
        printf("Error al asignar memoria\n");
        return 1;
    }

    for (int i = 0; i < SIZE; i++) {
        array[i] = 0;
    }

    struct timespec start, end;
    double sequential_time = 0.0;
    double random_time = 0.0;

    srand(time(NULL));

    for (int k = 0; k < ITERATIONS; k++) {
        clock_gettime(CLOCK_MONOTONIC, &start);

        for (int i = 0; i < SIZE; i++) {
            array[i]++;
        }

        clock_gettime(CLOCK_MONOTONIC, &end);
        sequential_time += diff_in_ms(start, end);
    }

    for (int k = 0; k < ITERATIONS; k++) {
        clock_gettime(CLOCK_MONOTONIC, &start);

        for (int i = 0; i < SIZE; i++) {
            int index = rand() % SIZE;
            array[index]++;
        }

        clock_gettime(CLOCK_MONOTONIC, &end);
        random_time += diff_in_ms(start, end);
    }

    printf("Promedio acceso secuencial: %.3f ms\n", sequential_time / ITERATIONS);
    printf("Promedio acceso aleatorio: %.3f ms\n", random_time / ITERATIONS);

    free(array);
    return 0;
}
