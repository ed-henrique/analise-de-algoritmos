#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>

// Função para realizar o ShellSort 
void shellSort(int arr[], int n) {
    // Inicia com o intervalo grande e o reduz gradualmente
    for (int intervalo = n / 2; intervalo > 0; intervalo /= 2) {
        // Realiza a inserção do intervalo-sorted para este intervalo
        for (int i = intervalo; i < n; i += 1) {
            int temp = arr[i];
            int j;
            for (j = i; j >= intervalo && arr[j - intervalo] > temp; j -= intervalo)
                arr[j] = arr[j - intervalo];
            arr[j] = temp;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <caminho_para_arquivo_de_entrada>\n", argv[0]);
        return -1;
    }

    FILE *inputFile, *outputFile;
    char *inputFileName = argv[1];
    int *arr;
    int n = 0;
    
    
    // Abre o arquivo de entrada
    inputFile = fopen(inputFileName, "r");
    if (inputFile == NULL) {
        perror("Erro ao abrir o arquivo de entrada");
        return -1;
    }
    
    // Lê o numero de linhas do arquivo de entrada
    int num;
    while (fscanf(inputFile, "%d", &num) == 1) {
        n++;
    }
     
    //define o nome do arquivo de saída de forma dinamica so com o numero de linhas que fora ordenado sempre na pasta outputs
    char outputFileName[100] = "outputs/";
    strcat(outputFileName, "sorted_");
    char numStr[10];
    sprintf(numStr, "%d", n);
    strcat(outputFileName, numStr);
    strcat(outputFileName, ".txt");
    
    // Aloca memória para o array
    arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }
    
    // Lê os números do arquivo de entrada e adiciona ao array
    for (int i = 0; i < n; i++) {
        fscanf(inputFile, "%d", &arr[i]);
    }
    
    // Fecha o arquivo de entrada
    fclose(inputFile);

    // Inicia o timer
    struct timeval start, end;
    gettimeofday(&start, NULL);

    // Chama o algoritmo de ordenação shellSort
    shellSort(arr, n);

    // Termina o timer
    gettimeofday(&end, NULL);

    // Calcula o tempo de execução em segundos
    double elapsedTime = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;

    // Abre o arquivo de saída
    outputFile = fopen(outputFileName, "w");
    if (outputFile == NULL) {
        perror("Erro ao criar o arquivo de saída");
        return -1;
    }

    // Escreve os números ordenados no arquivo de saída
    for (int i = 0; i < n; i++) {
        fprintf(outputFile, "%d\n", arr[i]);
    }

    // Fecha o arquivo de saída
    fclose(outputFile);
    
    // Libera a memória alocada para o array
    free(arr);
    
    // Imprime o tempo de execução
    printf("%.6f", elapsedTime);

    return 0;
}