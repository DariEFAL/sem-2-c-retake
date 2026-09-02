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

//подключение функций
//доп функции
int height(AVLNode *node);
int balance_factor(AVLNode *node);
void update_height(AVLNode *node);
AVLNode *create_avl_node(int key, int value);

//повороты
AVLNode *rotate_left(AVLNode *y);
AVLNode *rotate_right(AVLNode *y);
AVLNode *rotate_left_right(AVLNode *x);
AVLNode *rotate_right_left(AVLNode *x);

int insert_avl(AVLNode **root, int key, int value);
int delete_node(AVLNode **root, int key);
void print_node(struct AVLNode *treetop, int deep);
void free_tree(struct AVLNode *root);


#endif