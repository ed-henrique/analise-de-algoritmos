#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int array[], int low, int high) {
    int pivot = array[high];
    int i = (low - 1);

    for (int j = low; j < high; j++) {
        if (array[j] <= pivot) {
            i++;
            swap(&array[i], &array[j]);
        }
    }

    swap(&array[i + 1], &array[high]);
    return (i + 1);
}

void quickSort(int array[], int low, int high) {
    if (low < high) {
        int pi = partition(array, low, high);
        quickSort(array, low, pi - 1);
        quickSort(array, pi + 1, high);
    }
}

int main() {
    FILE *arquivo;
    FILE *arquivo_ordenado;
    int *array;
    int num_numeros = 0;
    char nome_arquivo_saida[100];
    
    // Abra o arquivo para leitura
    arquivo = fopen("inputs/D-5000.txt", "r");

    // Verifique se o arquivo foi aberto corretamente
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    // Contar quantos números estão no arquivo
    int num;
    while (fscanf(arquivo, "%d", &num) == 1) {
        num_numeros++;
    }

    // Alocar memória para o array
    array = (int*)malloc(num_numeros * sizeof(int));
    if (array == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    // Voltar ao início do arquivo
    rewind(arquivo);

    // Ler os números do arquivo e armazená-los no array
    for (int i = 0; i < num_numeros; i++) {
        fscanf(arquivo, "%d", &array[i]);
    }

    // Fechar o arquivo
    fclose(arquivo);
    
    // Ordenar o array usando o Quick Sort
    quickSort(array, 0, num_numeros - 1);

    // Criar o nome do arquivo de saída
    sprintf(nome_arquivo_saida, "%s-ok.txt", "inputs/D-5000");

    // Abrir o arquivo de saída
    arquivo_ordenado = fopen(nome_arquivo_saida, "w");

    // Verifique se o arquivo de saída foi aberto corretamente
    if (arquivo_ordenado == NULL) {
        printf("Erro ao abrir o arquivo de saída.\n");
        return 1;
    }

    // Escrever os números ordenados no arquivo de saída
    for (int i = 0; i < num_numeros; i++) {
        fprintf(arquivo_ordenado, "%d\n", array[i]);
    }

    // Fechar o arquivo de saída
    fclose(arquivo_ordenado);

    // Liberar memória alocada para o array
    free(array);

    return 0;
}
