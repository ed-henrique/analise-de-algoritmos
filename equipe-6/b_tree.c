#include <stdio.h>
#include <stdlib.h>

#define T 2 // Order of the B-tree

struct BTreeNode {
    int *keys;
    struct BTreeNode **childPointers;
    int n;
    int leaf;
};

struct BTreeNode *createNode() {
    struct BTreeNode *newNode = (struct BTreeNode *)malloc(sizeof(struct BTreeNode));
    newNode->keys = (int *)malloc(sizeof(int) * (2 * T - 1));
    newNode->childPointers = (struct BTreeNode **)malloc(sizeof(struct BTreeNode *) * (2 * T));
    newNode->n = 0;
    newNode->leaf = 1;
    return newNode;
}

void splitChild(struct BTreeNode *parent, int i, struct BTreeNode *child) {
    struct BTreeNode *newNode = createNode();
    newNode->leaf = child->leaf;
    newNode->n = T - 1;

    for (int j = 0; j < T - 1; j++)
        newNode->keys[j] = child->keys[j + T];

    if (!child->leaf) {
        for (int j = 0; j < T; j++)
            newNode->childPointers[j] = child->childPointers[j + T];
    }

    child->n = T - 1;

    for (int j = parent->n; j >= i + 1; j--)
        parent->childPointers[j + 1] = parent->childPointers[j];

    parent->childPointers[i + 1] = newNode;

    for (int j = parent->n - 1; j >= i; j--)
        parent->keys[j + 1] = parent->keys[j];

    parent->keys[i] = child->keys[T - 1];
    parent->n++;
}

void insertNonFull(struct BTreeNode *node, int key) {
    int i = node->n - 1;
    if (node->leaf) {
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->n++;
    } else {
        while (i >= 0 && key < node->keys[i])
            i--;
        i++;
        if (node->childPointers[i]->n == 2 * T - 1) {
            splitChild(node, i, node->childPointers[i]);
            if (key > node->keys[i])
                i++;
        }
        insertNonFull(node->childPointers[i], key);
    }
}

void insert(struct BTreeNode **root, int key) {
    struct BTreeNode *node = *root;
    if (node->n == 2 * T - 1) {
        struct BTreeNode *newRoot = createNode();
        newRoot->leaf = 0;
        newRoot->childPointers[0] = node;
        *root = newRoot;
        splitChild(newRoot, 0, node);
        insertNonFull(newRoot, key);
    } else {
        insertNonFull(node, key);
    }
}

void search(struct BTreeNode *node, int key) {
    int i = 0;
    while (i < node->n && key > node->keys[i])
        i++;
    if (i < node->n && key == node->keys[i]) {
        printf("Key %d found in the B-tree\n", key);
        return;
    }
    if (node->leaf) {
        printf("Key %d not found in the B-tree\n", key);
        return;
    }
    search(node->childPointers[i], key);
}

void traverse(struct BTreeNode *root) {
    if (root) {
        int i;
        for (i = 0; i < root->n; i++) {
            traverse(root->childPointers[i]);
            printf("%d ", root->keys[i]);
        }
        traverse(root->childPointers[i]);
    }
}

int main() {
    struct BTreeNode *root = createNode();
    insert(&root, 10);
    insert(&root, 20);
    insert(&root, 5);
    insert(&root, 6);
    insert(&root, 12);
    insert(&root, 30);

    printf("Traversal of the constructed B-tree:\n");
    traverse(root);
    printf("\n");

    int key = 6;
    search(root, key);

    key = 15;
    search(root, key);

    return 0;
}
