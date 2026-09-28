#ifndef STRUCT_H
#define STRUCT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct RBNode {
    int key; //unique
    int color; //0-black, 1-red
    struct RBNode *left, *right, *parent;
} RBNode;


void rotate_left(RBNode **root, RBNode *x);
void rotate_right(RBNode **root, RBNode *x);

int insert(RBNode **root, int key);
void print(RBNode *root, int depth);
void free_tree(RBNode *root);
int is_valid_rbt(RBNode *root);
int delete(RBNode **root, int key);

#endif