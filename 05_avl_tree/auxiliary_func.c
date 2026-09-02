#include "struct.h"

//--вспомогательные функции(4)--------------
int height(AVLNode *node) {
    if (node == NULL) return 0;
    return node->height;
}

// bf = height(left) - height(right)
int balance_factor(AVLNode *node) {
    if (node == NULL) return 0;
    return height(node->left) - height(node->right);
}

//считаем высоту узла по детям + 1
void update_height(AVLNode *node) {
    if (node == NULL) return;

    int left_h = height(node->left);
    int right_h = height(node->right);

    node->height = (left_h > right_h ? left_h : right_h) + 1;
}

AVLNode *create_avl_node(int key, int value) {
    AVLNode *new = (AVLNode*)malloc(sizeof(AVLNode));
    if (new == NULL) return NULL;

    new->key = key;
    new->value = value;
    new->height = 1;
    new->left = NULL;
    new->right = NULL;
    return new;
}