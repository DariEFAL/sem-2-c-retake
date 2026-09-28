#include "struct.h"

int height(AVLNode *node) {
    return node ? node->height : 0;
}

int balance_factor(AVLNode *node) {
    return node ? height(node->left) - height(node->right) : 0;
}

void update_height(AVLNode *node) {
    if (node) {
        int left_h = height(node->left);
        int right_h = height(node->right);
        node->height = (left_h > right_h ? left_h : right_h) + 1;
    }
}

/* --- Одинарные повороты --- */
AVLNode *rotate_left(AVLNode *y) {
    AVLNode *x = y->right;
    AVLNode *T2 = x->left;

    x->left = y;
    y->right = T2;

    update_height(y);
    update_height(x);
    return x;
}

AVLNode *rotate_right(AVLNode *y) {
    AVLNode *x = y->left;
    AVLNode *T2 = x->right;

    x->right = y;
    y->left = T2;

    update_height(y);
    update_height(x);
    return x;
}

/* --- Единая функция балансировки узла --- */
AVLNode *balance(AVLNode *node) {
    if (node == NULL) return NULL;

    update_height(node);
    int bf = balance_factor(node);

    /* Левое поддерево слишком тяжелое */
    if (bf > 1) {
        /* Зигзаг (Левый-Правый случай) -> сначала левый поворот для ребенка */
        if (balance_factor(node->left) < 0) {
            node->left = rotate_left(node->left);
        }
        /* Большой или малый правый поворот */
        return rotate_right(node);
    }

    /* Правое поддерево слишком тяжелое */
    if (bf < -1) {
        /* Зигзаг (Правый-Левый случай) -> сначала правый поворот для ребенка */
        if (balance_factor(node->right) > 0) {
            node->right = rotate_right(node->right);
        }
        /* Большой или малый левый поворот */
        return rotate_left(node);
    }

    return node; /* Балансировка не требуется */
}