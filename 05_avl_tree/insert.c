#include "struct.h"

AVLNode *create_avl_node(int key, int value) {
    AVLNode *new_node = (AVLNode*)malloc(sizeof(AVLNode));
    if (new_node == NULL) return NULL;
    new_node->key = key;
    new_node->value = value;
    new_node->height = 1;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

int insert_avl(AVLNode **root, int key, int value) {
    if (root == NULL) return -1;

    /* 1. Стандартная вставка в BST */
    if (*root == NULL) {
        AVLNode *new_node = create_avl_node(key, value);
        if (new_node == NULL) return -2;
        *root = new_node;
        return 0;
    } 
    
    if (key == (*root)->key) {
        (*root)->value = value; /* Обновление значения при совпадении ключа */
        return 0;
    }

    int status = insert_avl((key < (*root)->key ? &((*root)->left) : &((*root)->right)), key, value);
    
    /* 2. Автоматическая балансировка на обратном пути рекурсии */
    *root = balance(*root);

    return status;
}