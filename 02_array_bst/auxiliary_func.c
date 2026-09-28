#include "struct.h"

int init(BinaryTree *tree) {
    if (tree == NULL) return -1;
    tree->size = 0;
    for (int i = 0; i < MAX_SIZE; i++) {
        tree->data[i].occupaied = false;
    }
    return 0;
}

int is_empty(BinaryTree *tree, int index) {
    /* Если индекс за пределами массива, узел считается пустым */
    if (index < 0 || index >= MAX_SIZE) return 1; 
    return !tree->data[index].occupaied;
}

/* Центрированный обход: выводит элементы в строго возрастающем порядке */
void inorder_traversal(BinaryTree *tree, int index) {
    if (index >= MAX_SIZE || is_empty(tree, index)) return;

    inorder_traversal(tree, 2 * index + 1); /* Лево */
    printf("%d ", tree->data[index].value);  /* Корень */
    inorder_traversal(tree, 2 * index + 2); /* Право */
}

