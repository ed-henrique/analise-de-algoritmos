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
    int* stack = (int*)malloc((high - low + 1) * sizeof(int));
    int top = -1;

    stack[++top] = low;
    stack[++top] = high;

    while (top >= 0) {
        high = stack[top--];
        low = stack[top--];

        int pi = partition(array, low, high);

        if (pi - 1 > low) {
            stack[++top] = low;
            stack[++top] = pi - 1;
        }

        if (pi + 1 < high) {
            stack[++top] = pi + 1;
            stack[++top] = high;
        }
    }

    free(stack);
}

int main(int argc, char* argv[]) {
    clock_t inicio, fim;
    double tempo_decorrido;
    FILE *arquivo;
    int *array;
    int num_numeros = 0;
    
    
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

    free(array);

    return 0;
}
