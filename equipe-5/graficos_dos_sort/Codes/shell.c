#include <stdio.h>
#include <stdlib.h>

// Função para aplicar o algoritmo Shell Sort
void shellSort(int arr[], int n) {
    for (int gap = n/2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
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
    shellSort(D, D_count);
    shellSort(A, A_count);
    shellSort(O, O_count);

    // Escrevendo números ordenados nos arquivos de saída
    writeNumbersToFile("output/1000000_D_sorted.txt", D, D_count);
    writeNumbersToFile("output/1000000_A_sorted.txt", A, A_count);
    writeNumbersToFile("output/1000000_O_sorted.txt", O, O_count);

    printf("Números organizados e escritos nos arquivos de saída.\n");

    // Liberando a memória alocada
    free(D);
    free(A);
    free(O);

    return 0;
}
