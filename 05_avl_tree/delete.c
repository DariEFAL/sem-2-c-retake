#include "struct.h"

int delete_node(AVLNode **root, int key) {
    if (root == NULL || *root == NULL) return -1;

    int status = 0;

    /* 1. Поиск удаляемого узла */
    if (key < (*root)->key) {
        status = delete_node(&((*root)->left), key);
    } else if (key > (*root)->key) {
        status = delete_node(&((*root)->right), key);
    } else {
        /* Узел найден! */
        AVLNode *node_to_free = *root;

        if ((*root)->left == NULL && (*root)->right == NULL) {
            /* Случай 1: Нет детей */
            *root = NULL;
            free(node_to_free);
        } else if ((*root)->left == NULL) {
            /* Случай 2: Только правый ребёнок */
            *root = (*root)->right;
            free(node_to_free);
        } else if ((*root)->right == NULL) {
            /* Случай 2': Только левый ребёнок */
            *root = (*root)->left;
            free(node_to_free);
        } else {
            /* Случай 3: Оба ребёнка присутствуют */
            AVLNode *min_right = (*root)->right;
            while (min_right->left != NULL) {
                min_right = min_right->left;
            }
            
            /* Копируем данные преемника */
            (*root)->key = min_right->key;
            (*root)->value = min_right->value;

            /* Удаляем преемника из правого поддерева */
            status = delete_node(&((*root)->right), min_right->key);
        }
    }

    /* 2. Балансировка оставшегося поддерева */
    if (*root != NULL) {
        *root = balance(*root);
    }

    return status;
}