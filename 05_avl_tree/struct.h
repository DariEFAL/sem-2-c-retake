#ifndef STRUCT_H
#define STRUCT_H

#include <stdio.h>
#include <stdlib.h>

typedef struct AVLNode {
    int key;
    int value;
    int height; 
    struct AVLNode *left;
    struct AVLNode *right;
} AVLNode;

int height(AVLNode *node);
AVLNode *balance(AVLNode *node);

int insert_avl(AVLNode **root, int key, int value);
int delete_node(AVLNode **root, int key);
void print_node(AVLNode *treetop, int deep);
void free_tree(AVLNode *root);
int is_valid_avl(AVLNode *root);

#endif