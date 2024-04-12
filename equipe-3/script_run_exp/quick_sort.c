#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

#include "aux_functions.h"


#define BILLION 1000000000L


// Function to swap two elements 
void swap(int* a, int* b) 
{ 
    int temp = *a; 
    *a = *b; 
    *b = temp; 
} 
  
// Partition function 
int partition(int *arr, int low, int high) 
{ 
  
    // initialize pivot to be the first element 
    int pivot = arr[low]; 
    int i = low; 
    int j = high; 
  
    while (i < j) { 
  
        // condition 1: find the first element greater than 
        // the pivot (from starting) 
        while (arr[i] <= pivot && i <= high - 1) { 
            i++; 
        } 
  
        // condition 2: find the first element smaller than 
        // the pivot (from last) 
        while (arr[j] > pivot && j >= low + 1) { 
            j--; 
        } 
        if (i < j) { 
            swap(&arr[i], &arr[j]); 
        } 
    } 
    swap(&arr[low], &arr[j]); 
    return j; 
} 
  
// QuickSort function 
void quickSort(int *arr, int low, int high) 
{ 
    if (low < high) { 
  
        // call Partition function to find Partition Index 
        int partitionIndex = partition(arr, low, high); 
  
        // Recursively call quickSort() for left and right 
        // half based on partition Index 
        quickSort(arr, low, partitionIndex - 1); 
        quickSort(arr, partitionIndex + 1, high); 
    } 
} 
  

int main(int argc, char* argv[]){
    char filename[100], order, algorithm_name[] = "quick";
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
    
    free(numbers);
    return 0;
}