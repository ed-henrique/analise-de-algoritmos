#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void shellsort(int arr[], int num) {
    int i, j, k, tmp;
    for (i = num / 2; i > 0; i /= 2) {
        for (j = i; j < num; j++) {
            for (k = j - i; k >= 0; k -= i) {
                if (arr[k + i] >= arr[k])
                    break;
                else {
                    tmp = arr[k];
                    arr[k] = arr[k + i];
                    arr[k + i] = tmp;
                }
            }
        }
    }
}

int main(int argc, char* argv[]) {
    clock_t inicio, fim;
    double tempo_decorrido;
    FILE *arquivo;
    FILE *arquivo_ordenado;
    int *array;
    int num_numeros = 0;
    int i;
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

    // Ordenar o array usando o Shell Sort
    inicio = clock();
    shellsort(array, num_numeros);
    fim = clock();

    tempo_decorrido = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("%.10f\n", tempo_decorrido);

    sprintf(nome_arquivo_saida, "%s-ok.txt", argv[1]);

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