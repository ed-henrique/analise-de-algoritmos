#include <stdio.h>
#include <stdlib.h>

int* read_numbers_file(char file_name[], int n_numbers) {
  int* numbers = (int*)malloc(n_numbers * sizeof(int));

  FILE *arq;
  char Linha[100];
  char *result;
  int i;

  // Abre um arquivo TEXTO para LEITURA
  arq = fopen(file_name, "rt");

  if (arq == NULL)  // Se houve erro na abertura
  {
    printf("Problemas na abertura do arquivo\n");
    return NULL;
  }

  i = 1;
  while (!feof(arq))
  {
	// Lê uma linha (inclusive com o '\n')
    result = fgets(Linha, 100, arq);  // o 'fgets' lê até 99 caracteres ou até o '\n'
    if (result)  // Se foi possível ler
	    numbers[i-1] = atoi(Linha);
    i++;
  }
  fclose(arq);
  return numbers;
}

void print_numbers(int* v, int n){
  
  for (int i=0; i<n;i++) printf("%d ", v[i]);
  printf("\n");
}

int main() {
  int n_numbers = 100;

  char a_file_name[] = "o-100.txt";
  int* a_numbers = read_numbers_file("a-100.txt", n_numbers);
  int* d_numbers = read_numbers_file("d-100.txt", n_numbers);
  int* o_numbers = read_numbers_file("o-100.txt", n_numbers);

  printf("Unordered numbers: ");
  print_numbers(a_numbers, n_numbers);
  printf("Ordered numbers: ");
  print_numbers(o_numbers, n_numbers);
  printf("Reverse ordered numbers: ");
  print_numbers(d_numbers, n_numbers);

  free(a_numbers);
  free(d_numbers);
  free(o_numbers);
  return 0;
}