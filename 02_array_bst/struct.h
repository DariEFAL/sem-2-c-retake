#ifndef STRUCT_H
#define STRUCT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 200  /* Увеличим размер, так как дерево на массиве может быть разреженным */

typedef struct Node {
    int value;
    bool occupaied;   /* Перевели в bool для экономии и чистоты кода */
} Node;

typedef struct BinaryTree {
    Node data[MAX_SIZE];
    int size;
} BinaryTree;

/* Основной интерфейс */
int init(BinaryTree *tree);
int is_empty(BinaryTree *tree, int index);
int insert(BinaryTree *tree, int value);
int delete_value(BinaryTree *tree, int value);

/* Вспомогательные функции обхода и визуализации */
void print_tree_structure(BinaryTree *tree, int index, int depth);
void inorder_traversal(BinaryTree *tree, int index);

#endif