#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

#include "aux_functions.h"

#define BILLION 1000000000L

// Função para realizar o ShellSort 
void shellSort(int *arr, int n) {
    // Define o intervalo inicial como metade do tamanho do array
    for (int intervalo = n / 2; intervalo > 0; intervalo /= 2) {
        // Percorre os subarrays com o intervalo atual
        for (int i = intervalo; i < n; i++) {
            // Armazena o elemento atual para comparação
            int temp = arr[i];
            // Move os elementos que são maiores que o elemento armazenado para a frente do array
            int j;
            for (j = i; j >= intervalo && arr[j - intervalo] > temp; j -= intervalo)
                arr[j] = arr[j - intervalo];
            // Insere o elemento armazenado na posição correta
            arr[j] = temp;
        }
    }
}

int main(int argc, char* argv[]){
    char filename[100], order, algorithm_name[] = "shell";
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
    shellSort(numbers, n);
    clock_gettime(CLOCK_MONOTONIC, &end);
    // print_arr(numbers, n);

    diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;

    printf("%s - %s - elapsed time = %llu nanoseconds\n", algorithm_name ,filename, (long long unsigned int) diff);
    write_csv(algorithm_name, order, n, (long long unsigned int) diff);
    
    return 0;
}