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
    
    // Abra o arquivo para leitura
    char nome_do_arquivo[1024];
    sprintf(nome_do_arquivo, "%s.txt", argv[1]);
    arquivo = fopen(nome_do_arquivo, "r");

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

    inicio = clock();
    shellsort(array, num_numeros);
    fim = clock();

    tempo_decorrido = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("%.10f\n", tempo_decorrido);

    // Criar o nome do arquivo de saída
    sprintf(nome_arquivo_saida, "%s-ok.txt", argv[1]);

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