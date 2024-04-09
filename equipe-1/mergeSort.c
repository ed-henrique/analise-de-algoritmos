#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>

// Função para mesclar duas sub-arrays de arr[]
// A primeira sub-array é arr[l..m]
// A segunda sub-array é arr[m+1..r]
void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Cria arrays temporários
    int L[n1], R[n2];

    // Copia dados para os arrays temporários L[] e R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Mescla os arrays temporários de volta em arr[l..r]
    i = 0; // Índice inicial da primeira sub-array
    j = 0; // Índice inicial da segunda sub-array
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

    // Copia os elementos restantes de L[], se houver algum
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copia os elementos restantes de R[], se houver algum
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Função para realizar o Merge Sort recursivamente em um array
void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        // Encontra o ponto médio do array
        int m = l + (r - l) / 2;

        // Ordena a primeira metade
        mergeSort(arr, l, m);
        // Ordena a segunda metade
        mergeSort(arr, m + 1, r);

        // Mescla as metades ordenadas
        merge(arr, l, m, r);
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
    mkdir("outputs");

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

        mergeSort(arr, 0, num_elements - 1);

        // Constrói o nome do arquivo de saída
        char output_filename[100];
        snprintf(output_filename, sizeof(output_filename), "outputs/%s_sorted.txt", entry->d_name);

        FILE *output_file = fopen(output_filename, "w");
        if (output_file == NULL) {
            printf("Erro ao abrir o arquivo de saída: %s\n", output_filename);
            free(arr);
            continue;
        }

        printArray(arr, num_elements, output_file);

        fclose(output_file);
        free(arr);
    }

    closedir(dir);

    return 0;
}


