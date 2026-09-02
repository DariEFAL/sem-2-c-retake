#include "struct.h"

int delete_node(AVLNode **root, int key) {
    if (root == NULL || *root == NULL) return -1;

    int exit = -3;
    if (key == (*root)->key) {
        if ((*root)->left == NULL && (*root)->right == NULL) {
            free(*root);
            *root = NULL;
            return 0;
        }
        else if ((*root)->left == NULL) {
            AVLNode *temp = (*root)->right;
            free(*root);
            *root = temp;
            return 0;
        }
        else if ((*root)->right == NULL) {
            AVLNode *temp = (*root)->left;
            free(*root);
            *root = temp;
            return 0;
        }

        AVLNode *min_right = (*root)->right;

        while (min_right->left != NULL) {
            min_right = min_right->left;
        }
        
        (*root)->key = min_right->key;
        (*root)->value = min_right->value;

        exit = delete_node(&((*root)->right), min_right->key);
    }
    else {
        exit = delete_node((key < (*root)->key 
                            ? &((*root)->left) 
                            : &((*root)->right)), key);
    }

    update_height(*root);
    int bf = balance_factor(*root);

    if (bf < -1 && balance_factor((*root)->right) <= 0) *root = rotate_left(*root);
    else if (bf > 1 && balance_factor((*root)->left) >= 0) *root = rotate_right(*root);
    else if (bf > 1 && balance_factor((*root)->left) < 0) *root = rotate_left_right(*root);
    else if (bf < -1 && balance_factor((*root)->right) > 0) *root = rotate_right_left(*root);

    return exit;
}