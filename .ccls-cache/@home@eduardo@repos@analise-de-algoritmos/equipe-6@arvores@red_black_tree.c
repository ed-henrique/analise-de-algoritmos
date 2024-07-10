#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum { RED, BLACK } Color;

typedef struct Node {
    int data;
    Color color;
    struct Node *left, *right, *parent;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->color = RED;  // New nodes are always RED
    newNode->left = newNode->right = newNode->parent = NULL;
    return newNode;
}

Node* bstInsert(Node* root, Node* newNode) {
    if (root == NULL) return newNode;

    if (newNode->data < root->data) {
        root->left = bstInsert(root->left, newNode);
        root->left->parent = root;
    } else if (newNode->data > root->data) {
        root->right = bstInsert(root->right, newNode);
        root->right->parent = root;
    }

    return root;
}

Node* rotateLeft(Node* root, Node* x) {
    Node* y = x->right;
    x->right = y->left;

    if (x->right != NULL)
        x->right->parent = x;

    y->parent = x->parent;

    if (x->parent == NULL)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;

    return root;
}

Node* rotateRight(Node* root, Node* y) {
    Node* x = y->left;
    y->left = x->right;

    if (x->right != NULL)
        x->right->parent = y;

    x->parent = y->parent;

    if (y->parent == NULL)
        root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    x->right = y;
    y->parent = x;

    return root;
}

void fixViolation(Node** root, Node* pt) {
    Node* parent_pt = NULL;
    Node* grand_parent_pt = NULL;

    while ((pt != *root) && (pt->color != BLACK) &&
           (pt->parent->color == RED)) {

        parent_pt = pt->parent;
        grand_parent_pt = pt->parent->parent;

        /* Case : A
           Parent of pt is left child of Grand-parent of pt */
        if (parent_pt == grand_parent_pt->left) {

            Node* uncle_pt = grand_parent_pt->right;

            /* Case : 1
               The uncle of pt is also red
               Only Recoloring required */
            if (uncle_pt != NULL && uncle_pt->color == RED) {
                grand_parent_pt->color = RED;
                parent_pt->color = BLACK;
                uncle_pt->color = BLACK;
                pt = grand_parent_pt;
            } else {
                /* Case : 2
                   pt is right child of its parent
                   Left-rotation required */
                if (pt == parent_pt->right) {
                    *root = rotateLeft(*root, parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }

                /* Case : 3
                   pt is left child of its parent
                   Right-rotation required */
                *root = rotateRight(*root, grand_parent_pt);
                Color temp = parent_pt->color;
                parent_pt->color = grand_parent_pt->color;
                grand_parent_pt->color = temp;
                pt = parent_pt;
            }
        }

        /* Case : B
           Parent of pt is right child of Grand-parent of pt */
        else {
            Node* uncle_pt = grand_parent_pt->left;

            /* Case : 1
               The uncle of pt is also red
               Only Recoloring required */
            if ((uncle_pt != NULL) && (uncle_pt->color == RED)) {
                grand_parent_pt->color = RED;
                parent_pt->color = BLACK;
                uncle_pt->color = BLACK;
                pt = grand_parent_pt;
            } else {
                /* Case : 2
                   pt is left child of its parent
                   Right-rotation required */
                if (pt == parent_pt->left) {
                    *root = rotateRight(*root, parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }

                /* Case : 3
                   pt is right child of its parent
                   Left-rotation required */
                *root = rotateLeft(*root, grand_parent_pt);
                Color temp = parent_pt->color;
                parent_pt->color = grand_parent_pt->color;
                grand_parent_pt->color = temp;
                pt = parent_pt;
            }
        }
    }

    (*root)->color = BLACK;
}

Node* insert(Node* root, int data) {
    Node* newNode = createNode(data);

    root = bstInsert(root, newNode);

    fixViolation(&root, newNode);

    // Root may change after fixing violations
    while (root->parent != NULL) {
        root = root->parent;
    }
    
    return root;
}

void inOrder(Node* root) {
    if (root == NULL) return;

    inOrder(root->left);
    printf("%d ", root->data);
    inOrder(root->right);
}

int main(int argc, char* argv[]) {
    Node* root = NULL;
    clock_t inicio, fim;
    double tempo_decorrido;
    FILE *arquivo;
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

    rewind(arquivo);

    inicio = clock();
    for (int i = 0; i < num_numeros; i++) {
        int numero_a_inserir;
        fscanf(arquivo, "%d", &numero_a_inserir);
        root = insert(root, numero_a_inserir);
    }
    fim = clock();

    fclose(arquivo);
    tempo_decorrido = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("%.10f\n", tempo_decorrido);
    free(root);

    return 0;
}
