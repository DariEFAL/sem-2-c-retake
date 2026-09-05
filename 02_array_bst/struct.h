#ifndef STRUCT_H
#define STRUCT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100

//реализация бинарного дерева на массиве
//два масива: массив данных и массив флагов, где будет обозначатся пустой ли узел
typedef struct Node {
    int value;
    int occupaied; //true-yes
} Node;

typedef struct BinaryTree {
    Node data[MAX_SIZE];
    int size;
} BinaryTree;

int init(BinaryTree *tree);
int is_empty(BinaryTree *tree, int index);

int insert(BinaryTree *tree, int value);

#endif