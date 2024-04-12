#include "aux_functions.h"

int* read_numbers_file(char file_name[], int n) {
  int* numbers = (int*)malloc(n * sizeof(int));

  FILE *arq;
  char Linha[100];
  char *result;
  int i;

  arq = fopen(file_name, "rt");

  if (arq == NULL) {
    printf("Problemas na abertura do arquivo\n");
    return NULL;
  }

  i = 1;
  while (!feof(arq)) {
	// Lê uma linha (inclusive com o '\n')
    result = fgets(Linha, 100, arq);  // o 'fgets' lê até 99 caracteres ou até o '\n'
    if (result)  // Se foi possível ler
        // printf("%d ", atoi(Linha));
	    numbers[i-1] = atoi(Linha);
    i++;
  }
  fclose(arq);
  return numbers;
}

void get_path_filename(char* buffer, char* path) {
  int i;
  int filename_i = 0;
  for(i = 0; path[i] != '\0'; i++) if (path[i] == '/') filename_i = i+1;

  for(i = 0; path[i]; i++) buffer[i] = path[filename_i + i];
  buffer[i] = '\0';
}

int get_filename_n(char* filename) {
  int i = 0;
  char str_n[100];
  while (1) {
    if (filename[i] == '\0'){
      printf("error: invalid numbers sequence filename.\n");
      exit(-1);
    }
    if (filename[i++] == '-') break;
  }
  int j = 0;
  while (1) {
    str_n[j++] = filename[i];
    if (filename[i] == '\0'){
      printf("error: invalid numbers sequence filename.\n");
      exit(-1);
    }
    if (filename[i++] == '.') break;
  }
  return atoi(str_n);
}

char get_filename_order(char* filename) {
  if (filename[1] != '-') {
      printf("error: invalid numbers sequence filename.\n");
      exit(-1);
  }
  return filename[0];
}

void write_csv(char* algorithm_name, char order, int n, unsigned long long duration) {
  char filename[] = "log.csv";
  FILE* csv;
  if (!(access("log.csv", F_OK) != -1)) {
    csv = fopen(filename, "w");
    fprintf(csv, "algorithm_name, order, n, duration_ns\n");
  } else {
    csv = fopen(filename, "a");
  }
  fprintf(csv, "%s, %c, %d, %llu\n", algorithm_name, order, n, duration);
}