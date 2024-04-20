#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include "aux_functions.h"

#define BILLION 1000000000L

// Estrutura de um nó da árvore
typedef struct Node {
    int data;
    char color; // 'R' para vermelho, 'B' para preto
    struct Node *parent;
    struct Node *left;
    struct Node *right;
} Node;

// Função auxiliar para criar um novo nó
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Erro ao alocar memória para o novo nó.\n");
        exit(1);
    }
    newNode->data = data;
    newNode->color = 'R'; // Por padrão, novo nó é vermelho
    newNode->parent = NULL;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Função para realizar uma rotação à esquerda
void leftRotate(Node **root, Node *x) {
    Node *y = x->right;
    x->right = y->left;
    if (y->left != NULL)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL)
        *root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

// Função para realizar uma rotação à direita
void rightRotate(Node **root, Node *y) {
    Node *x = y->left;
    y->left = x->right;
    if (x->right != NULL)
        x->right->parent = y;
    x->parent = y->parent;
    if (y->parent == NULL)
        *root = x;
    else if (y == y->parent->right)
        y->parent->right = x;
    else
        y->parent->left = x;
    x->right = y;
    y->parent = x;
}

// Função para corrigir violações das propriedades da árvore rubro-negra após inserção
void fixViolation(Node **root, Node *newNode) {
    Node *parent = NULL;
    Node *grandparent = NULL;
    while (newNode != *root && newNode->color != 'B' && newNode->parent->color == 'R') {
        parent = newNode->parent;
        grandparent = newNode->parent->parent;
        if (parent == grandparent->left) {
            Node *uncle = grandparent->right;
            if (uncle != NULL && uncle->color == 'R') {
                grandparent->color = 'R';
                parent->color = 'B';
                uncle->color = 'B';
                newNode = grandparent;
            } else {
                if (newNode == parent->right) {
                    leftRotate(root, parent);
                    newNode = parent;
                    parent = newNode->parent;
                }
                rightRotate(root, grandparent);
                char temp = parent->color;
                parent->color = grandparent->color;
                grandparent->color = temp;
                newNode = parent;
            }
        } else {
            Node *uncle = grandparent->left;
            if (uncle != NULL && uncle->color == 'R') {
                grandparent->color = 'R';
                parent->color = 'B';
                uncle->color = 'B';
                newNode = grandparent;
            } else {
                if (newNode == parent->left) {
                    rightRotate(root, parent);
                    newNode = parent;
                    parent = newNode->parent;
                }
                leftRotate(root, grandparent);
                char temp = parent->color;
                parent->color = grandparent->color;
                grandparent->color = temp;
                newNode = parent;
            }
        }
    }
    (*root)->color = 'B';
}

// Função para inserir um novo nó na árvore rubro-negra
void insert(Node **root, int data) {
    Node *newNode = createNode(data);
    Node *parent = NULL;
    Node *current = *root;
    while (current != NULL) {
        parent = current;
        if (newNode->data < current->data)
            current = current->left;
        else
            current = current->right;
    }
    newNode->parent = parent;
    if (parent == NULL)
        *root = newNode;
    else if (newNode->data < parent->data)
        parent->left = newNode;
    else
        parent->right = newNode;
    fixViolation(root, newNode);
}

// Função auxiliar para imprimir a árvore rubro-negra em ordem
void inOrder(Node *root) {
    if (root == NULL)
        return;
    inOrder(root->left);
    printf("%d%c ", root->data, root->color);
    inOrder(root->right);
}

int main(int argc, char* argv[]) {



    /////////////////////////////////////////////////////////////////////////////
    char filename[100], order, algorithm_name[] = "rubro_negro";
    int n;

    // search filename:
    get_path_filename(filename, argv[1]);

    // get execution variables:
    n = get_filename_n(filename);
    order = get_filename_order(filename);
    
    // read sequence from file:
    int* numbers = read_numbers_file(argv[1], n);


    Node *root = NULL;



    // measure execution time:
    uint64_t diff;
    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC, &start);
    

    for (int i = 0; i < n; i++) {
        insert(&root, numbers[i]);
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    print_arr(numbers, n);

    diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;

    printf("%s - %s - elapsed time = %llu nanoseconds\n", algorithm_name ,filename, (long long unsigned int) diff);
    write_csv(algorithm_name, order, n, (long long unsigned int) diff);

    // printf("Árvore rubro-negra em ordem: ");
    // inOrder(root);
    // printf("\n");
    
    free(numbers);
    return 0;
}
