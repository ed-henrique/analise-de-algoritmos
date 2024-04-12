#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

#include "aux_functions.h"


#define BILLION 1000000000L

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int* arr, int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int* arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main(int argc, char* argv[]){
    char filename[100], order, algorithm_name[] = "quick_sort";
    int n;

    // search filename:
    get_path_filename(filename, argv[1]);

    // get execution variables:
    n = get_filename_n(filename);
    order = get_filename_order(filename);
    
    // read sequence from file:
    int* numbers = read_numbers_file(argv[1], n);

    // measure execution time:
    uint64_t diff;
    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC, &start);
    quickSort(numbers, 0, n - 1);
    clock_gettime(CLOCK_MONOTONIC, &end);

    diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;

    printf("%s - %s - elapsed time = %llu nanoseconds\n", algorithm_name ,filename, (long long unsigned int) diff);
    write_csv(algorithm_name, order, n, (long long unsigned int) diff);
    
    return 0;
}