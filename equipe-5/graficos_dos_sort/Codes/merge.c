#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Função para combinar duas partes ordenadas de um array
void merge(int arr[], int l, int m, int r) {
    clock_t start = clock(); // Iniciando a contagem do tempo

    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Criando arrays temporários
    int L[n1], R[n2];

    // Copiando dados para os arrays temporários L[] e R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Merge dos arrays temporários de volta em arr[l..r]
    i = 0; // Índice inicial do primeiro subarray
    j = 0; // Índice inicial do segundo subarray
    k = l; // Índice inicial do array mesclado
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copiando os elementos restantes de L[], se houver algum
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copiando os elementos restantes de R[], se houver algum
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    clock_t end = clock(); // Finalizando a contagem do tempo

    double time_spent = (double)(end - start) / CLOCKS_PER_SEC * 1000.0; // Calculando o tempo em milissegundos

    // Escrevendo o tempo de execução
    printf("Tempo de execução (merge): %f ms\n", time_spent);
}

// Função para aplicar o algoritmo Merge Sort
void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        // Chamadas recursivas para as duas metades
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        // Mesclando as duas metades
        merge(arr, l, m, r);
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
    mergeSort(D, 0, D_count - 1);
    mergeSort(A, 0, A_count - 1);
    mergeSort(O, 0, O_count - 1);

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
