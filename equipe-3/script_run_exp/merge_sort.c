#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

#include "aux_functions.h"

#define BILLION 1000000000L

// Função para intercalar duas sub-arrays de arr[] // A primeira sub-array é arr[l..m] // A segunda sub-array é arr[m+1..r]

void intercalar(int *arr, int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Cria arrays temporários
    int *esq = (int *)malloc(n1 * sizeof(int));
    int *dir = (int *)malloc(n2 * sizeof(int));

    // Copia dados para os arrays temporários esq[] e dir[]
    for (i = 0; i < n1; i++)
        esq[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        dir[j] = arr[m + 1 + j];

    // Mescla os arrays temporários de volta em arr[l..r]
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (esq[i] <= dir[j]) {
            arr[k] = esq[i];
            i++;
        } else {
            arr[k] = dir[j];
            j++;
        }
        k++;
    }

    // Copia os elementos restantes de esq[], se houver algum
    while (i < n1) {
        arr[k] = esq[i];
        i++;
        k++;
    }

    // Copia os elementos restantes de dir[], se houver algum
    while (j < n2) {
        arr[k] = dir[j];
        j++;
        k++;
    }

    // Libera a memória dos arrays temporários
    free(esq);
    free(dir);
}

// Função para realizar o Merge Sort recursivamente em um array
void mergeSort(int *arr, int l, int r) {
    if (l < r) {
        // Encontra o ponto médio do array
        int m = l + (r - l) / 2;

        // Ordena a primeira metade
        mergeSort(arr, l, m);
        // Ordena a segunda metade
        mergeSort(arr, m + 1, r);

        // Mescla as metades ordenadas
        intercalar(arr, l, m, r);
    }
}

int main(int argc, char* argv[]){
    char filename[100], order, algorithm_name[] = "merge";
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
    mergeSort(numbers, 0, n-1);
    clock_gettime(CLOCK_MONOTONIC, &end);
    print_arr(numbers, n);

    diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;

    printf("%s - %s - elapsed time = %llu nanoseconds\n", algorithm_name ,filename, (long long unsigned int) diff);
    write_csv(algorithm_name, order, n, (long long unsigned int) diff);
    
    return 0;
}