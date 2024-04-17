#include <stdio.h>
#include <stdlib.h>

// Função para trocar dois elementos de posição em um array
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Função para escolher o pivô e particionar o array
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

// Função para aplicar o algoritmo Quick Sort
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Função para ler números de um arquivo e armazená-los em um array
int readNumbersFromFile(char *filename, int **arr) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo %s\n", filename);
        exit(1);
    }

    int count = 0;
    int num;
    *arr = malloc(sizeof(int) * 5000000); // Alocando espaço para até 5.000.000 de números
    if (*arr == NULL) {
        printf("Erro de alocação de memória.\n");
        exit(1);
    }

    while (fscanf(file, "%d", &num) != EOF && count < 5000000) {
        (*arr)[count++] = num;
    }

    fclose(file);
    return count;
}

// Função para escrever números ordenados em um arquivo
void writeNumbersToFile(char *filename, int arr[], int n) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo %s\n", filename);
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        fprintf(file, "%d\n", arr[i]);
    }

    fclose(file);
}

int main() {
    int *D, *A, *O;
    int D_count, A_count, O_count;

    // Lendo números dos arquivos
    D_count = readNumbersFromFile("inputs/D.txt", &D);
    A_count = readNumbersFromFile("inputs/A.txt", &A);
    O_count = readNumbersFromFile("inputs/O.txt", &O);

    // Ordenando os números
    quickSort(D, 0, D_count - 1);
    quickSort(A, 0, A_count - 1);
    quickSort(O, 0, O_count - 1);

    // Escrevendo números ordenados nos arquivos de saída
    writeNumbersToFile("output/5000000_D_sorted.txt", D, D_count);
    writeNumbersToFile("output/5000000_A_sorted.txt", A, A_count);
    writeNumbersToFile("output/5000000_O_sorted.txt", O, O_count);

    printf("Números organizados e escritos nos arquivos de saída.\n");

    // Liberando a memória alocada
    free(D);
    free(A);
    free(O);

    return 0;
}
