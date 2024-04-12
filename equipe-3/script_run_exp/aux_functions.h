#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int* read_numbers_file(char file_name[], int n);
int count_file_lines(char file_name[]);
void get_path_filename(char* buffer, char* path);
int get_filename_n(char* filename);
char get_filename_order(char* filename);
void write_csv(char* algorithm_name, char order, int n, unsigned long long duration);