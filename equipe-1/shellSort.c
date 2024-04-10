#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>


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

// Função para imprimir um array
void printArray(int A[], int size, FILE *output_file) {
    for (int i = 0; i < size; i++) {
        fprintf(output_file, "%d,", A[i]);
    }
}

int main() {
    DIR *dir;
    struct dirent *entry;

    // Abre o diretório de entrada
    dir = opendir("inputs");
    if (dir == NULL) {
        printf("Erro ao abrir o diretório de entrada.\n");
        return 1;
    }

    // Cria o diretório de saída se não existir
    //mkdir("outputs");

    // Itera sobre os arquivos no diretório de entrada
    while ((entry = readdir(dir)) != NULL) {
        // Ignora os diretórios '.' e '..'
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Constrói o caminho completo do arquivo
        char filename[100];
        snprintf(filename, sizeof(filename), "inputs/%s", entry->d_name);

        FILE *input_file = fopen(filename, "r");
        if (input_file == NULL) {
            printf("Erro ao abrir o arquivo de entrada: %s\n", filename);
            continue;
        }

        int num_elements = 0;
        int capacity = 10;
        int *arr = (int *)malloc(capacity * sizeof(int));
        if (arr == NULL) {
            printf("Erro de alocação de memória.\n");
            fclose(input_file);
            continue;
        }

        int number;
        while (fscanf(input_file, "%d,", &number) == 1) {
            if (num_elements == capacity) {
                capacity *= 2;
                int *temp = (int *)realloc(arr, capacity * sizeof(int));
                if (temp == NULL) {
                    printf("Erro de realocação de memória.\n");
                    fclose(input_file);
                    free(arr);
                    continue;
                }
                arr = temp;
            }
            arr[num_elements++] = number;
        }

        fclose(input_file);

        // Aplica o Shell Sort
        shellSort(arr, num_elements);

        // Constrói o nome do arquivo de saída
        char output_filename[100];
        snprintf(output_filename, sizeof(output_filename), "outputs/%s_sorted.txt", entry->d_name);

        FILE *output_file = fopen(output_filename, "w");
        if (output_file == NULL) {
            printf("Erro ao abrir o arquivo de saída: %s\n", output_filename);
            free(arr);
            continue;
        }

        // Escreve o array ordenado no arquivo de saída
        printArray(arr, num_elements, output_file);

        fclose(output_file);
        free(arr);
    }

    closedir(dir);

    return 0;
}
