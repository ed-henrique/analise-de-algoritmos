#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = (int*)malloc(n1 * sizeof(int));
    int *R = (int*)malloc(n2 * sizeof(int));

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;

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

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

int main(int argc, char* argv[]) {
    clock_t inicio, fim;
    double tempo_decorrido;
    FILE *arquivo;
    int *array;
    int num_numeros = 0;
    int i;
    
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

    // Ordenar o array usando o Merge Sort
    inicio = clock();
    mergeSort(array, 0, num_numeros - 1);
    fim = clock();
    
    tempo_decorrido = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("%.10f\n", tempo_decorrido);
    free(array);

    return 0;
}
