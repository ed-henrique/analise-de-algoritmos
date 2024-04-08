#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

int main(int argc, char* argv[]) {
    clock_t inicio, fim;
    double tempo_decorrido;
    FILE *arquivo;
    FILE *arquivo_ordenado;
    int *array;
    int num_numeros = 0;
    char nome_arquivo_saida[100];
    
    
    char nome_do_arquivo[1024];
    sprintf(nome_do_arquivo, "%s.txt", argv[1]);
    arquivo = fopen(nome_do_arquivo, "r");

    
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    
    int num;
    while (fscanf(arquivo, "%d", &num) == 1) {
        num_numeros++;
    }

    
    array = (int*)malloc(num_numeros * sizeof(int));
    if (array == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    
    rewind(arquivo);

    
    for (int i = 0; i < num_numeros; i++) {
        fscanf(arquivo, "%d", &array[i]);
    }

    
    fclose(arquivo);
    
    // Ordenar o array usando o Quick Sort
    inicio = clock();
    quickSort(array, 0, num_numeros - 1);
    fim = clock();

    tempo_decorrido = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("%.10f\n", tempo_decorrido);
    
    sprintf(nome_arquivo_saida, "%s-ok.txt", "inputs/D-5000");

    
    arquivo_ordenado = fopen(nome_arquivo_saida, "w");

    if (arquivo_ordenado == NULL) {
        printf("Erro ao abrir o arquivo de saída.\n");
        return 1;
    }

    
    for (int i = 0; i < num_numeros; i++) {
        fprintf(arquivo_ordenado, "%d\n", array[i]);
    }

    
    fclose(arquivo_ordenado);
    free(array);

    return 0;
}
